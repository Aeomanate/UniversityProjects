#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

using Vector = vector<double>;
using Matrix = vector<Vector>;
struct Layer {
    double const time_point;
    Matrix temperature; // Матрица температур в узлах пластины.
                        // В строках - температуры по оси Ox.
                        // В столбцах - температуры по оси Oy.
    
    // Конструктор нового слоя.
    // Необязательный параметр используется при создании самого первого слоя.
    Layer(double time_point, size_t y, size_t x,
          double start_temperature = numeric_limits<double>::quiet_NaN())
    : time_point(time_point), temperature(y, Vector(x, start_temperature)) { }
};
using Layers = vector<Layer>;


inline double sqr(double x) {
    return x * x;
}
struct StartData {
    StartData(double a,
              double length_x, double length_y,
              size_t splits_x, size_t splits_y,
              double start_plate_temperature,
              double environment_temperature)
            : length_x(length_x), length_y(length_y)
              , splits_x(splits_x + 1), splits_y(splits_y + 1)
              , step_x(length_x / splits_x)
              , step_y(length_y / splits_y)
              , step_t(sqr(step_x) * sqr(step_y) / (2 * a * (sqr(step_x) + sqr(step_y))))
              , a(a)
              , r(1 - 2*a*step_t * (1/sqr(step_x) + 1/sqr(step_y)))
              , rx(a*step_t / sqr(step_x))
              , ry(a*step_t / sqr(step_y))
              , start_plate_temperature(start_plate_temperature)
              , environment_temperature(environment_temperature)
    { }
    
    double const length_x, length_y;
    size_t const splits_x, splits_y;
    double const step_x, step_y, step_t; // Величина шагов в разностной схеме.
    double const a;  // Коэффициент теплопроводности.
    double const r;  // Коэффициент при U_ij.
    double const rx; // Коэффициент при разности по x.
    double const ry; // Коэффициент при разности по y.
    double const start_plate_temperature;
    double const environment_temperature;
};

class MatlabVisualization {
    // Делаем другом класс рассчёта температур пластины
    // с любым набором функций, описывающих температуру на границе.
    template <class Collection> friend class PlateHeatEquation;
  private:
    
    MatlabVisualization(Layers const& layers,
                        StartData const& data,
                        size_t delimiter_layers)
    : layers(layers), data(data), delimiter_layers(delimiter_layers) { }
    
    void generate(string filename) {
        // Созданные матрицы описывают точку, в которой задана температура узла.
        // Строка i из X - это положение узла по оси Ox.
        // Для каждой строки i из X есть строка i из Y,
        // описывающая положение узла в X на оси Oy.
        Matrix coord_nodes_X = create_X();
        Matrix coord_nodes_Y = create_Y();
        
        // Одна матрица описывает температуру пластины в указанных узлах сетки
        // в фиксированный момент времени.
        // В строке расположены температуры узлов по оси Ox.
        // Строки описывают температру узлов по оси Oy.
        vector<Matrix> temperatures = create_Zs();
        
        // Создаём файл с матрицами температур.
        create_data_file("Data_" + filename, coord_nodes_X, coord_nodes_Y, temperatures);
        
        // Создаём файл с функцией, рисующей температуру пластины во времени.
        create_animation_function("RunAnimation_" + filename, "Data_" + filename);
    }
  
  private:
    Matrix create_X() {
        Matrix coord_nodes_X(data.splits_y, Vector(data.splits_x));
        
        // Сгенерируем только раз разбиение по X, ...
        size_t cur_node = 0;
        double x = 0;
        while(cur_node < data.splits_x) {
            coord_nodes_X[0][cur_node++] = x;
            x += data.step_x;
        }
        
        // ... после чего скопируем.
        // Самоприсваивание должно быть учтено классом vector в operator=.
        for(auto& row: coord_nodes_X)
            row = coord_nodes_X[0];
        
        return coord_nodes_X;
    }
    Matrix create_Y() {
        Matrix coord_nodes_Y(data.splits_y, Vector(data.splits_x));
        
        // Генерируем разбиение по Y для каждой строки по X.
        double cur_y = 0;
        for(auto& row: coord_nodes_Y) {
            for(auto& column: row)
                column = cur_y;
            cur_y += data.step_y;
        }
        
        return coord_nodes_Y;
    }
    vector<Matrix> create_Zs() {
        vector<Matrix> temperatures(layers.size());
        
        // Просто переносим уже имеющиеся данные температуры в матрицы.
        for(size_t i = 0; i != layers.size(); ++i)
            temperatures[i] = move(layers[i].temperature);
        
        return temperatures;
    }
    
    void create_data_file(string DataFile,
                          Matrix const& X, Matrix const& Y,
                          vector<Matrix> const& Zs) {
        ofstream out(DataFile);
        if(!out) throw runtime_error("File not open: " + DataFile);
        
        auto printer = [&out] (Matrix const& M, string variable_name) mutable -> ostream& {
            out << variable_name << " = [" << endl;
            
            for(auto& row: M) {
                for (auto& cell: row)
                    out << setw(12) << left << setprecision(6) << cell << ", ";
                out << ';' << endl;
            }
            
            out << "];";
            
            return out;
        };
    
    
        out << "function [X, Y, Z] = "
            // Отбрасываем расширение файла и используем остаток как имя функции.
            << DataFile.substr(0, DataFile.rfind('.'))
            << "()"
            << endl;
        
        // Генерируем два двумерных массива для MatLAB.
        printer(X, "X") << endl << endl;
        printer(Y, "Y") << endl << endl;
        
        // Генерируем трёхмерный массив для MatLAB.
        count_print_layers = 1;
        for(size_t i = 0; i != Zs.size(); ++i)
            if(i % delimiter_layers == 0)
                printer(Zs[i], "Z(:,:," + to_string(count_print_layers++) + ")") << endl;
    }
    
    void create_animation_function(string animation_func_name,
                                   string DataFile) {
        ofstream out(animation_func_name);
        
        if(!out)
            throw runtime_error("File not open: " + animation_func_name);
        
        out << "function [] = " +
                // Отбрасываем точку в имени файла-функции.
               animation_func_name.substr(0, animation_func_name.rfind('.')) +
               "()" << endl;
        
        out << "[X, Y, Z] = " +
                // Отбрасываем точку в имени файла данных температур.
               DataFile.substr(0, DataFile.rfind('.')) +
               "();" << endl;
        
        // Создаём код вывода графика изменения температуры пластины во времени.
        out << "                                                                      \n"
               "minX = min(min(X(:,:)));                                              \n"
               "maxX = max(max(X(:,:)));                                              \n"
               "minY = min(min(Y(:,:)));                                              \n"
               "maxY = max(max(Y(:,:)));                                              \n"
               "minZ = min(min(min(Z(:,:,:))));                                       \n"
               "maxZ = max(max(max(Z(:,:,:))));                                       \n"
               "                                                                      \n"
               "h = figure(1);                                                        \n"
               "i = 0;                                                                \n"
               "axis([minX maxX minY maxY minZ maxZ]);                                \n"
               "                                                                      \n"
               "isRecordGif = false;                                                  \n"
               "f = getframe;                                                         \n"
               "[im,map] = rgb2ind(f.cdata,256,'nodither');                           \n"
               "im(1,1,1," + to_string(count_print_layers-1) + ") = 0;                \n"
               "while true                                                            \n"
               "    if ~ishandle(h) % While the window with the graph is alive        \n"
               "        return;                                                       \n"
               "    end                                                               \n"
               "                                                                      \n"
               "    if i == " + to_string(count_print_layers-1) + "                   \n"
               "      if isRecordGif == true                                          \n"
               "        imwrite(im,map,'Test.gif','DelayTime',t_step,'LoopCount',inf) \n"
               "        break;                                                        \n"
               "      else                                                            \n"
               "        i = 1;                                                        \n"
               "      end                                                             \n"
               "    else                                                              \n"
               "        i = i + 1;                                                    \n"
               "    end                                                               \n"
               "                                                                      \n"
               "                                                                      \n"
               "    [az, el] = view; % Get current view-point                         \n"
               "    surf(X, Y, Z(:,:,i));                                             \n"
               "    axis([minX maxX minY maxY minZ maxZ])                             \n"
               "    view([az el]);   % Set previous view-point                        \n"
               "                                                                      \n"
               "    grid on;                                                          \n"
               "    xlabel('X');                                                      \n"
               "    ylabel('Y');                                                      \n"
               "    zlabel('Temperature');                                            \n"
               "                                                                      \n"
               "    t_step = " + to_string(data.step_t) + ";                          \n"
               "                                                                      \n"
               "    title(['Current time: ' num2str(i * t_step)]);                    \n"
               "    if isRecordGif == true                                            \n"
               "        f = getframe;                                                 \n"
               "        im(:,:,1,i) = rgb2ind(f.cdata,map,'nodither');                \n"
               "    end                                                               \n"
               "                                                                      \n"
               "  % Transfer flow of execution to the functions of the interface      \n"
               "    drawnow;                                                          \n"
               "    pause(t_step);                                                    \n"
               "end                                                                   \n"
               "                                                                      \n"
               "end                                                                   \n";
    }
  private:
    size_t count_print_layers; // Используется в отрисовке графиков в MatLAB.
    size_t delimiter_layers; // Пример: при 2/12/n печатаем каждый 2/12/n-й слой.
    Layers    const& layers;
    StartData const& data;
};

namespace BorderFunctors {
  template <class T>
      struct Storage {
          // Дополнительный класс-обёртка (уже функтор, а не функция) вводится
          // ради того, чтобы было удобно вызывать нужную функцию расчёта
          // температуры на границе полиморфно - не заботясь о типах параметров
          // и их количестве, которые исходная функция принимает.
    
          using FunctionSingature = T;
          
          Storage(function<FunctionSingature> border_temperature)
          : border_temperature(border_temperature) { }
          
          // Полиморфный оператор, используемый потомками-функторами
          virtual double operator()(double, Matrix const&, size_t) const {
              throw logic_error("Attempt to call base-temperature-border function");
          };
          
          // Тут храним функцию, вычисляющую температуру
          // на переданной в конструктор границе.
          function<FunctionSingature> border_temperature;
      };
  
  template <size_t, class T> // Объявление функтора, содержание которого
      struct BorderFunctor;  // зависит от первого параметра -
                             // количества аргументов у переданной функции.
  
  template <class F>
      struct BorderFunctor<1, F>: Storage<F> {
          using Storage<F>::Storage;
          
          // Этот функтор отвечает за расчёт температуры границы из-за нагрева.
          // Соответствующая функция принимает только один аргумент -
          // текущее время, поэтому текущий слой и узел не важны.
          double operator()(double time, Matrix const&, size_t) const override {
              return this->border_temperature(time);
          }
      };
  template <class F>
      struct BorderFunctor<2, F>: Storage<F> {
          using Storage<F>::Storage;
          
          // Этот функтор отвечает за расчёт температуры остывающей границы.
          // Соответствующая функция требует текущий слой и узел, для которого
          // рассчитывается температура. Текущее время здесь не играет роли.
          double
          operator()(double, Matrix const& cur_layer, size_t node) const override {
              return this->border_temperature(cur_layer, node);
          }
      };
  
  template <class F1, class F2, class F3, class F4>
      class BorderFunctors {
          // Этот класс предоставляет возможность унифицированного обращения к
          // функторам, возвращающим температуру на требуемой границе.
        public:
          BorderFunctors(Storage<F1>* left, Storage<F2>* up,
                         Storage<F3>* right, Storage<F4>* down)
          : left(left), up(up), right(right), down(down) {
          }
          
          enum class Barriers { LEFT, UP, RIGHT, DOWN };
          double
          operator()(Barriers requested,
                     double cur_time,
                     Matrix const& cur_layer,
                     size_t node) const {
              switch (requested) {
                  // Вызываем функцию для соответствующей границы полиморфно -
                  // пусть сама догадается какие аргументы ей нужны.
                  case Barriers::LEFT : return (*left) (cur_time, cur_layer, node);
                  case Barriers::UP   : return (*up)   (cur_time, cur_layer, node);
                  case Barriers::RIGHT: return (*right)(cur_time, cur_layer, node);
                  case Barriers::DOWN : return (*down) (cur_time, cur_layer, node);
              }
          }
        
        private:
          // Храним указатели на функторы, так как полиморфный вызов возможен
          // только при условии, что родитель ссылается на потомка.
          
          // Ссылку (и тем более правую ссылку) на стековый объект
          // использовать опасно из-за риска её удалить в процессе.
          // Поэтому используем указатель на функтор в куче.
          shared_ptr<Storage<F1>> left;
          shared_ptr<Storage<F2>> up;
          shared_ptr<Storage<F3>> right;
          shared_ptr<Storage<F4>> down;
      };
  
  template <class Ret, class... Params>
      auto MakeBorderFunctor(function<Ret(Params...)> f) {
          // Функция принимает std::function с сигнатурой,
          // вычисляемой компилятором при вызове.
          
          // Возвращает указатель на функтор в куче, который параметризован
          // двумя параметрами:
          // - Количеством принимаемых параметров std::function,
          // - Сигнатурой переданной функции
          // Инициализируется этот функтор переданной std::function.
          return new BorderFunctor<sizeof...(Params), Ret(Params...)>(f);
      }
  template <class... Functors>
      auto MakeBorderFunctors(Storage<Functors>* ... args) {
          // Функция принимает указатели на базовый-класс обёртку.
          // Каждый указатель на базовый класс параметризован функтором.
          // Этот функтор, в свою очередь, хранит std::function -
          // функтор, хранящий функцию, вычисляющую температуру на границе.
          // Тип переданного функтора компилятор вычисляет при вызове функции.
          
          // Делается ставка на то, что переданных аргументов 4,
          // а возможных сигнатур базовых классов-хранилищ всего две:
          // - double(Matrix const&, size_t)
          // - double(double)
          // При других вариантах нужно переписывать программу.
          
          // Возвращается один объект-функтор,
          // параметризованный вычисленными сигнатурами функций и инициализируемый
          // переданными указателями на базовые классы хранилища функторов.
          return BorderFunctors<typename Storage<Functors>::FunctionSingature...>(args...);
      }
}

template <class BordersCollection>
    class PlateHeatEquation {
      public:
        PlateHeatEquation(StartData const& data, BordersCollection functors)
        : functors(functors), data(data)
        // Создаём в коллекции слоёв один слой с заданными параметрами.
        , layers{{0, data.splits_y, data.splits_x, data.start_plate_temperature}}
        { }
        
        void generate_visualization_matlab(string filename, bool while_not_stationary,
                                           size_t count_layers,
                                           size_t delimiter_layers,
                                           double epsilon) {
            // Выбираем до какой поры ведутся вычисления новых слоёв.
            if(while_not_stationary)
                do {
                    calculate_new_layer();
                    calculate_new_layer();
                } while(!isTemperatureStationary(epsilon));
            else
                for(size_t i = 0; i < count_layers - 1; ++i)
                        calculate_new_layer();
            
            // Создаём файлы функций для визуализации результата в MatLAB.
            MatlabVisualization(layers, data, delimiter_layers).generate(filename);
        }
      
      private:
        // Так как параметры шаблонного класса функторов BorderFunctions
        // вычислить проблематично (потребуется ещё одна make-функция),
        // то пусть компилятор сделает всё сам, а тут не будем указывать
        // явно, что тип объекта functors - BorderFunctors<...>.
        // TODO: Заменяя класс функторов не аналогичным по функционалу,
        // TODO: этот класс придётся переписать.
        BordersCollection const functors;
        StartData const data;
        Layers  layers;
      
      private:
        void calculate_new_layer() {
            // Для начала добавим новый слой.
            layers.push_back(
                    Layer{
                            layers.back().time_point + data.step_t,
                            data.splits_y,
                            data.splits_x
                    }
            );
            
            // По разностной схеме считаем температуру "в середине",
            // руководствуясь температурой на предыдущем слое.
            auto& cur  = (layers.rbegin())    ->temperature;
            auto& prev = (layers.rbegin() + 1)->temperature;
            
            // Значения splits_x/y однозначно связаны с размерами слоя.
            for(size_t y = 1; y <= data.splits_y - 2; ++y)
                for(size_t x = 1; x <= data.splits_x - 2; ++x)
                    cur[y][x] = data.r * prev[y][x] +
                                data.rx * (prev[y][x-1]+ prev[y][x+1]) +
                                data.ry * (prev[y-1][x]+ prev[y+1][x]) ;
            
            // Рассчитали середину - пора и к границам подступиться.
            calculate_borders();
        }
        void calculate_borders() {
            // Рассчитываем температуру на границах пластины через функторы,
            // которые являются функциями зависимости температуры на границе
            // от температуры, что ближе к середине (или времени, если нагрев).
            auto&  cur_layer  = layers.back().temperature;
            double cur_time   = layers.back().time_point;
            using B = typename BordersCollection::Barriers;
            
            // Сначала рассчитаем границы при x_min, x_max
            // без верхней и нижней границ по y_min и y_max.
            size_t x_min = 0;
            size_t x_max = data.splits_x - 1;
            for(size_t y = 1; y <= data.splits_y - 2; ++y) {
                cur_layer[y][x_max] = functors(B::RIGHT, cur_time, cur_layer, y);
                cur_layer[y][x_min] = functors(B::LEFT , cur_time, cur_layer, y);
            }
            
            // Теперь рассчитаем границы при y_min, y_max по всей длине x.
            size_t y_min = 0;
            size_t y_max = data.splits_y - 1;
            for(size_t x = 0; x <= data.splits_x - 1; ++x) {
                cur_layer[y_max][x] = functors(B::UP  , cur_time, cur_layer, x);
                cur_layer[y_min][x] = functors(B::DOWN, cur_time, cur_layer, x);
            }
        }
        
        bool isTemperatureStationary(double epsilon) {
            auto& upper  = (layers.end() - 1)->temperature;
            auto& middle = (layers.end() - 2)->temperature;
            auto& lower  = (layers.end() - 3)->temperature;
            
            auto max_matrix_variation = [] (Matrix const& A, Matrix const& B) {
                double max_variation = -1;
                
                // Размерности матриц предполагаются одинаковыми.
                for(size_t i = 0; i != A.size(); ++i)
                    for(size_t j = 0; j != A[0].size(); ++j){
                        double variation = abs(A[i][j] - B[i][j]);
                        if(max_variation < variation)
                            max_variation = variation;
                    }
                
                return max_variation;
            };
    
            double variation_up_mid  = max_matrix_variation(upper, middle);
            double variation_mid_low = max_matrix_variation(middle, lower);
    
            // Сравниваем отклонения температур на трёх слоях.
            return abs(variation_up_mid - variation_mid_low) < epsilon;
        }
    };

namespace BorderFunctions {
  struct WrapperBase {
      // Служит для хранения постоянных переменных от вызова к вызову в функциях.
      WrapperBase(StartData const& data, double k): data(data), k(k) { }
    protected:
      StartData const data;
      double k; // Коэффициент, заданный для границы по условию.
  };
  
  // Функции, обеспечивающие рассчёт температуры на данной границе.
  struct Left   : WrapperBase {
      using WrapperBase::WrapperBase;
      double f (Matrix const& cur_layer, size_t row) const {
          return (cur_layer[row][1] +
                  data.step_x * k * data.environment_temperature)
                 / (1 + data.step_x * k);
      }
  };
  struct Up     : WrapperBase {
      using WrapperBase::WrapperBase;
      double f (Matrix const& cur_layer, size_t col) const {
          return (cur_layer[data.splits_y - 2][col] -
                  data.step_y * k * data.environment_temperature)
                 / (1 - data.step_y * k);
      }
  };
  struct Right  : WrapperBase {
      using WrapperBase::WrapperBase;
      double f (Matrix const& cur_layer, size_t row) const {
          return (cur_layer[row][data.splits_x - 2] -
                  data.step_x * k * data.environment_temperature)
                 / (1 - data.step_x * k);
      }
  };
  struct Down   : WrapperBase {
      using WrapperBase::WrapperBase;
      double f (Matrix const& cur_layer, size_t col) const {
          return (cur_layer[1][col] +
                  data.step_y * k * data.environment_temperature)
                 / (1 + data.step_y * k);
      }
  };
  struct Heating: WrapperBase {
      using WrapperBase::WrapperBase;
      double f (double time) const {
          return data.start_plate_temperature + k * time;
      }
  };
  
  template <class Functor, class Ret, class... Params>
      function<Ret(Params...)>
      GenerateLambda (Functor const& functor, Ret(Functor::*f)(Params...) const) {
          // Приняли обёртку и вычислили сигнатуру функции, хранимой в ней.
          
          // Теперь вернём лямбду, вызывающую функцию-член
          // с вычисленными параметрами.
          return [&functor, f] (Params... args) {
              // В самой лямбде принимаем параметры для функции-члена,
              // известные из сигнатуры, после чего вызываем функцию-член,
              // используя переданные параметры.
              return (functor.*f)(args...);
          };
      }
  
  template <class Functor, size_t option = 0, class... InitParams>
      auto LambdaGenerator (InitParams... init_args) {
          // - Функция принимает 2 параметра: необходимые данные типа StartData
          // и коэффициент, разный для каждой из граничных функций.
          // - Параметр шаблона option нужен для создания разных функций для
          // разных границ, которые нагреваются
          // (если границ с нагревом больше одной).
          
          
          // Так как функция-обёртка для одной границы будет только одна,
          // укажем, что она будет храниться в статической области памяти.
          // Более того, объект будет константным, так как не изменяет хранимых
          // аргументов, необходимых для вычисления температуры.
          static const Functor border(init_args...);
          
          // Указываем, что хотим получить лямбду от заданной границы,
          // которая будет использовать переданные параметры:
          // сам объект барьера и указатель на функцию-член, необходимый для
          // вычисления сигнатуры этой функции-члена.
          return GenerateLambda<Functor>(border, border.f);
      }
}
namespace BF = BorderFunctions;

int main() {
    // Значения коэффициентов, заданных по условию задачи.
    double a = 0.01;
    double length_x = 1, length_y = 1;
    double start_plate_temperature  = 372;
    double environment_temperature  = 293;
    
    // Значения, используемые при решении задачи.
    size_t splits_x = 50 , splits_y = 50;
    size_t count_layers = 3500;
    size_t delimiter_layers = 20; // Печатаем только каждый delimiter_layers слой.
    bool   while_not_stationary = false; // Считаем отклонения температур или слои?
    double epsilon = 1e-6; // При такой разнице отклонений температур - остановка.
    
    // Объект, представляющий собою совокупность данных по условию
    // и данных, вычисленных на их основе.
    StartData start_data(a,
                         length_x, length_y,
                         splits_x, splits_y,
                         start_plate_temperature,
                         environment_temperature);
    
    // Обёртки над функциями.
    // Считают температуру на границе в задаваемом слое и узле ИЛИ времени.
    // Обёртки хранят состояние (данные, необходимые для их работы)
    // и делают удобным вычисление температуры на границе:
    // без передачи лишних, постоянных аргументов.
    // auto left  = BF::LambdaGenerator<BF::Left   , 1> (start_data, 0.1);
    // auto up    = BF::LambdaGenerator<BF::Heating, 2> (start_data,  4 );
    // auto right = BF::LambdaGenerator<BF::Right  , 3> (start_data, 0.2);
    // auto down  = BF::LambdaGenerator<BF::Down   , 4> (start_data,  0 );
    
    auto left  = BF::LambdaGenerator<BF::Left   , 1> (start_data,  0);
    auto up    = BF::LambdaGenerator<BF::Up     , 2> (start_data,  0.1);
    auto right = BF::LambdaGenerator<BF::Heating, 3> (start_data,  1);
    auto down  = BF::LambdaGenerator<BF::Down   , 4> (start_data,  0.3);
    
    auto border_functors = BorderFunctors::MakeBorderFunctors (
            BorderFunctors::MakeBorderFunctor( left),
            BorderFunctors::MakeBorderFunctor(   up),
            BorderFunctors::MakeBorderFunctor(right),
            BorderFunctors::MakeBorderFunctor( down)
    );
    
    using BordersCollection = decltype(border_functors);
    
    try {
        PlateHeatEquation<BordersCollection>(start_data, border_functors)
        .generate_visualization_matlab("Plate4.m", while_not_stationary,
                                       count_layers, delimiter_layers, epsilon);
        cout << "Success" << endl;
    } catch(exception const& e) {
        cout << "Error: " << e.what() << endl;
        system("PAUSE");
    }
    return 0;
}