// Сделать БД и меню под неё

// БД:
// Фамилия, имя, отчество, год рождения, пол
// Задание: показать мужчин

// Меню:
// Добавление записи, редактирование записи,
// удаление записи, удаление всех записей, просмотр БД

// P.S. Проблемы этого проекта
// 1.  Внесение дополнительного модуля повлекло за собой создание идентичных
//     логически функций. Работу функции выполняют разную, но принципы работы
//     одинаковы. Следовало бы объединить их под одним началом,
//     но слишком много зависимостей нужно будет нарушить.
//     Фактически, нужно переписать полностью часть модуля Editor, а время поджимает.

// 2.  Find-функции надо бы разделить, но непонятно надо ли

// 3.  Editor зависит от внешних условий.
//     Хотя изначально не зависел: внешние шапки и внешние сообщения
//     портят картину кода.
//     Может, стоило бы сделать обработчик для всех внешних событий?

// 4.  Имена функций, выполняющих похожую работу,
//     рознятся от места к месту. Print, Show, See - ???

// 5.  Разделение на файлы не получилось. Очень много зависимостей.
//     Вдобавок, CLion не слишком лестно реагирует на синтаксис разделения.

// 6.  inline. Их много. Но, это помогает понять, какие функции
//     главные, а какие - вторичные.

// 7.  Добавление или удаление одного поля в БД потребует больших правок
//     из-за наличия разных ассоциативных констант, отвечающих за
//     расположение полей на экране и в массивах.
//     Нужно было создать только два ассоциативных перечисления,
//     которые бы удовлетворили все функции меню.

// 8.  Есть магические числа типа строк "мужчина", при замене которых
//     нужно будет просмотреть несколько мест, а не одно.
//     Препятствует интернационализации программы.

// 9.  В редакторе используется символьное редактирование пола персоны, хотя
//     переключатель выглядел бы красивее и работал бы быстрее.

// 10. Слишком много однотипных функций для перемещения курсора:
//     нужно было сделать общий обработчик, в который посылать возможные границы
//     и множители положения курсора. Так и короче, и понятнее.
//
//
//

// Понятые истины:
// 1. COORD cursor и консоль связаны только от программиста к консоли,
//    обратное не верно - консоль не изменяет cursor (lol).

// 2. Не зря специальные клавиши возвращают 2 кода.
//    Коды спецклавиш совпадают с обычными чаще, чем предполагалось.
// 3. Пересечение имён в неограниченных enum - страшная вещь.
//    В следующий раз нужно будет использовать enum class.
//    И выбирать имена констант короче.

// 4. Разделение ответственности функций способствует быстрому внесению
//    изменений и тестированию программы. Следует разбивать большие функции
//    на такие, которые бы требовали мало аргументов и выполняли много работы.

// 5. Слишком усердное разбиение логики на малкие функции может серьёзно
//    увеличить количество функций.
//    Лучше вызвать все необходимые функции заранее, а потом написать их.
//    Тогда будет исключён избыток функций.

// 6. Нельзя создавать обёртку для функций, которые выполняют противоположные
//    действия. (См. пункт 5).
#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
using namespace std;

enum Constants{
    maxLength = 40, // Максимум символов для ввода в редакторе
    maxCountPersons = 50,
    currentYear = 2017
};
constexpr int getCountDigits(int x, int n){
    return (x == 0 ? n : getCountDigits(x/10, n + 1));
}

struct Person {
    char surName[maxLength]    = {};
    char name[maxLength]       = {};
    char middleName[maxLength] = {};
    char birthday[maxLength]   = {};
    char gender[maxLength]     = {};
    
    // Персона может не иметь каких-то полей.
    // Об этом свидетельствует данный массив.
    
    // Нужен для поиска персоны по одному или нескольким
    // заданным значениям, и, как следствие,
    // нужен для вывода прочерка на месте отсутствующего поля.
    
    // [0] - Фамилия.
    // [1] - Имя.
    // [2] - Отчество.
    // [3] - Дата рождения.
    // [4] - Пол.
    bool isFieldAviable[5] = {};
} persons[maxCountPersons];
int countPersons = 0;

namespace Menu {
  bool myStrCmp(const char* s1, const char* s2){
      return strcmp(s1, s2) == 0;
  }
  short slen(const char* s){
      return static_cast<short> (strlen(s));
  }
  enum {
      
      successEdit,
      successAdd,
      
      successRemove,
      successRemoveDB,
      
      
      
      failedRemove,
      failedAdd,
      failedEdit,
      failedRemoveDB,
      
      
      failedSee,
      failedSearch,
      nothingHappens,
      
      canceledAdd,
      canceledEdit,
      canceledRemove,
      
      cancelSelectionShow
      
  } coreAnswer;
  
  COORD cursor;
  enum MoveMode{
      move,
      set
  };
  void moveCursor(const int x = 0, const int y = 0, MoveMode mode = move) {
      // Обёртка над функцией WinAPI.
      // При заданных x или y смещает курсор.
      
      // При вызове без аргументов просто устанавливает
      // новые координаты.
      
      // При вызове с аргументом set, а не move,
      // вместо перемещения на заданное количество
      // позиций производится установка курсора
      // на заданные позиции.
      
      static HANDLE consoleID = GetStdHandle(STD_OUTPUT_HANDLE);
      
      if(mode == move) {
          if (x != 0)
              cursor.X += short(x); // Столбцы
          
          if (y != 0)
              cursor.Y += short(y); // Строки
      }
      else {
          cursor.X = short(x);
          cursor.Y = short(y);
      }
      
      SetConsoleCursorPosition(consoleID, cursor);
  }
  
  enum Keys {
      Up = 72,
      Down = 80,
      Left = 75,
      Right = 77,
      Enter = 13,
      Backspace = 8,
      Esc = 27,
      Delete = 83
  };
  struct PressedKey {
      bool isSpecial = false;
      char code;
  };
  PressedKey whatPressed() {
      PressedKey key;
      // Нажали клавишу?
      key.code = char(_getch());
      
      // Это была специальная клавиша?
      if (_kbhit()) {
          key.isSpecial = true;
          key.code = char(_getch());
      }
      
      return key;
  }
  
  
  namespace Editor {
    // Editor - надстройка.
    // Editor совмещает общие процедуры редактирования полей
    // для добавления и изменения существующей персоны.
    struct RawPerson {
        // Сырая вводимая информация
        // [0] - Фамилия
        // [1] - Имя
        // [2] - Отчество
        // [3] - Год рождения
        // [4] - Пол
        char fields[5][maxLength] = {};
        
        // Пользователь захотел вернуться в главное меню
        // или же сохранил редактируемую персону?
        bool isSubmit = false;
    };
    enum EditFields {
        surName,
        name,
        middleName,
        birthday,
        gender
    };
    
    constexpr COORD defaultCoord = {27, 2}; // Позиция "фамилия"
    enum YEditFields {
        surNameY = defaultCoord.Y,
        nameY,
        middleNameY,
        birthdayY,
        genderY
    };
    enum YControlCoord {
        controlButtons = defaultCoord.Y + 8,
        errorCoordY = defaultCoord.Y + 6
    };
    enum XControlCoord {
        
        backCoordX   = defaultCoord.X - 8,
        submitCoordX = defaultCoord.X + 11,
        errorCoordX  = defaultCoord.X - 23
    };
    
    enum EditErrors {
        noEditErrors,
        submitError, // При сохранении персоны.
        tooLongField,
        wrongSymbol,
        comboWrong, // И символ запрещён, и места нет для вставки.
        nothingRemove, // Если невозможно удалить символ.
    } editError;
    enum ExternalErrors {
        noExternalErrors,
        similarPersonNotFound
    } externalError;
    
    inline void printEditMenu() {
        // Шапку рисует вызывающая процедура
        //      "                       ╔   Добавте персону   ╗                       "
        
        //      "                       ╔     Кого удаляем?    ╗                       "
        
        //      "                       ╔   Кого редактируем?  ╗                       "
        //      "                       ╔ Редактируйте персону ╗                       "
        
        //      "                       ╔   Критерии выборки   ╗                       "
        cout << "  ╔────────────────────┴──────────────────────┴──────────────────────╗" << endl;
        cout << "  │               Фамилия:                                           │" << endl;
        cout << "  │                   Имя:                                           │" << endl;
        cout << "  │              Отчество:                                           │" << endl;
        cout << "  │ Рождение (ДД.ММ.ГГГГ):                                           │" << endl;
        cout << "  │ Пол (мужчина|женщина):                                           │" << endl;
        cout << "  ╟──────────────────────────────────────────────────────────────────╢" << endl;
        cout << "  ╟                                                                  ╢" << endl;
        cout << "  ╟──────────────────────────────────────────────────────────────────╢" << endl;
        cout << "  ╟               [ ] Назад в меню   [ ] Подтвердить                 ╢" << endl;
        cout << "  ╚──────────────────────────────────────────────────────────────────╝" << endl;
        //      "             Ошибка. Одно из заполненных полей некорректно            "
        
        cursor = defaultCoord;
        moveCursor();
    }
    
    /* --- Тут перемещаем курсор по редактируемым полям и кнопкам редактора --- */
    inline void handling_ShiftUp_OnLastName() {
        // Переместим курсор на управляющие кнопки
        // и поставим метку положения.
        moveCursor(backCoordX, controlButtons, set);
        cout << 'x';
        moveCursor(); // Вернём в начальное положение, за x.
    }
    inline void handling_ShiftUp_OnMiddle(const RawPerson& rawP) {
        --cursor.Y;
        int nextField = cursor.Y - surNameY; // Получим индекс текущего raw-поля персоны.
        
        cursor.X = defaultCoord.X + slen(rawP.fields[nextField]);
        moveCursor();
    }
    inline void handling_ShiftUp_OnControl(const RawPerson& rawP) {
        // Удалим отметку на "назад" или "Подтвердить".
        // Т.к. курсор устанавливается на это поле
        // уже в нужной позиции, то просто сотрём символ:
        cout << ' ';
        
        // Переместимся на поле пола персоны,
        // на последнюю введённую букву.
        moveCursor(defaultCoord.X + slen(rawP.fields[gender]), genderY, set);
    }
    void shiftUp(const RawPerson& rawP) {
        if (cursor.Y == controlButtons) // Курсон на кнопке "назад" или "отмена"
            handling_ShiftUp_OnControl(rawP);
        
        else if (cursor.Y > surNameY) // Где-то в середине меню
            handling_ShiftUp_OnMiddle(rawP);
        
        else  // Точно на первом пункте
            handling_ShiftUp_OnLastName();
    }
    
    inline void handling_ShiftDown_OnMiddle(const RawPerson& rawP) {
        ++cursor.Y;
        
        int nextField = cursor.Y - surNameY; // Получим индекс текущего поля в массиве.
        cursor.X = defaultCoord.X + slen(rawP.fields[nextField]);
        moveCursor();
    }
    inline void handling_ShiftDown_OnPreControl() {
        // Переместим курсор и поставим метку положения курсора
        moveCursor(backCoordX, controlButtons, set);
        cout << 'x';
        moveCursor(); // Вернём курсор за символ x.
    }
    inline void handling_ShiftDownEnter_OnPreControl(){
        // Переместим курсор и поставим метку положения курсора
        moveCursor(submitCoordX, controlButtons, set);
        cout << 'x';
        moveCursor(); // Вернём курсор за символ x.
    }
    inline void handling_ShiftDown_OnControl() {
        // Удалим отметку на "назад" или "Подтвердить".
        // Т.к. курсор устанавливается на это поле
        // уже в нужной позиции, то просто сотрём символ:
        cout << ' ';
        
        cursor = defaultCoord;
        moveCursor();
    }
    void shiftDownEnter(const RawPerson& rawP){
        // Всё то же самое, что и в функции ниже.
        // Заменена только обработка preControl.
        
        if (cursor.Y < genderY) // Где-то в середине меню
            handling_ShiftDown_OnMiddle(rawP);
        
        else if (cursor.Y == genderY) // На последнем пункте
            handling_ShiftDownEnter_OnPreControl();
        
        else // Курсор установлен на "назад" или "отмена"
            handling_ShiftDown_OnControl();
    }
    void shiftDown(const RawPerson& rawP) {
        if (cursor.Y < genderY) // Где-то в середине меню
            handling_ShiftDown_OnMiddle(rawP);
        
        else if (cursor.Y == genderY) // На последнем пункте
            handling_ShiftDown_OnPreControl();
        
        else // Курсор установлен на "назад" или "отмена"
            handling_ShiftDown_OnControl();
    }
    
    inline void handling_MoveLeft_Field(const RawPerson& rawP) {
        if (defaultCoord.X < cursor.X) // Курсор в середине поля
            --cursor.X;
        
        else if (defaultCoord.X == cursor.X)  // Курсор в начале поля
            cursor.X = defaultCoord.X + slen(rawP.fields[cursor.Y - surNameY]);
        
        moveCursor();
    }
    inline void handling_MoveLeft_ControlButtons() {
        // Удалим старую метку курсора, поставим новую.
        cout << ' ';
        
        if (cursor.X == backCoordX) // Был на кнопке "назад"
            cursor.X = submitCoordX;
        else
            cursor.X = backCoordX;
        
        moveCursor(); // Переместим на новое место.
        cout << 'x';
        moveCursor(); // Вернём курсор обратно за символ x.
        
    }
    void moveLeft(const RawPerson& rawP) {
        if (cursor.Y < controlButtons) // Курсор где-то на редактируемом поле
            handling_MoveLeft_Field(rawP);
        
        else // Курсор на управляющих кнопках редактирования
            handling_MoveLeft_ControlButtons();
    }
    
    inline void handling_MoveRight_Field(const RawPerson& rawP) {
        if (defaultCoord.X + slen(rawP.fields[cursor.Y - surNameY]) > cursor.X)
            ++cursor.X; // Курсор был где-то в середине поля редактирования
        
        else // Курсор был в конце поля редактирования
            cursor.X = defaultCoord.X;
        
        moveCursor();
    }
    inline void handling_MoveRight_ControlButtons() {
        // Удалим старую отметку положения курсора и установим новую
        cout << ' ';
        
        if (cursor.X == submitCoordX) // Был на кнопке "Подтвердить"
            cursor.X = backCoordX;
        else
            cursor.X = submitCoordX;
        
        moveCursor(); // На новое место сдвинем.
        cout << 'x';
        moveCursor(); // Вернём курсор за символ x.
        
    }
    void moveRight(const RawPerson& rawP) {
        if (cursor.Y < controlButtons) // Курсор где-то на редактируемом поле
            handling_MoveRight_Field(rawP);
        
        else // Курсор на управляющих кнопках
            handling_MoveRight_ControlButtons();
        moveCursor();
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* ---           Удаление символов из полей            --- */
    inline void removeSymbol(char field[], int remSymPos){
        // Курсор находится "в" удаляемом символе, т.е. перед ним.
        for (int i = remSymPos; i < slen(field); ++i)
            field[i] = field[i + 1];
        
        // Покажем изменение строки.
        cout << &field[remSymPos];
        
        // Допишем в конце пробел, чтобы графически стереть оставшийся символ.
        cout << ' ';
        
        // Вернём курсор обратно, т.к. он сдвинулся после вывода пробела.
        moveCursor();
    }
    
    void handler_DeleteRemove(RawPerson& rawP){
        // Положение символа в массиве, который нужно удалить
        int remSymPos = cursor.X - defaultCoord.X;
        int curField = cursor.Y - surNameY;
        
        // После курсора должен быть хотя бы один символ.
        // Значит, позиция удаляемого символа не должна
        // ссылаться на последний элемент строки.
        if(remSymPos == slen(rawP.fields[curField]) || cursor.Y == controlButtons){
            editError = nothingRemove;
            return;
        }
        
        // Удалим и в консоли, и в массиве.
        removeSymbol(rawP.fields[curField], remSymPos);
    }
    void handler_BackspaceRemove(RawPerson& rawP){
        // Получим положение символа в массиве.
        int remSymPos = cursor.X - defaultCoord.X - 1;
        
        // Перед курсором должен быть хотя бы один символ.
        // Он не может находиться в начале поля.
        // Значит, если индекс удаляемого символа -1, то это ошибка.
        int curField = cursor.Y - surNameY;
        if(remSymPos == -1 || cursor.Y == controlButtons){
            editError = nothingRemove;
            return;
        }
        
        // Т.к. курсор сейчас после удаляемого символа,
        moveCursor(-1, 0); // переместим его на удаляемый символ.
        
        // Удалим символ и в консоли, и в массиве.
        removeSymbol(rawP.fields[curField], remSymPos);
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    /* ---           Добавление символов в поля            --- */
    void insertSym(char field[], int symPos, char sym) {
        // Перед вызовом этой функции нужно проверить
        // возможность вставки символа.
        
        // Отодвинем символы вправо.
        for (int i = slen(field); i >= symPos; --i)
            field[i + 1] = field[i];
        
        // Вставим символ.
        field[symPos] = sym;
        
        // Выведем символы после вставленного включительно.
        cout << field + symPos;
        
        moveCursor(1, 0); // Переместим курсор после вставленного символа.
    }
    
    inline bool isCorrectSymbol(char sym) {
        return isalpha(sym) || isdigit(sym) ||
               ('А' <= sym && sym <= 'я')   ||
               sym == 'Ё' || sym == 'ё'   ||
               sym == '.' || sym == '-'   ||
               sym == ' ';
    }
    inline bool isSpaceFree(char field[], int rightLength){
        return slen(field) < rightLength;
    }
    bool setInsertErrors(RawPerson& rawP, char sym, int rightBorder){
        int curField = cursor.Y - surNameY; // Индекс поля при текущем положении курсора.
        
        if (!isCorrectSymbol(sym) && !isSpaceFree(rawP.fields[curField], rightBorder)){
            editError = comboWrong;
            return true;
        }
        if(!isCorrectSymbol(sym)) {
            editError = wrongSymbol;
            return true;
        }
        if(!isSpaceFree(rawP.fields[curField], rightBorder)) {
            editError = tooLongField;
            return true;
        }
        return false;
    }
    
    void handler_InsertSym(RawPerson& rawP, char sym){
        // Текущее положение курсора - место вставки символа в массив.
        int symPos = cursor.X - defaultCoord.X;
        int curField = cursor.Y - defaultCoord.Y;
        
        // Действия вставки:
        // 1) Проверим, корректный ли символ.
        // 2) Проверим, что место для вставки ещё есть.
        if(setInsertErrors(rawP, sym, maxLength))
            return; // Есть ошибки? Отменим вставку.
        
        // 3) Если всё хорошо, то вставим символ сначала
        //    в массив, а потом часть массива, начиная с
        //    данного символа, распечатаем.
        insertSym(rawP.fields[curField], symPos, sym);
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* --- Тут обрабатываем нажатие Enter в полях редактора и на кнопках --- */
    inline bool checkDate(int day, int month, int year) {
        // TODO: Научить работать с текущей датой.
        return 1 <= day && day <= 31 &&
               1 <= month && month <= 12 &&
               1800 <= year && year <= currentYear;
    }
    inline bool checkGender(const char* gender) {
        return myStrCmp(gender, "мужчина") || myStrCmp(gender, "женщина");
    }
    bool isCorrectInfo(RawPerson& rawP) {
        int day, month, year;
        int numbersInDate = sscanf(rawP.fields[birthday], "%d.%d.%d", &day, &month, &year);
        
        // Оставляем возможность не заполнять любое поле
        
        // Если дата не введена (numbersInDate == 0), значит,
        // она будет пропущена при создании персоны.
        if(slen(rawP.fields[birthday]) > 0 || numbersInDate == 3)
            if (!checkDate(day, month, year))
                return false; // Ошибка в синтаксисе даты.
        
        if(slen(rawP.fields[gender]) != 0)
            if (!checkGender(rawP.fields[gender]))
                return false;
        
        return true; // Раз уж все поля корректны.
    }
    
    bool handler_Enter(RawPerson& rawP){
        // Определяет, сохранять ли объект.
        // Также, интуитивно, нажатие Enter должно провоцировать
        // переход на следующее поле; при "подтверждении"
        // ввода на последнем поле, нужно перебросить пользователя
        // на кнопку сохранения персоны.
        
        // Функция определит, требуется ли продолжать редактирование персоны.
        bool isEdit;
        if (cursor.Y == controlButtons)
            switch (cursor.X) {
                case backCoordX :
                    rawP.isSubmit = false;
                    isEdit = false;
                    break;
                
                case submitCoordX :
                    if (isCorrectInfo(rawP)) {
                        rawP.isSubmit = true;;
                        isEdit = false;
                    } else {
                        editError = submitError;;
                        isEdit = true;
                    }
                    break;
                
                default:
                    throw(__LINE__); // Не должно использоваться
            }
        else {
            shiftDownEnter(rawP);
            
            isEdit = true;
        }
        
        return isEdit;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* --- Главный обработчик действий пользователя в редакторе  --- */
    inline void printDoneData(const RawPerson& rawP){
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        for(int i = surName; i <= gender; ++i) {
            cout << rawP.fields[i];
            moveCursor(0, 1);
        }
        // Переместим курсор в конец первого поля.
        moveCursor(defaultCoord.X + slen(rawP.fields[surName]), defaultCoord.Y, set);
    }
    
    inline void setExternalErrors(){{}
        if(externalError != noExternalErrors) {
            COORD tempCoord = cursor;
            
            moveCursor(errorCoordX, errorCoordY, set);
            switch (externalError) {
                case similarPersonNotFound          :
                    cout << "     Ошибка. Персоны с подобными данными не существует в БД     ";
                    break;
                default :
                    throw(__LINE__); // Не должно использоваться
            }
            moveCursor(tempCoord.X, tempCoord.Y, set);
        }
    }
    inline void setErrors(){
        
        if(editError != EditErrors::noEditErrors){
            COORD tempCoord = cursor;
            moveCursor(errorCoordX, errorCoordY, set);
            
            switch(editError) {
                case submitError                  :
                    cout << "   Ошибка. Одно или несколько из заполненных полей некорректно  ";
                    break;
                case tooLongField                 :
                    cout << "           Ошибка. Введённая информация слишком длинна          ";
                    break;
                case wrongSymbol                  :
                    cout << "              Ошибка. Недопустимый символ для ввода             ";
                    break;
                case comboWrong :
                    cout << "   Ошибка. Недопустимый символ для ввода; нет места для ввода   ";
                    break;
                case nothingRemove                :
                    cout << "                   Ошибка. Нечего тут удалять                   ";
                    break;
                default                           :
                    throw(__LINE__); // Не должно использоваться
            }
            
            moveCursor(tempCoord.X, tempCoord.Y, set);
        }
    }
    inline void removeErrors() {
        // Уберём ошибку при следующем нажатии кнопки
        if(editError != noEditErrors || externalError != noExternalErrors) {
            COORD tempCoord = cursor;
            
            moveCursor(errorCoordX, errorCoordY, set); // Очищаем всё поле ошибок редактора
            cout << "                                                                " << endl;
            moveCursor(tempCoord.X, tempCoord.Y, set);
            
            editError = noEditErrors;
            externalError = noExternalErrors;
        }
    }
    void core_EditPerson(RawPerson& rawP) {
        printEditMenu();
        // Данные вводятся во временный объект побуквенно,
        // Поэтому больше возможностей для редактирования в любой момент ввода.
        // Готовые пол и возраст сохраняются при корректности.
        
        // Можно перемещать курсор по редактируемому полю.
        // Можно перемещать курсор на разные поля,
        // при этом введённое сохраняется.
        // Можно вставлять/удалять буквы.
        
        // Если на вход подали уже заполненную персону, выведем её поля.
        if(rawP.isSubmit)
            printDoneData(rawP);
        
        // Главный обработчик редактирования.
        bool isEdit = true;
        while (isEdit) {
            
            setExternalErrors();
            PressedKey key = whatPressed();
            removeErrors();
            
            if(key.isSpecial)
                switch (key.code) {
                    case Up     : shiftUp(rawP);             break;
                    case Down   : shiftDown(rawP);           break;
                    case Left   : moveLeft(rawP);            break;
                    case Right  : moveRight(rawP);           break;
                    case Delete : handler_DeleteRemove(rawP);break;
                    default     : break;
                }
            else
                switch(key.code){
                    case Enter     : isEdit = handler_Enter(rawP);   break;
                    case Backspace : handler_BackspaceRemove(rawP);  break;
                    default        : // Если не нажата ни одна управляющая клавиша
                        handler_InsertSym(rawP, key.code);
                        break;
                }
            
            setErrors();
            
        }
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* ---     Дополнительные функции, использующие редактор     --- */
    RawPerson toRaw(int index){
        RawPerson rawP;
        if(slen(persons[index].surName) > 0)
            strcpy(rawP.fields[0], persons[index].surName);
        if(slen(persons[index].name) > 0)
            strcpy(rawP.fields[1], persons[index].name);
        if(slen(persons[index].middleName) > 0)
            strcpy(rawP.fields[2], persons[index].middleName);
        if(slen(persons[index].birthday) > 0)
            strcpy(rawP.fields[3], persons[index].birthday);
        if(slen(persons[index].gender) > 0)
            strcpy(rawP.fields[4], persons[index].gender);
        rawP.isSubmit = true;
        return rawP;
    }
    Person toPerson(RawPerson& rawP){
        Person person;
        if(slen(rawP.fields[0])>0){
            strcpy(person.surName,   rawP.fields[0]);
            person.isFieldAviable[0] = true;
        }
        if(slen(rawP.fields[1])>0){
            strcpy(person.name,      rawP.fields[1]);
            person.isFieldAviable[1] = true;
        }
        if(slen(rawP.fields[2])>0){
            strcpy(person.middleName,rawP.fields[2]);
            person.isFieldAviable[2] = true;
        }
        if(slen(rawP.fields[3])>0){
            strcpy(person.birthday,  rawP.fields[3]);
            person.isFieldAviable[3] = true;
        }
        if(slen(rawP.fields[4])>0){
            strcpy(person.gender,    rawP.fields[4]);
            person.isFieldAviable[4] = true;
        }
        return person;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
  }
  namespace Find {
    using Editor::RawPerson;
    // "Внутренние" функции поиска одной персоны из нескольких похожих
    
    /* --- Тут находим индексы персон, идентичных данной --- */
    inline bool checkSimilar(const Person& person, const RawPerson& rawP) {
        // Проверим, идентична ли искомая личность данной
        // Вернём false, как только хотя бы одно из заполненных полей
        // не будет соответствовать существующему объекту
        
        if (slen(rawP.fields[Editor::surName]) != 0)
            if (!myStrCmp(person.surName, rawP.fields[Editor::surName]))
                return false;
        
        if (slen(rawP.fields[Editor::name]) != 0)
            if (!myStrCmp(person.name, rawP.fields[Editor::name]))
                return false;
        
        if (slen(rawP.fields[Editor::middleName]) != 0)
            if (!myStrCmp(person.middleName, rawP.fields[Editor::middleName]))
                return false;
        
        if (slen(rawP.fields[Editor::birthday]) != 0)
            if (!myStrCmp(person.birthday, rawP.fields[Editor::birthday]))
                return false;
        
        if (slen(rawP.fields[Editor::gender]) != 0)
            if (!myStrCmp(person.gender, rawP.fields[Editor::gender]))
                return false;
        
        return true;
    }
    
    struct Similar {
        int number[maxCountPersons];
        int n;
    };
    Similar findSimilar(const RawPerson& rawP) {
        Similar similar;
        similar.n = 0;
        
        // Пройдёмся по всем существующим персонам и сравним их с данной
        for (int i = 0; i < countPersons; ++i)
            if (checkSimilar(persons[i], rawP))
                similar.number[similar.n++] = i;
        
        return similar;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* --- Тут красиво выводим список идентичных персон --- */
    inline void printTablePersonsCap(){
        cout << "  ╔─────┬───────────────┬───────────────┬────────────────────┬──────────┬─────╗" << endl
             << "  │  #  │    Фамилия    │      Имя      │      Отчество      │  Рождён  │ Пол │" << endl
             << "  ╟─────┼───────────────┼───────────────┼────────────────────┼──────────┼─────╢" << endl;
    }
    inline void printSeparatorLine(){
        cout << "  ╟─────┼───────────────┼───────────────┼────────────────────┼──────────┼─────╢" << endl;
    }
    inline void printEndTable(){
        cout << "  ╚─────┴───────────────┴───────────────┴────────────────────┴──────────┴─────╝" << endl;
    }
    
    enum LimitsField {
        maxSurNameLength = 15,
        maxNameLength = 15,
        maxMiddleNameLength = 20,
        maxBirthdayLength = 10,
        maxGenderLength = 5
    };
    string reformName(const char* name, LimitsField limit){
        // Не помещается имя в поле? Исправим ситуацию.
        string str = name;
        
        if(str.size() > limit) {
            str[limit - 0] = '\0';
            str[limit - 1] = '.';
            str[limit - 2] = '.';
            str[limit - 3] = '.';
        }
        else // Дополним пробелами поле для корректного отображения
            while(str.size() < limit)
                str += ' ';
        
        return str.c_str();
    }
    string reformDate(const char date[]){
        int day, month, year;
        sscanf(date, "%d.%d.%d", &day, &month, &year);
        
        // Не хватает ведущего нуля? Добавим, для красоты.
        auto normalizeNumber = [](int number) -> string {
            string str = "  ";
            if (number < 10) {
                str[0] = '0';
                itoa(number, &str[1], 10);
            }
            else
                itoa(number, &str[0], 10);
            
            return str;
        };
        
        string fullYear;
        fullYear += normalizeNumber(day); fullYear += '.';
        fullYear += normalizeNumber(month); fullYear += '.';
        char buffer[5];
        fullYear += itoa(year, buffer, 10);
        
        return fullYear;
        
    }
    string reformGender(const char gender[]){
        return (myStrCmp(gender, "мужчина") ? "  М  " : "  Ж  ");
    }
    string centerDash(LimitsField limit){
        // В зависимости от чётности длины поля,
        // отдаём либо одно, либо два прочерка.
        string str;
        
        if(limit%2 == 0){
            for(int i = 0; i < limit/2 - 1; ++i)
                str += ' ';
            str += "──";
            for(int i = limit/2 + 1; i < limit; ++i)
                str += ' ';
        }
        else {
            
            for(int i = 0; i < limit/2 ; ++i)
                str += ' ';
            str += "─";
            for(int i = limit/2 + 1; i < limit; ++i)
                str += ' ';
        }
        
        return str;
    }
    void printPerson(Person& curPerson, int index){
        // FIXME: Сложная функция.
        // Вывод существующих полей персоны.
        // Отсутствующие поля заменяем прочерками и центрируем их.
        
        static_assert(getCountDigits(maxCountPersons, 0) <= 3, "Table persons will be broken");
        printf("  │ %3d │", index);
        
        if(curPerson.isFieldAviable[Editor::surName])
            cout << reformName(curPerson.surName, maxSurNameLength);
        else cout << centerDash(maxSurNameLength);
        cout << '│';
        
        if (curPerson.isFieldAviable[Editor::name])
            cout << reformName(curPerson.name, maxNameLength);
        else cout << centerDash(maxNameLength);
        cout << '│';
        
        if (curPerson.isFieldAviable[Editor::middleName])
            cout << reformName(curPerson.middleName, maxMiddleNameLength);
        else cout << centerDash(maxMiddleNameLength);
        cout << '│';
        
        if(curPerson.isFieldAviable[Editor::birthday])
            cout << reformDate(curPerson.birthday);
        else cout << centerDash(maxBirthdayLength);
        cout << '│';
        
        if(curPerson.isFieldAviable[Editor::gender])
            cout << reformGender(curPerson.gender);
        else cout << centerDash(maxGenderLength);
        cout << '│' << endl;
    }
    
    void selectSimilarPersons_ToPrint (Similar& similar){
        printTablePersonsCap();
        
        for(int i = 0; i < similar.n; ++i){
            Person& curPerson = persons[similar.number[i]];
            printPerson(curPerson, similar.number[i]);
            if(i + 1 != similar.n) // Чтобы таблица красиво заканчивалась
                printSeparatorLine();
        }
        
        printEndTable();
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* --- Тут даём пользователю выбрать одну из похожих персон --- */
    static const COORD defaultCoord = {0, 6};
    inline void printSimilarPersonsCap(){
        cout << "                              Похожие персоны:                                " << endl;
    }
    
    inline void printCursor(){
        cout << "->"; // Объект cursor не менялся.
        
        // Но графически его положение изменилось, вернём обратно.
        moveCursor();
    }
    inline void removeCursor(){
        // Каретка уже в нужном положении для стирания курсора
        cout << "  "; // Объект cursor не менялся.
        
        // Но графически его положение изменилось, вернём обратно.
        moveCursor();
    }
    
    inline void moveUp(Similar& similar){
        removeCursor();
        
        // Определяется граничная координата,
        // на которой может быть курсор
        short downBorder = short(defaultCoord.Y + similar.n*2 - 2);
        
        if(cursor.Y > defaultCoord.Y)
            moveCursor(0, -2);
        else
            moveCursor(defaultCoord.X, downBorder, set);
        
        printCursor();
    }
    inline void moveDown(Similar& similar){
        removeCursor();
        
        // Определяется граничная координата,
        // на которой может быть курсор
        short downBorder = short(defaultCoord.Y + similar.n*2 - 2);
        
        if(cursor.Y < downBorder)
            moveCursor(0, 2);
        else
            moveCursor(defaultCoord.X, defaultCoord.Y, set);
        
        printCursor();
    }
    
    inline int handlingEnter(Similar& similar){
        // Возвращает индекс выбранной персоны.
        
        // /2, т.к. персоны располагаются через разделитель.
        return similar.number[(cursor.Y - defaultCoord.Y) / 2];
    }
    
    enum UserChoice {
        cancelChoice = -1,
    };
    int core_RefineChoice(Similar &similar){
        printSimilarPersonsCap(); // Описание таблицы.
        
        selectSimilarPersons_ToPrint(similar);
        
        // Установим курсор на первое имя таблицы.
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        printCursor();
        
        while(true){
            PressedKey key = whatPressed();
            
            // Тут нет совпадений между кодами специальных и обычных клавиш.
            switch(key.code){
                case Up    : moveUp(similar);        break;
                case Down  : moveDown(similar);      break;
                case Enter : return handlingEnter(similar);
                case Esc   : return cancelChoice;
                default    : break;
            }
            
        }
        
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
  }
  
  namespace Add {
    inline void printAddMenu() {
        system("CLS");
        cout << "                       ╔   Добавте  персону   ╗                       " << endl;
    }
    
    inline Editor::RawPerson getRawPerson(){
        Editor::RawPerson rawP;
        Editor::core_EditPerson(rawP);
        
        return rawP;
    }
    void core_addPerson() {
        if(countPersons == maxCountPersons){
            coreAnswer = failedAdd;
            return;
        }
        
        printAddMenu();
        Editor::RawPerson rawP = getRawPerson();
        
        // Подтвердил ли пользователь, что хочет
        // добавить персону в БД или захотел вернуться обратно в меню?
        if (rawP.isSubmit) {
            persons[countPersons++] = Editor::toPerson(rawP);
            coreAnswer = successAdd;
        }
        else
            coreAnswer = canceledAdd;
    }
  }
  namespace Remove {
    using Editor::RawPerson;
    /* --- Функции удаления персоны, указанной пользователем --- */
    
    inline void printEnterRemoveCap() {
        system("CLS");
        cout << "                       ╔     Кого удаляем?    ╗                       " << endl;
    }
    inline void printChoiceSimilarRemoveCap(){
        system("CLS");
        cout << "                        Какую персону следует удалить?                        " << endl << endl;
    }
    
    inline void removePerson(int whoRemove) {
        // Надвинем всем персон ниже данной на неё.
        for(int i = whoRemove; i < countPersons-1; ++i)
            persons[i] = persons[i+1];
        
        --countPersons;
    }
    bool core_removePerson (int) {
        if(countPersons == 0){
            coreAnswer = failedRemove;
            return true; // В меню выбора метода выбора
        }
        
        // Принцип работы:
        //
        // I.   Получить данные об искомой персоне для удаления
        //      от пользователя.
        //    * При отказе вводить данные, завершим процедуру.
        //
        // II.  Получить количество похожих персон
        //      1) При отсутствии похожих персон,
        //         покажем оповестим об этом в редакторе,
        //         перейдём к пункту I.
        //      *  При отказе от выбора, вернём пользователя
        //         на пункт I.
        //      2) Если персона одна, запомним её индекс.
        //      3) Если похожих персон более одной,
        //         дадим пользователю выбрать нужную.
        //
        // III. Удалить персону, вернуться в главное меню.
        
        int whoRemove;
        
        while(true){
            // I.
            printEnterRemoveCap();
            Editor::RawPerson rawP = Add::getRawPerson();
            
            if (rawP.isSubmit) {
                // II.
                Find::Similar similar = Find::findSimilar(rawP);
                
                // II. 1)
                if(similar.n == 0) {
                    Editor::externalError = Editor::ExternalErrors::similarPersonNotFound;
                    continue; // Запросим корректные данные ещё раз.
                }
                
                // II. 2)
                if(similar.n == 1) {
                    whoRemove = similar.number[0];
                    break; // Перейдём к шагу III.
                }
                    
                    // II. 3)
                else if(similar.n > 1){
                    // Покажем пользователю новое меню
                    printChoiceSimilarRemoveCap();
                    // Получим ответ от пользователя
                    whoRemove = Find::core_RefineChoice(similar);
                    
                    // II. 3) *
                    if(whoRemove == Find::UserChoice::cancelChoice)
                        continue; // Запросим данные ещё раз.
                    else
                        break; // В главное меню.
                }
                
                throw(__LINE__); // Не должно использоваться
            }
            else {
                // I. *
                coreAnswer = canceledRemove;
                return true; // В главное меню, отмена выбора метода выбора.
            }
        }
        
        // III.
        removePerson(whoRemove);
        coreAnswer = successRemove;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* --- Функции для удаления персоны через её индекс --- */
    bool handler_IndexRemove(int index){
        // Продолжить выбор метода выбора или выбор персоны уже сделан?
        if(index == -1)
            return true; // Продолжить выбор метода выбора.
        
        removePerson(index);
        coreAnswer = successRemove;
        
        return false; // В главное меню вернёмся.
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* --- Функции для выбора метода выбора удаления персоны --- */
    inline void printSelectChoiceRemoveModeCap(){
        moveCursor(-1, -2); // От defaultCoord в шапку.
        cout << "  Способ удаления персоны?  ";
        moveCursor(1, 2); // Обратно в defaultCoord.
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
  }
  namespace Change {
    /* Функции для поиска персоны через её поле */
    inline void printEnterDataCap() {
        system("CLS");
        cout << "                       ╔   Кого редактируем?  ╗                       " << endl;
    }
    inline void printSimilarEditCap(){
        system("CLS");
        cout << "              Какую персону из этих редактируем? [Esc: вернуться]              "   << endl << endl;
    }
    inline void printEditDataCap() {
        system("CLS");
        cout << "                       ╔ Редактируйте персону ╗                       " << endl;
    }
    
    bool core_FieldEdit(int){
        
        // Принцип работы:
        //
        // I.   Получить данные об искомой персоне для редактирования
        //      от пользователя.
        //    * При отказе вводить данные, завершим процедуру.
        //
        // II.  Получить количество похожих персон
        //      1) При отсутствии похожих персон,
        //         покажем оповестим об этом в редакторе,
        //         перейдём к пункту I.
        //      *  При отказе от выбора, перейдём обратно в главное меню.
        //      2) Если персона одна, запомним её индекс.
        //      3) Если похожих персон более одной,
        //         дадим пользователю выбрать нужную.
        //
        // III. Покажем меню редактирования выбранной персоны.
        //      Саму персону занесём во временную, превратив в "сырую".
        //    * При отказе пользователя от редактирования персоны,
        //      вернёмся к пункту I.
        //
        // IV.  Сохранение персоны осуществится по появлению флага isSubmit,
        //      который установит модуль Editor::cookData.
        //    * При отказе от сохранения изменений в существующей персоне,
        //      выйдем в главное меню.
        
        int whoEdit;
        
        while(true){
            // I.
            printEnterDataCap();
            Editor::RawPerson rawP = Add::getRawPerson();
            
            if (rawP.isSubmit) {
                // II.
                Find::Similar similar = Find::findSimilar(rawP);
                
                
                // II. 1)
                if(similar.n == 0) {
                    Editor::externalError = Editor::ExternalErrors::similarPersonNotFound;
                    continue; // Запросим корректные данные ещё раз.
                }
                    
                    // II. 2)
                else if(similar.n == 1)
                    whoEdit = similar.number[0];
                    // Перейдём к шагу III.
                    
                    // II. 3)
                else if(similar.n > 1){
                    // Покажем пользователю меню выбора похожих персон.
                    printSimilarEditCap();
                    // Получим ответ от пользователя.
                    whoEdit = Find::core_RefineChoice(similar);
                    
                    // II. 3) *
                    if(whoEdit == Find::UserChoice::cancelChoice) {
                        coreAnswer = canceledEdit;
                        return false; // Вернёмся в меню.
                    }
                    // else // Перейдём к шагу III.
                }
                
                if(whoEdit < 0)
                    throw(__LINE__); // Не должно выполниться.
                // III.
                rawP = Editor::toRaw(whoEdit);
                printEditDataCap();
                Editor::core_EditPerson(rawP);
                
                // IV.
                if(rawP.isSubmit) {
                    persons[whoEdit] = Editor::toPerson(rawP);
                    coreAnswer = successEdit;
                    return false; // Работа функции закончена, в главное меню.
                }
                else { // IV. *
                    coreAnswer = canceledEdit;
                    return false; // В главное меню.
                }
                
            }
            else {
                // I. *
                coreAnswer = canceledEdit;
                return false; // В главное меню.
            }
        }
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* Функции для редактирования персоны через её индекс */
    bool handler_IndexEdit(int index){
        // Продолжить выбор метода выбора или выбор персоны уже сделан?
        if(index == -1)
            return true; // Продолжить выбор метода выбора.
        
        Editor::RawPerson rawP = Editor::toRaw(index);
        printEditDataCap();
        // Раз выбор сделан, покажем меню редактирования
        // выбранной персоны.
        Editor::core_EditPerson(rawP);
        
        if(rawP.isSubmit){
            persons[index] = Editor::toPerson(rawP);
            coreAnswer = successEdit;
        }
        else coreAnswer = canceledEdit;
        
        return false; // В главное меню вернёмся.
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* Меню с выбором режима выбора персоны */
    constexpr COORD defaultCoord = {27, 3}; // "Поля персоны"
    
    inline void printCursor(){
        cout << "->"; // COORD cursor не изменился.
        moveCursor(); // В default-положение.
    }
    inline void removeCursor(){
        cout << "  "; // COORD cursor не изменился.
        moveCursor(); // Вернём в старое положение.
    }
    
    inline void printSelectChoiceEditModeCap(){
        moveCursor(-1, -2); // От defaultCoord в шапку.
        cout << "   Способ выбора персоны?   ";
        moveCursor(1, 2); // Обратно в defaultCoord.
    }
    inline void updateMenuItems(){
        moveCursor(-1, 0); // Сдвинемся на место левой скобки.
        
        // И отрисуем все пункты нового меню.
        cout << "[  ] Поля персоны            ";
        
        moveCursor(0, 1);
        // HINT:      Изменить данные персоны
        cout << "[  ] Индекс персоны          ";
        
        moveCursor(0, 1);
        cout << "[  ] В главное меню          ";
        
        // Теперь меню не "главное", удалим его пункты.
        moveCursor(0, 1);
        cout << "                             ";
        moveCursor(0, 1);
        cout << "                             ";
        moveCursor(0, 1);
        cout << "                             ";
        moveCursor(0, 1);
        cout << "                             ";
        
        cursor = defaultCoord;
        moveCursor();
        printCursor();
    }
    
    enum ModeMenuItems {
        fieldChoice = defaultCoord.Y,
        indexChoice,
        backChoice
    };
    inline void moveUp(){
        removeCursor();
        
        if(cursor.Y > fieldChoice)
            moveCursor(0, -1);
        else
            moveCursor(0, 2);
        
        printCursor();
    }
    inline void moveDown(){
        removeCursor();
        
        
        if(cursor.Y < backChoice)
            moveCursor(0, 1);
        else
            moveCursor(0, -2);
        
        printCursor();
    }
    
    
    namespace MiniEditor { // NOTE: Написано только ради сохранения единого интерфейса.
      // WHITE: На самом деле тут дикий ужас и куча зависимостей.
      // Тут написан обработчик ввода пользователем индекса персоны.
      // FIXME: Это - аналогия Editor, только в одном поле.
      
      // NOTE: Это - чтобы меньше нужно было менять при изменении количества персон.
      static_assert(getCountDigits(maxCountPersons, 0) <= 3, "Table persons will be broken");
      char index[getCountDigits(maxCountPersons, 0)+1] = {};
      constexpr COORD defaultCoord = {short(Change::defaultCoord.X + 4 + 16),
                                      short(Change::defaultCoord.Y + 1)};
      
      inline void printInviteToEnterIndex(){
          // HINT: [  ] Индекс персоны
          // HINT:  ^
          moveCursor(4, 0); // Двигаемся от стрелочки слева.
          cout << "Введите индекс: "; // cursor всё ещё находится на +4 позиции от стрелочки.
          cursor = defaultCoord; // Закрепим новое положение.
      }
      inline void handler_Back (){
          // Переместим курсор за текущую надпись, перепишем её на предыдущую.
          moveCursor(- slen(index) - 16, 0);
          cout << "Индекс персоны          ";
          
          moveCursor(-4, 0); // Вернём курсор обратно на левую стрелочку.
          removeCursor(); // И удалим его следом.
          
          // Очистим введённый индекс
          for(auto& c: index)
              c = '\0';
      }
      
      inline void moveLeft(){
          // Перемещение курсора влево со скачком вправо.
          if(defaultCoord.X < cursor.X)
              moveCursor(-1, 0);
          else
              moveCursor(slen(index), 0);
      }
      inline void moveRight(){
          // Перемещение курсора вправо со скачком влево.
          if(cursor.X < defaultCoord.X + slen(index))
              moveCursor(1, 0);
          else
              moveCursor(-slen(index), 0);
      }
      
      enum {
          cancelEnter = -1,
          
          nothingHappens,
          
          errorInsert,
          errorRemove,
          errorEnter,
          
          messagesFieldY = 11
      } editErrors;
      void handler_DeleteRemove(){
          // Положение символа в массиве, который нужно удалить
          int remSymPos = cursor.X - defaultCoord.X;
          
          // После курсора должен быть хотя бы один символ.
          // Значит, позиция удаляемого символа не должна
          // ссылаться на последний элемент строки.
          if(remSymPos == slen(index)){
              editErrors = errorRemove;
              return;
          }
          
          // Удалим и в консоли, и в массиве.
          Editor::removeSymbol(index, remSymPos);
      }
      void handler_BackspaceRemove(){
          // Получим положение символа в массиве.
          int remSymPos = cursor.X - defaultCoord.X - 1;
          
          // Перед курсором должен быть хотя бы один символ.
          // Он не может находиться в начале поля.
          // Значит, если индекс удаляемого символа -1, то это ошибка.
          if(remSymPos == -1){
              editErrors = errorRemove;
              return;
          }
          
          // Т.к. курсор сейчас после удаляемого символа,
          moveCursor(-1, 0); // переместим его на удаляемый символ.
          
          // Удалим символ и в консоли, и в массиве.
          Editor::removeSymbol(index, remSymPos);
      }
      void handler_InsertSym(char sym){
          // Текущее положение курсора - место вставки символа в массив.
          int symPos = cursor.X - defaultCoord.X;
          
          // Действия вставки:
          // 1) Проверим, корректный ли символ.
          // 2) Проверим, что место для вставки ещё есть.
          if(!isdigit(sym) || slen(index)+1 > getCountDigits(maxCountPersons, 0)) {
              editErrors = errorInsert;
              return; // Есть ошибки? Отменим вставку.
          }
          
          // 3) Проверка выше успешна? Вставим символ сначала
          //    в массив, а потом часть массива, начиная с
          //    данного символа, распечатаем.
          Editor::insertSym(index, symPos, sym);
      }
      
      inline bool isIndexCorrect(){
          if(atoi(index) < countPersons)
              return true;
          else {
              editErrors = errorEnter;
              return false;
          }
      }
      
      inline void setError(){
          COORD tempCoord = cursor;
          
          moveCursor(Change::defaultCoord.X-1, messagesFieldY, set);
          if(editErrors != nothingHappens)
              switch(editErrors){
                  case errorInsert : cout << "Индекс не может быть больше "; break;
                  case errorEnter  : cout << "Введённый индекс некорректен"; break;
                  case errorRemove : cout << "  Невозможно удалить символ "; break;
                  default          : throw(__LINE__); // Не должно исполниться.
              }
          
          moveCursor(tempCoord.X, tempCoord.Y, set);
          
      }
      inline void removeError(){
          if(editErrors != nothingHappens) {
              COORD tempCoord = cursor;
              
              moveCursor(Change::defaultCoord.X-1, messagesFieldY, set);
              cout << "                            ";
              moveCursor(tempCoord.X, tempCoord.Y, set);
              
              editErrors = nothingHappens;
          }
      }
      int core_Editor(){
          // Вернёт написанный пользователем индекс персоны.
          printInviteToEnterIndex();
          
          int index;
          bool isEditingContinue = true;
          while(isEditingContinue){
              PressedKey key = whatPressed();
              removeError();
              
              if(key.isSpecial)
                  switch (key.code) {
                      case Up     :
                          handler_Back();
                          moveUp();
                          // Возвращаемся к выбору способа выбора
                          return cancelEnter;
                      case Down   :
                          handler_Back();
                          moveDown();
                          // Возвращаемся к выбору способа выбора
                          return cancelEnter;
                      case Left   : moveLeft();             break;
                      case Right  : moveRight();            break;
                      case Delete : handler_DeleteRemove(); break;
                      default     : break;
                  }
              else
                  switch(key.code){
                      case Esc    :
                          handler_Back();
                          // Возвращаемся к выбору способа выбора
                          return cancelEnter;
                      case Enter     : isEditingContinue = !isIndexCorrect(); break;
                      case Backspace : handler_BackspaceRemove();  break;
                      default        : // Если не нажата ни одна управляющая клавиша
                          handler_InsertSym(key.code);
                          break;
                  }
              
              setError();
          }
          
          return index;
      }
    }
    enum TypeEvent {
        edit,
        remove
    };
    void core_ChooseSelectMode(TypeEvent type) {
        if(countPersons == 0){ // Что пользователь хотел запустить?
            if(type == remove)
                coreAnswer = failedEdit;
            else
                coreAnswer = failedRemove;
            
            return; // В главное меню.
        }
        
        // Установим курсор в шапку главного меню.
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        
        // Объяаим обработчик выбранного пользователем события.
        bool (*handler_Enter1)(int);
        bool (*handler_Enter2)(int);
        
        if(type == remove){
            handler_Enter1 = Remove::core_removePerson;
            handler_Enter2 = Remove::handler_IndexRemove;
            Remove::printSelectChoiceRemoveModeCap(); // Обновим шапку
        }
        else {
            handler_Enter1 = core_FieldEdit;
            handler_Enter2 = handler_IndexEdit;
            printSelectChoiceEditModeCap(); // Обновим шапку
        }
        
        
        updateMenuItems(); // Обновим пункты уже не главного меню.
        
        // Устроим обработку действий пользователя в подменю выбора.
        enum {fakeArg}; // Для вызова действия, которое выбрал пользователь, костыль.
        bool isEditing = true;
        while(coreAnswer == nothingHappens && isEditing){
            PressedKey key = whatPressed();
            
            if(key.isSpecial)
                switch(key.code){
                    case Up   : moveUp();   break;
                    case Down : moveDown(); break;
                    default   : break;
                }
            else if(key.code == Enter)
                switch(cursor.Y){
                    case fieldChoice : isEditing = handler_Enter1(fakeArg); break;
                    case indexChoice : isEditing = handler_Enter2(MiniEditor::core_Editor()); break;
                    case backChoice  : return; // Назад в главное меню
                    default          : throw(__LINE__); // Не должно исполниться.
                }
        }
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
  }
  
  namespace RemoveDB {
    inline void core_DeleteDatabase() {
        if(countPersons == 0){
            coreAnswer = failedRemoveDB;
            return;
        }
        countPersons = 0;
        coreAnswer = successRemoveDB;
    }
  }
  namespace See {
    inline void printAllDbCap(){
        system("CLS");
        cout << "                                  Все персоны:                                " << endl;
    }
    
    void core_seeDB() {
        if(countPersons == 0){
            coreAnswer = failedSee;
            return;
        }
        
        printAllDbCap();
        Find::printTablePersonsCap();
        
        for(int i = 0; i < countPersons; ++i){
            Find::printPerson(persons[i], i);
            if(i + 1 != countPersons) // Чтобы таблица красиво заканчивалась
                Find::printSeparatorLine();
        }
        
        Find::printEndTable();
        system("PAUSE");
    }
  }
  namespace Search {
    // Поиск и вывод людей по хотя бы одному совпадающему критерию.
    inline void printSearchCap(){
        system("CLS");
        cout << "                       ╔   Критерии выборки   ╗                       " << endl;
    }
    
    void core_SimilarSelection() {
        if(countPersons == 0){
            coreAnswer = failedSearch;
            return;
        }
        
        Editor::RawPerson rawP;
        printSearchCap();
        Editor::core_EditPerson(rawP); // Получим критерии отбора от пользователя.
        
        if (rawP.isSubmit) {
            Find::Similar similar = Find::findSimilar(rawP);
            
            // Покажем что есть в БД по этим критериям.
            system("CLS"); // Т.к. функция ниже этого не делает
            Find::printSimilarPersonsCap();
            Find::selectSimilarPersons_ToPrint(similar);
            
            system("PAUSE");
        }
        else
            coreAnswer = cancelSelectionShow;
    }
  }
  
  namespace Main {
    // Всегда указывает на первый пункт главного меню
    constexpr COORD defaultCoord = {27, 3};
    static_assert(defaultCoord.X == Change::defaultCoord.X &&
                  defaultCoord.Y == Change::defaultCoord.Y,
                  "Размеры и положение главного меню связаны с "
                          "частями добавления и удаления персоны. "
                          "Изменяя здесь - измени и там."
                 );
    
    enum MainMenuItems {
        addPerson = 3, //defaultCoord.Y,
        changePerson,
        delPerson,
        delDB,
        seeDB,
        addons,
        leave,
        coreMessagesField = leave + 2 // Т.к. есть разделительная линия
    };
    
    inline void printCursor(){
        moveCursor();
        cout << "->";
        moveCursor();
    }
    inline void removeCursor(){
        cout << "  ";
    }
    
    void printMainMenu() {
        system("CLS");
        cout << "                        ╔═────────────────────────────═╗" << endl;
        cout << "                        ╟         Главное меню         ╢" << endl;
        cout << "                        ╟──────────────────────────────╢" << endl;
        cout << "                        │ [  ] Добавить персону в БД   │" << endl;
        cout << "                        │ [  ] Изменить данные персоны │" << endl;
        cout << "                        │ [  ] Удаление персоны из БД  │" << endl;
        cout << "                        │ [  ] Очистка БД              │" << endl;
        cout << "                        │ [  ] Просмотр всей базы      │" << endl;
        cout << "                        │ [  ] Поиск по критерию       │" << endl;
        cout << "                        │ [  ] Выход                   │" << endl;
        cout << "                        │──────────────────────────────│" << endl;
        cout << "                        │                              │" << endl;
        cout << "                        │══════════════════════════════│" << endl;
        cout << "                        │ Персон в базе данных:        │" << endl;
        cout << "                        ╚══════════════════════════════╝" << endl;
        
        moveCursor(defaultCoord.X + 21, defaultCoord.Y + 10, set);
        cout << countPersons;
        
        cursor = defaultCoord;
        printCursor();
        
    }
    
    namespace CheatCodes {
      namespace StreamInput {
        inline void printExplanation(){
            system("CLS");
            cout << "Сейчас можно ввести список персон в таком формате: "<< endl;
            cout << "Фамилия, Имя, Отчество, дата рождения(ДД.ММ.ГГГГ), пол (Ж\\М);" << endl;
            
            cout << "За соответствие формата отвечает пользователь." << endl;
            cout << "Выход в главное меню по нажатию Enter. Введите список персон: " << endl;
        }
        
        inline void getNextField(char* personField, char separator){
            char enterField[maxLength];
            int countSyms = 0;
            
            while(cin.peek() != separator){
                enterField[countSyms++] = char(cin.get());
            }
            cin.get(); // Игнорируем разделитель.
            
            // Уберём все пробелы после запятой.
            while(isspace(cin.peek()) && cin.peek() != '\n')
                cin.get();
            
            // Завершим принятие поля персоны.
            enterField[countSyms] = '\0';
            strcpy(personField, enterField);
        }
        Editor::RawPerson& fillRawPerson(Editor::RawPerson& rawP){
            // Фамилия, имя отчество, дата рождения и пол в одном флаконе.
            getNextField(rawP.fields[Editor::surName],    ',');
            getNextField(rawP.fields[Editor::name],       ',');
            getNextField(rawP.fields[Editor::middleName], ',');
            getNextField(rawP.fields[Editor::birthday],   ',');
            getNextField(rawP.fields[Editor::gender],     ';');
            return rawP;
        }
        void runStreamInput(){
            printExplanation();
            
            Editor::RawPerson rawP;
            while(cin.peek() != '\n')
                persons[countPersons++] = Editor::toPerson(fillRawPerson(rawP));
            
            cin.get(); // Заберём \n из потока после ввода всех персон.
            
            // Вернём меню обратно, т.к. после нажатия стрелки
            // не было запланировано появление чего-либо.
            printMainMenu();
        }
        
        inline void handling_Up(const char cheat[], int& n, int cheatLength){
            if (cheat[n] == 'U') {
                if (n == cheatLength)
                    runStreamInput();
            } else
                n = -1;
        }
        inline void handling_Down(const char cheat[], int& n, int cheatLength){
            if (cheat[n] == 'D') {
                if (n == cheatLength)
                    runStreamInput();
            }
            else
                n = -1;
        }
        void handlerCheat(Keys key){
            // Позволяет переключиться в потоковый ввод персон.
            
            // Формат ввода данных:
            // Фамилия, Имя, Отчество, дата рождения(ДД.ММ.ГГГГ), пол (М\Ж);
            
            // Выход в главное меню осуществляется после
            // нажатия Enter.
            static const char cheat[] = "UDDDUDDDUUUUUUUD";
            static int n = -1; // Индикатор ввода чита.
            
            ++n;
            switch (key) {
                case Up   : handling_Up  (cheat, n, sizeof(cheat)-2); break;
                case Down : handling_Down(cheat, n, sizeof(cheat)-2); break;
                default   : throw (__LINE__); // Не должно использоваться
            }
            
        }
      }
      
      void handler_Cheats(Keys key) {
          // Отправим нажатую клавишу во все обработчики читов.
          
          void (*handlers[])(Keys) = {
                  StreamInput::handlerCheat
          };
          
          for(size_t i = 0; i < sizeof(handlers)/sizeof(void*); ++i) // FIXME sizeof(void*) == sizeof( (void*)() )?
              handlers[i](key);
      }
    }
    inline void moveUp() {
        removeCursor();
        
        if (cursor.Y > addPerson)
            --cursor.Y; // Вверх на одну строку
        
        else // Если в самом верху
            cursor.Y = leave;
        
        printCursor();
        
        CheatCodes::handler_Cheats(Up);
    }
    inline void moveDown() {
        removeCursor();
        
        if (cursor.Y < leave)
            ++cursor.Y; // Вниз на одну строку
        
        else // Если в самом низу
            cursor.Y = defaultCoord.Y;
        
        printCursor();
        
        CheatCodes::handler_Cheats(Down);
    }
    
    inline bool handling_Enter() {
        // Обработает выбор пользователя.
        // Вернёт ответ, продолжать ли работу БД.
        
        // После выполнения работы функции, вернём главное меню обратно
        
        switch (cursor.Y) {
            case addPerson    :
                Add::core_addPerson();
                printMainMenu();
                return true;
            case changePerson :
                Change::core_ChooseSelectMode(Change::TypeEvent::edit);
                printMainMenu(); return true;
            case delPerson    :
                Change::core_ChooseSelectMode(Change::TypeEvent::remove);
                printMainMenu(); return true;
            case delDB        :
                RemoveDB::core_DeleteDatabase();
                printMainMenu();
                return true;
            case seeDB        :
                See::core_seeDB();
                printMainMenu();
                return true;
            case addons       :
                Search::core_SimilarSelection();
                printMainMenu();
                return true;
            case leave        : return false;
            default           : throw(__LINE__); // Не должно использоваться
        }
        
    }
    
    inline void printCoreMessage(){
        
        if(coreAnswer != nothingHappens){
            COORD tempCoord = cursor;
            moveCursor(defaultCoord.X - 1, coreMessagesField, set);
            
            switch (coreAnswer) {
                case successAdd          : cout << "  Новая персона добавлена   "; break;
                case failedAdd           : cout << "      Места больше нет      "; break;
                case successEdit         : cout << "      Персона изменена      "; break;
                case failedEdit          : cout << "      Некого изменять       "; break;
                case successRemove       : cout << "      Персона удалена       "; break;
                case failedRemove        : cout << "      Некого удалять        "; break;
                case successRemoveDB     : cout << "    База данных очищена     "; break;
                case failedRemoveDB      : cout << "       Нечего очищать       "; break;
                case failedSee           : cout << "     База данных пуста      "; break;
                case failedSearch        : cout << "       Некого искать        "; break;
                
                case canceledAdd         : cout << "    Добавление отменено     "; break;
                case canceledEdit        : cout << "  Редактирование отменено   "; break;
                case canceledRemove      : cout << " Удаление персоны отменено  "; break;
                
                case cancelSelectionShow : cout << "  Выборочный показ отменён  "; break;
                
                default                  : throw(__LINE__); // Не должно использоваться
            }
            
            moveCursor(tempCoord.X, tempCoord.Y, set);
        }
        
    }
    inline void removeMessage(){
        if(coreAnswer != nothingHappens) {
            COORD tempCoord = cursor;
            
            moveCursor(defaultCoord.X - 1, coreMessagesField, set);
            cout << "                            ";
            moveCursor(tempCoord.X, tempCoord.Y, set);
            
            coreAnswer = nothingHappens;
        }
    }
    void runInterfaceDB() {
        // Главное меню управления БД
        printMainMenu();
        bool isProgramWork = true;
        
        while (isProgramWork) {
            PressedKey key = whatPressed();
            removeMessage();
            
            // Тут нет совпадений между кодами специальных и обычных клавиш.
            switch(key.code){
                case Enter   : isProgramWork = handling_Enter(); break;
                case Up      : moveUp();                         break;
                case Down    : moveDown();                       break;
                default      :                                   break;
            }
            
            printCoreMessage();
        }
    }
  }
}

int main(){system("chcp 866 && cls");
    try {
        Menu::Main::runInterfaceDB();
    }
    catch(int numberString){
        system("CLS");
        cout << "Ошибка, выполнение долшло до строки " << numberString << endl;
        system("PAUSE");
    }
    return 0;
}
