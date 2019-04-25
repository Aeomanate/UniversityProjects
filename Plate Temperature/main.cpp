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
    Matrix temperature; // ����� ⥬������ � 㧫�� ����⨭�.
                        // � ��ப�� - ⥬������� �� �� Ox.
                        // � �⮫��� - ⥬������� �� �� Oy.
    
    // ��������� ������ ᫮�.
    // ����易⥫�� ��ࠬ��� �ᯮ������ �� ᮧ����� ᠬ��� ��ࢮ�� ᫮�.
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
    double const step_x, step_y, step_t; // ����稭� 蠣�� � ࠧ���⭮� �奬�.
    double const a;  // �����樥�� ⥯���஢������.
    double const r;  // �����樥�� �� U_ij.
    double const rx; // �����樥�� �� ࠧ���� �� x.
    double const ry; // �����樥�� �� ࠧ���� �� y.
    double const start_plate_temperature;
    double const environment_temperature;
};

class MatlabVisualization {
    // ������ ��㣮� ����� ������ ⥬������ ����⨭�
    // � ��� ����஬ �㭪権, ����뢠��� ⥬������� �� �࠭��.
    template <class Collection> friend class PlateHeatEquation;
  private:
    
    MatlabVisualization(Layers const& layers,
                        StartData const& data,
                        size_t delimiter_layers)
    : layers(layers), data(data), delimiter_layers(delimiter_layers) { }
    
    void generate(string filename) {
        // �������� ������ ����뢠�� ���, � ���ன ������ ⥬������ 㧫�.
        // ��ப� i �� X - �� ��������� 㧫� �� �� Ox.
        // ��� ������ ��ப� i �� X ���� ��ப� i �� Y,
        // ����뢠��� ��������� 㧫� � X �� �� Oy.
        Matrix coord_nodes_X = create_X();
        Matrix coord_nodes_Y = create_Y();
        
        // ���� ����� ����뢠�� ⥬������� ����⨭� � 㪠������ 㧫�� �⪨
        // � 䨪�஢���� ������ �६���.
        // � ��ப� �ᯮ������ ⥬������� 㧫�� �� �� Ox.
        // ��ப� ����뢠�� ⥬������ 㧫�� �� �� Oy.
        vector<Matrix> temperatures = create_Zs();
        
        // ������ 䠩� � ����栬� ⥬������.
        create_data_file("Data_" + filename, coord_nodes_X, coord_nodes_Y, temperatures);
        
        // ������ 䠩� � �㭪樥�, ����饩 ⥬������� ����⨭� �� �६���.
        create_animation_function("RunAnimation_" + filename, "Data_" + filename);
    }
  
  private:
    Matrix create_X() {
        Matrix coord_nodes_X(data.splits_y, Vector(data.splits_x));
        
        // �������㥬 ⮫쪮 ࠧ ࠧ������ �� X, ...
        size_t cur_node = 0;
        double x = 0;
        while(cur_node < data.splits_x) {
            coord_nodes_X[0][cur_node++] = x;
            x += data.step_x;
        }
        
        // ... ��᫥ 祣� ᪮���㥬.
        // ������ᢠ������ ������ ���� ��⥭� ����ᮬ vector � operator=.
        for(auto& row: coord_nodes_X)
            row = coord_nodes_X[0];
        
        return coord_nodes_X;
    }
    Matrix create_Y() {
        Matrix coord_nodes_Y(data.splits_y, Vector(data.splits_x));
        
        // ������㥬 ࠧ������ �� Y ��� ������ ��ப� �� X.
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
        
        // ���� ��७�ᨬ 㦥 ����騥�� ����� ⥬������� � ������.
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
            // ����뢠�� ���७�� 䠩�� � �ᯮ��㥬 ���⮪ ��� ��� �㭪樨.
            << DataFile.substr(0, DataFile.rfind('.'))
            << "()"
            << endl;
        
        // ������㥬 ��� ��㬥��� ���ᨢ� ��� MatLAB.
        printer(X, "X") << endl << endl;
        printer(Y, "Y") << endl << endl;
        
        // ������㥬 ���嬥�� ���ᨢ ��� MatLAB.
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
                // ����뢠�� ��� � ����� 䠩��-�㭪樨.
               animation_func_name.substr(0, animation_func_name.rfind('.')) +
               "()" << endl;
        
        out << "[X, Y, Z] = " +
                // ����뢠�� ��� � ����� 䠩�� ������ ⥬������.
               DataFile.substr(0, DataFile.rfind('.')) +
               "();" << endl;
        
        // ������ ��� �뢮�� ��䨪� ��������� ⥬������� ����⨭� �� �६���.
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
    size_t count_print_layers; // �ᯮ������ � ���ᮢ�� ��䨪�� � MatLAB.
    size_t delimiter_layers; // �ਬ��: �� 2/12/n ���⠥� ����� 2/12/n-� ᫮�.
    Layers    const& layers;
    StartData const& data;
};

namespace BorderFunctors {
  template <class T>
      struct Storage {
          // �������⥫�� �����-����⪠ (㦥 �㭪��, � �� �㭪��) ��������
          // ࠤ� ⮣�, �⮡� �뫮 㤮��� ��뢠�� �㦭�� �㭪�� �����
          // ⥬������� �� �࠭�� �������䭮 - �� �������� � ⨯�� ��ࠬ��஢
          // � �� ������⢥, ����� ��室��� �㭪�� �ਭ�����.
    
          using FunctionSingature = T;
          
          Storage(function<FunctionSingature> border_temperature)
          : border_temperature(border_temperature) { }
          
          // ��������� ������, �ᯮ��㥬� ��⮬����-�㭪�ࠬ�
          virtual double operator()(double, Matrix const&, size_t) const {
              throw logic_error("Attempt to call base-temperature-border function");
          };
          
          // ��� �࠭�� �㭪��, ��������� ⥬�������
          // �� ��।����� � ��������� �࠭��.
          function<FunctionSingature> border_temperature;
      };
  
  template <size_t, class T> // ������� �㭪��, ᮤ�ঠ��� ���ண�
      struct BorderFunctor;  // ������ �� ��ࢮ�� ��ࠬ��� -
                             // ������⢠ ��㬥�⮢ � ��।����� �㭪樨.
  
  template <class F>
      struct BorderFunctor<1, F>: Storage<F> {
          using Storage<F>::Storage;
          
          // ��� �㭪�� �⢥砥� �� ����� ⥬������� �࠭��� ��-�� ���ॢ�.
          // ���⢥������� �㭪�� �ਭ����� ⮫쪮 ���� ��㬥�� -
          // ⥪�饥 �६�, ���⮬� ⥪�騩 ᫮� � 㧥� �� �����.
          double operator()(double time, Matrix const&, size_t) const override {
              return this->border_temperature(time);
          }
      };
  template <class F>
      struct BorderFunctor<2, F>: Storage<F> {
          using Storage<F>::Storage;
          
          // ��� �㭪�� �⢥砥� �� ����� ⥬������� ���뢠�饩 �࠭���.
          // ���⢥������� �㭪�� �ॡ�� ⥪�騩 ᫮� � 㧥�, ��� ���ண�
          // �����뢠���� ⥬������. ����饥 �६� ����� �� ��ࠥ� ஫�.
          double
          operator()(double, Matrix const& cur_layer, size_t node) const override {
              return this->border_temperature(cur_layer, node);
          }
      };
  
  template <class F1, class F2, class F3, class F4>
      class BorderFunctors {
          // ��� ����� �।��⠢��� ����������� 㭨��஢������ ���饭�� �
          // �㭪�ࠬ, �������騬 ⥬������� �� �ॡ㥬�� �࠭��.
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
                  // ��뢠�� �㭪�� ��� ᮮ⢥�����饩 �࠭��� �������䭮 -
                  // ����� ᠬ� ���������� ����� ��㬥��� �� �㦭�.
                  case Barriers::LEFT : return (*left) (cur_time, cur_layer, node);
                  case Barriers::UP   : return (*up)   (cur_time, cur_layer, node);
                  case Barriers::RIGHT: return (*right)(cur_time, cur_layer, node);
                  case Barriers::DOWN : return (*down) (cur_time, cur_layer, node);
              }
          }
        
        private:
          // �࠭�� 㪠��⥫� �� �㭪���, ⠪ ��� ��������� �맮� ��������
          // ⮫쪮 �� �᫮���, �� த�⥫� ��뫠���� �� ��⮬��.
          
          // ��뫪� (� ⥬ ����� �ࠢ�� ��뫪�) �� �⥪��� ��ꥪ�
          // �ᯮ�짮���� ���᭮ ��-�� �᪠ �� 㤠���� � �����.
          // ���⮬� �ᯮ��㥬 㪠��⥫� �� �㭪�� � ���.
          shared_ptr<Storage<F1>> left;
          shared_ptr<Storage<F2>> up;
          shared_ptr<Storage<F3>> right;
          shared_ptr<Storage<F4>> down;
      };
  
  template <class Ret, class... Params>
      auto MakeBorderFunctor(function<Ret(Params...)> f) {
          // �㭪�� �ਭ����� std::function � ᨣ����ன,
          // ����塞�� ��������஬ �� �맮��.
          
          // �����頥� 㪠��⥫� �� �㭪�� � ���, ����� ��ࠬ��ਧ����
          // ���� ��ࠬ��ࠬ�:
          // - ������⢮� �ਭ������� ��ࠬ��஢ std::function,
          // - �������ன ��।����� �㭪樨
          // ���樠��������� ��� �㭪�� ��।����� std::function.
          return new BorderFunctor<sizeof...(Params), Ret(Params...)>(f);
      }
  template <class... Functors>
      auto MakeBorderFunctors(Storage<Functors>* ... args) {
          // �㭪�� �ਭ����� 㪠��⥫� �� ������-����� ������.
          // ����� 㪠��⥫� �� ������ ����� ��ࠬ��ਧ���� �㭪�஬.
          // ��� �㭪��, � ᢮� ��।�, �࠭�� std::function -
          // �㭪��, �࠭�騩 �㭪��, ��������� ⥬������� �� �࠭��.
          // ��� ��।������ �㭪�� ��������� ������ �� �맮�� �㭪樨.
          
          // �������� �⠢�� �� �, �� ��।����� ��㬥�⮢ 4,
          // � ��������� ᨣ����� ������� ����ᮢ-�࠭���� �ᥣ� ���:
          // - double(Matrix const&, size_t)
          // - double(double)
          // �� ��㣨� ��ਠ��� �㦭� ��९��뢠�� �ணࠬ��.
          
          // �����頥��� ���� ��ꥪ�-�㭪��,
          // ��ࠬ��ਧ������ ���᫥��묨 ᨣ����ࠬ� �㭪権 � ���樠�����㥬�
          // ��।���묨 㪠��⥫ﬨ �� ������ ������ �࠭���� �㭪�஢.
          return BorderFunctors<typename Storage<Functors>::FunctionSingature...>(args...);
      }
}

template <class BordersCollection>
    class PlateHeatEquation {
      public:
        PlateHeatEquation(StartData const& data, BordersCollection functors)
        : functors(functors), data(data)
        // ������ � ������樨 ᫮� ���� ᫮� � ������묨 ��ࠬ��ࠬ�.
        , layers{{0, data.splits_y, data.splits_x, data.start_plate_temperature}}
        { }
        
        void generate_visualization_matlab(string filename, bool while_not_stationary,
                                           size_t count_layers,
                                           size_t delimiter_layers,
                                           double epsilon) {
            // �롨ࠥ� �� ����� ���� ������� ���᫥��� ����� ᫮�.
            if(while_not_stationary)
                do {
                    calculate_new_layer();
                    calculate_new_layer();
                } while(!isTemperatureStationary(epsilon));
            else
                for(size_t i = 0; i < count_layers - 1; ++i)
                        calculate_new_layer();
            
            // ������ 䠩�� �㭪権 ��� ���㠫���樨 १���� � MatLAB.
            MatlabVisualization(layers, data, delimiter_layers).generate(filename);
        }
      
      private:
        // ��� ��� ��ࠬ���� 蠡������� ����� �㭪�஢ BorderFunctions
        // ���᫨�� �஡�����筮 (���ॡ���� ��� ���� make-�㭪��),
        // � ����� ��������� ᤥ���� ��� ᠬ, � ��� �� �㤥� 㪠�뢠��
        // �, �� ⨯ ��ꥪ� functors - BorderFunctors<...>.
        // TODO: ������� ����� �㭪�஢ �� ��������� �� �㭪樮����,
        // TODO: ��� ����� �ਤ���� ��९����.
        BordersCollection const functors;
        StartData const data;
        Layers  layers;
      
      private:
        void calculate_new_layer() {
            // ��� ��砫� ������� ���� ᫮�.
            layers.push_back(
                    Layer{
                            layers.back().time_point + data.step_t,
                            data.splits_y,
                            data.splits_x
                    }
            );
            
            // �� ࠧ���⭮� �奬� ��⠥� ⥬������� "� �।���",
            // �㪮��������� ⥬�����ன �� �।��饬 ᫮�.
            auto& cur  = (layers.rbegin())    ->temperature;
            auto& prev = (layers.rbegin() + 1)->temperature;
            
            // ���祭�� splits_x/y �������筮 �易�� � ࠧ��ࠬ� ᫮�.
            for(size_t y = 1; y <= data.splits_y - 2; ++y)
                for(size_t x = 1; x <= data.splits_x - 2; ++x)
                    cur[y][x] = data.r * prev[y][x] +
                                data.rx * (prev[y][x-1]+ prev[y][x+1]) +
                                data.ry * (prev[y-1][x]+ prev[y+1][x]) ;
            
            // �����⠫� �।��� - ��� � � �࠭�栬 �����㯨����.
            calculate_borders();
        }
        void calculate_borders() {
            // ������뢠�� ⥬������� �� �࠭��� ����⨭� �१ �㭪���,
            // ����� ����� �㭪�ﬨ ����ᨬ��� ⥬������� �� �࠭��
            // �� ⥬�������, �� ����� � �।��� (��� �६���, �᫨ ���ॢ).
            auto&  cur_layer  = layers.back().temperature;
            double cur_time   = layers.back().time_point;
            using B = typename BordersCollection::Barriers;
            
            // ���砫� ����⠥� �࠭��� �� x_min, x_max
            // ��� ���孥� � ������ �࠭�� �� y_min � y_max.
            size_t x_min = 0;
            size_t x_max = data.splits_x - 1;
            for(size_t y = 1; y <= data.splits_y - 2; ++y) {
                cur_layer[y][x_max] = functors(B::RIGHT, cur_time, cur_layer, y);
                cur_layer[y][x_min] = functors(B::LEFT , cur_time, cur_layer, y);
            }
            
            // ������ ����⠥� �࠭��� �� y_min, y_max �� �ᥩ ����� x.
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
                
                // �����୮�� ����� �।���������� ��������묨.
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
    
            // �ࠢ������ �⪫������ ⥬������ �� ���� ᫮��.
            return abs(variation_up_mid - variation_mid_low) < epsilon;
        }
    };

namespace BorderFunctions {
  struct WrapperBase {
      // ��㦨� ��� �࠭���� ����ﭭ�� ��६����� �� �맮�� � �맮�� � �㭪���.
      WrapperBase(StartData const& data, double k): data(data), k(k) { }
    protected:
      StartData const data;
      double k; // �����樥��, ������� ��� �࠭��� �� �᫮���.
  };
  
  // �㭪樨, ���ᯥ稢��騥 ������ ⥬������� �� ������ �࠭��.
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
          // �ਭ﫨 ������ � ���᫨�� ᨣ������ �㭪樨, �࠭���� � ���.
          
          // ������ ���� �ﬡ��, ��뢠���� �㭪��-童�
          // � ���᫥��묨 ��ࠬ��ࠬ�.
          return [&functor, f] (Params... args) {
              // � ᠬ�� �ﬡ�� �ਭ����� ��ࠬ���� ��� �㭪樨-童��,
              // ������� �� ᨣ������, ��᫥ 祣� ��뢠�� �㭪��-童�,
              // �ᯮ���� ��।���� ��ࠬ����.
              return (functor.*f)(args...);
          };
      }
  
  template <class Functor, size_t option = 0, class... InitParams>
      auto LambdaGenerator (InitParams... init_args) {
          // - �㭪�� �ਭ����� 2 ��ࠬ���: ����室��� ����� ⨯� StartData
          // � �����樥��, ࠧ�� ��� ������ �� �࠭���� �㭪権.
          // - ��ࠬ��� 蠡���� option �㦥� ��� ᮧ����� ࠧ��� �㭪権 ���
          // ࠧ��� �࠭��, ����� ���ॢ�����
          // (�᫨ �࠭�� � ���ॢ�� ����� �����).
          
          
          // ��� ��� �㭪��-����⪠ ��� ����� �࠭��� �㤥� ⮫쪮 ����,
          // 㪠���, �� ��� �㤥� �࠭����� � ����᪮� ������ �����.
          // ����� ⮣�, ��ꥪ� �㤥� ����⠭��, ⠪ ��� �� ������� �࠭����
          // ��㬥�⮢, ����室���� ��� ���᫥��� ⥬�������.
          static const Functor border(init_args...);
          
          // ����뢠��, �� �⨬ ������� �ﬡ�� �� �������� �࠭���,
          // ����� �㤥� �ᯮ�짮���� ��।���� ��ࠬ����:
          // ᠬ ��ꥪ� ����� � 㪠��⥫� �� �㭪��-童�, ����室��� ���
          // ���᫥��� ᨣ������ �⮩ �㭪樨-童��.
          return GenerateLambda<Functor>(border, border.f);
      }
}
namespace BF = BorderFunctions;

int main() {
    // ���祭�� �����樥�⮢, �������� �� �᫮��� �����.
    double a = 0.01;
    double length_x = 1, length_y = 1;
    double start_plate_temperature  = 372;
    double environment_temperature  = 293;
    
    // ���祭��, �ᯮ��㥬� �� �襭�� �����.
    size_t splits_x = 50 , splits_y = 50;
    size_t count_layers = 3500;
    size_t delimiter_layers = 20; // ���⠥� ⮫쪮 ����� delimiter_layers ᫮�.
    bool   while_not_stationary = false; // ��⠥� �⪫������ ⥬������ ��� ᫮�?
    double epsilon = 1e-6; // �� ⠪�� ࠧ��� �⪫������ ⥬������ - ��⠭����.
    
    // ��ꥪ�, �।�⠢���騩 ᮡ�� ᮢ��㯭���� ������ �� �᫮���
    // � ������, ���᫥���� �� �� �᭮��.
    StartData start_data(a,
                         length_x, length_y,
                         splits_x, splits_y,
                         start_plate_temperature,
                         environment_temperature);
    
    // ����⪨ ��� �㭪�ﬨ.
    // ����� ⥬������� �� �࠭�� � ���������� ᫮� � 㧫� ��� �६���.
    // ����⪨ �࠭�� ���ﭨ� (�����, ����室��� ��� �� ࠡ���)
    // � ������ 㤮��� ���᫥��� ⥬������� �� �࠭��:
    // ��� ��।�� ��譨�, ����ﭭ�� ��㬥�⮢.
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