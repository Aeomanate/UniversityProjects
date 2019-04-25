#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
using namespace std;
enum Constants{
    maxLength = 40,
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
    bool isFieldAviable[5] = {};
} persons[maxCountPersons];
int countPersons = 0;
namespace Menu {
  bool myStrCmp(const char* s1, const char* s2){
      while(*s1 != '\0')
          if(*s1++ != *s2++)
              return false;
      while(*s2 != '\0')
          if(*s2++ != *s2++)
              return false;
      return true;
  }
  short slen(const char* s){
      short length = 0;
      while(*s++)
          ++length;
      return length;
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
      static HANDLE consoleID = GetStdHandle(STD_OUTPUT_HANDLE);
      if(mode == move) {
          if (x != 0)
              cursor.X += short(x);
          if (y != 0)
              cursor.Y += short(y);
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
      key.code = char(_getch());
      if (_kbhit()) {
          key.isSpecial = true;
          key.code = char(_getch());
      }
      return key;
  }
  namespace Editor {
    struct RawPerson {
        char fields[5][maxLength] = {};
        bool isSubmit = false;
    };
    enum EditFields {
        surName,
        name,
        middleName,
        birthday,
        gender
    };
    constexpr COORD defaultCoord = {27, 2};
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
        submitError,
        tooLongField,
        wrongSymbol,
        comboWrong,
        nothingRemove,
    } editError;
    enum ExternalErrors {
        noExternalErrors,
        similarPersonNotFound
    } externalError;
    inline void printEditMenu() {
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
        cursor = defaultCoord;
        moveCursor();
    }
    inline void handling_ShiftUp_OnLastName() {
        moveCursor(backCoordX, controlButtons, set);
        cout << 'x';
        moveCursor();
    }
    inline void handling_ShiftUp_OnMiddle(const RawPerson& rawP) {
        --cursor.Y;
        int nextField = cursor.Y - surNameY;
        cursor.X = defaultCoord.X + slen(rawP.fields[nextField]);
        moveCursor();
    }
    inline void handling_ShiftUp_OnControl(const RawPerson& rawP) {
        cout << ' ';
        moveCursor(defaultCoord.X + slen(rawP.fields[genderY]), genderY, set);
    }
    void shiftUp(const RawPerson& rawP) {
        if (cursor.Y == controlButtons)
            handling_ShiftUp_OnControl(rawP);
        else if (cursor.Y > surNameY)
            handling_ShiftUp_OnMiddle(rawP);
        else
            handling_ShiftUp_OnLastName();
    }
    inline void handling_ShiftDown_OnMiddle(const RawPerson& rawP) {
        ++cursor.Y;
        int nextField = cursor.Y - surNameY;
        cursor.X = defaultCoord.X + slen(rawP.fields[nextField]);
        moveCursor();
    }
    inline void handling_ShiftDown_OnPreControl() {
        moveCursor(backCoordX, controlButtons, set);
        cout << 'x';
        moveCursor();
    }
    inline void handling_ShiftDownEnter_OnPreControl(){
        moveCursor(submitCoordX, controlButtons, set);
        cout << 'x';
        moveCursor();
    }
    inline void handling_ShiftDown_OnControl(const RawPerson& rawP) {
        cout << ' ';
        cursor = defaultCoord;
        moveCursor();
    }
    void shiftDownEnter(const RawPerson& rawP){
        if (cursor.Y < genderY)
            handling_ShiftDown_OnMiddle(rawP);
        else if (cursor.Y == genderY)
            handling_ShiftDownEnter_OnPreControl();
        else
            handling_ShiftDown_OnControl(rawP);
    }
    void shiftDown(const RawPerson& rawP) {
        if (cursor.Y < genderY)
            handling_ShiftDown_OnMiddle(rawP);
        else if (cursor.Y == genderY)
            handling_ShiftDown_OnPreControl();
        else
            handling_ShiftDown_OnControl(rawP);
    }
    inline void handling_MoveLeft_Field(const RawPerson& rawP) {
        if (defaultCoord.X < cursor.X)
            --cursor.X;
        else if (defaultCoord.X == cursor.X)
            cursor.X = defaultCoord.X + slen(rawP.fields[cursor.Y - surNameY]);
        moveCursor();
    }
    inline void handling_MoveLeft_ControlButtons() {
        cout << ' ';
        if (cursor.X == backCoordX)
            cursor.X = submitCoordX;
        else
            cursor.X = backCoordX;
        moveCursor();
        cout << 'x';
        moveCursor();
    }
    void moveLeft(const RawPerson& rawP) {
        if (cursor.Y < controlButtons)
            handling_MoveLeft_Field(rawP);
        else
            handling_MoveLeft_ControlButtons();
    }
    inline void handling_MoveRight_Field(const RawPerson& rawP) {
        if (defaultCoord.X + slen(rawP.fields[cursor.Y - surNameY]) > cursor.X)
            ++cursor.X;
        else
            cursor.X = defaultCoord.X;
        moveCursor();
    }
    inline void handling_MoveRight_ControlButtons() {
        cout << ' ';
        if (cursor.X == submitCoordX)
            cursor.X = backCoordX;
        else
            cursor.X = submitCoordX;
        moveCursor();
        cout << 'x';
        moveCursor();
    }
    void moveRight(const RawPerson& rawP) {
        if (cursor.Y < controlButtons)
            handling_MoveRight_Field(rawP);
        else
            handling_MoveRight_ControlButtons();
        moveCursor();
    }
    inline void removeSymbol(char field[], int remSymPos){
        for (int i = remSymPos; i < slen(field); ++i)
            field[i] = field[i + 1];
        cout << &field[remSymPos];
        cout << ' ';
        moveCursor();
    }
    void handler_DeleteRemove(RawPerson& rawP){
        int remSymPos = cursor.X - defaultCoord.X;
        int curField = cursor.Y - surNameY;
        if(remSymPos == slen(rawP.fields[curField]) || cursor.Y == controlButtons){
            editError = nothingRemove;
            return;
        }
        removeSymbol(rawP.fields[curField], remSymPos);
    }
    void handler_BackspaceRemove(RawPerson& rawP){
        int remSymPos = cursor.X - defaultCoord.X - 1;
        int curField = cursor.Y - surNameY;
        if(remSymPos == -1 || cursor.Y == controlButtons){
            editError = nothingRemove;
            return;
        }
        moveCursor(-1, 0);
        removeSymbol(rawP.fields[curField], remSymPos);
    }
    void insertSym(char field[], int symPos, char sym) {
        for (int i = slen(field); i >= symPos; --i)
            field[i + 1] = field[i];
        field[symPos] = sym;
        cout << field + symPos;
        moveCursor(1, 0);
    }
    inline bool isCorrectSymbol(char sym) {
        return isalpha(sym) || isdigit(sym) ||
               'А' <= sym && sym <= 'я'   ||
               sym == 'Ё' || sym == 'ё'   ||
               sym == '.' || sym == '-'   ||
               sym == ' ';
    }
    inline bool isSpaceFree(char field[], int rightLength){
        return slen(field) < rightLength;
    }
    bool setInsertErrors(RawPerson& rawP, char sym, int rightBorder){
        int curField = cursor.Y - surNameY;
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
        int symPos = cursor.X - defaultCoord.X;
        int curField = cursor.Y - defaultCoord.Y;
        if(setInsertErrors(rawP, sym, maxLength))
            return;
        insertSym(rawP.fields[curField], symPos, sym);
    }
    inline bool checkDate(int day, int month, int year) {
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
        if(slen(rawP.fields[birthday]) > 0 || numbersInDate == 3)
            if (!checkDate(day, month, year))
                return false;
        if(slen(rawP.fields[gender]) != 0)
            if (!checkGender(rawP.fields[gender]))
                return false;
        return true;
    }
    bool handler_Enter(RawPerson& rawP){
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
                    throw(__LINE__);
            }
        else {
            shiftDownEnter(rawP);
            isEdit = true;
        }
        return isEdit;
    }
    inline void printDoneData(const RawPerson& rawP){
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        for(int i = surName; i <= gender; ++i) {
            cout << rawP.fields[i];
            moveCursor(0, 1);
        }
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
                    throw(__LINE__);
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
                    throw(__LINE__);
            }
            moveCursor(tempCoord.X, tempCoord.Y, set);
        }
    }
    inline void removeErrors() {
        if(editError != noEditErrors || externalError != noExternalErrors) {
            COORD tempCoord = cursor;
            moveCursor(errorCoordX, errorCoordY, set);
            cout << "                                                                " << endl;
            moveCursor(tempCoord.X, tempCoord.Y, set);
            editError = noEditErrors;
            externalError = noExternalErrors;
        }
    }
    void core_EditPerson(RawPerson& rawP) {
        printEditMenu();
        if(rawP.isSubmit)
            printDoneData(rawP);
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
                    default        :
                        handler_InsertSym(rawP, key.code);
                        break;
                }
            setErrors();
        }
    }
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
  }
  namespace Find {
    using Editor::RawPerson;
    inline bool checkSimilar(const Person& person, const RawPerson& rawP) {
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
        for (int i = 0; i < countPersons; ++i)
            if (checkSimilar(persons[i], rawP))
                similar.number[similar.n++] = i;
        return similar;
    }
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
        string str = name;
        if(str.size() > limit) {
            str[limit - 0] = '\0';
            str[limit - 1] = '.';
            str[limit - 2] = '.';
            str[limit - 3] = '.';
        }
        else
            while(str.size() < limit)
                str += ' ';
        return str.c_str();
    }
    string reformDate(const char date[]){
        int day, month, year;
        sscanf(date, "%d.%d.%d", &day, &month, &year);
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
            if(i + 1 != similar.n)
                printSeparatorLine();
        }
        printEndTable();
    }
    static const COORD defaultCoord = {0, 6};
    inline void printSimilarPersonsCap(){
        cout << "                              Похожие персоны:                                " << endl;
    }
    inline void printCursor(){
        cout << "->";
        moveCursor();
    }
    inline void removeCursor(){
        cout << "  ";
        moveCursor();
    }
    inline void moveUp(Similar& similar){
        removeCursor();
        short downBorder = short(defaultCoord.Y + similar.n*2 - 2);
        if(cursor.Y > defaultCoord.Y)
            moveCursor(0, -2);
        else
            moveCursor(defaultCoord.X, downBorder, set);
        printCursor();
    }
    inline void moveDown(Similar& similar){
        removeCursor();
        short downBorder = short(defaultCoord.Y + similar.n*2 - 2);
        if(cursor.Y < downBorder)
            moveCursor(0, 2);
        else
            moveCursor(defaultCoord.X, defaultCoord.Y, set);
        printCursor();
    }
    inline int handlingEnter(Similar& similar){
        return similar.number[(cursor.Y - defaultCoord.Y) / 2];
    }
    enum UserChoice {
        cancelChoice = -1,
    };
    int core_RefineChoice(Similar &similar){
        printSimilarPersonsCap();
        selectSimilarPersons_ToPrint(similar);
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        printCursor();
        while(true){
            PressedKey key = whatPressed();
            switch(key.code){
                case Up    : moveUp(similar);        break;
                case Down  : moveDown(similar);      break;
                case Enter : return handlingEnter(similar);
                case Esc   : return cancelChoice;
                default    : break;
            }
        }
    }
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
    inline void printEnterRemoveCap() {
        system("CLS");
        cout << "                       ╔     Кого удаляем?    ╗                       " << endl;
    }
    inline void printChoiceSimilarRemoveCap(){
        system("CLS");
        cout << "                        Какую персону следует удалить?                        " << endl << endl;
    }
    inline void removePerson(int whoRemove) {
        for(int i = whoRemove; i < countPersons-1; ++i)
            persons[i] = persons[i+1];
        --countPersons;
    }
    bool core_removePerson (int) {
        if(countPersons == 0){
            coreAnswer = failedRemove;
            return true;
        }
        int whoRemove;
        while(true){
            printEnterRemoveCap();
            Editor::RawPerson rawP = Add::getRawPerson();
            if (rawP.isSubmit) {
                Find::Similar similar = Find::findSimilar(rawP);
                if(similar.n == 0) {
                    Editor::externalError = Editor::ExternalErrors::similarPersonNotFound;
                    continue;
                }
                if(similar.n == 1) {
                    whoRemove = similar.number[0];
                    break;
                }
                else if(similar.n > 1){
                    printChoiceSimilarRemoveCap();
                    whoRemove = Find::core_RefineChoice(similar);
                    if(whoRemove == Find::UserChoice::cancelChoice)
                        continue;
                    else
                        break;
                }
                throw(__LINE__);
            }
            else {
                coreAnswer = canceledRemove;
                return true;
            }
        }
        removePerson(whoRemove);
        coreAnswer = successRemove;
    }
    bool handler_IndexRemove(int index){
        if(index == -1)
            return true;
        removePerson(index);
        coreAnswer = successRemove;
        return false;
    }
    inline void printSelectChoiceRemoveModeCap(){
        moveCursor(-1, -2);
        cout << "  Способ удаления персоны?  ";
        moveCursor(1, 2);
    }
  }
  namespace Change {
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
        int whoEdit;
        while(true){
            printEnterDataCap();
            Editor::RawPerson rawP = Add::getRawPerson();
            if (rawP.isSubmit) {
                Find::Similar similar = Find::findSimilar(rawP);
                if(similar.n == 0) {
                    Editor::externalError = Editor::ExternalErrors::similarPersonNotFound;
                    continue;
                }
                else if(similar.n == 1)
                    whoEdit = similar.number[0];
                else if(similar.n > 1){
                    printSimilarEditCap();
                    whoEdit = Find::core_RefineChoice(similar);
                    if(whoEdit == Find::UserChoice::cancelChoice) {
                        coreAnswer = canceledEdit;
                        return false;
                    }
                }
                if(whoEdit < 0)
                    throw(__LINE__);
                rawP = Editor::toRaw(whoEdit);
                printEditDataCap();
                Editor::core_EditPerson(rawP);
                if(rawP.isSubmit) {
                    persons[whoEdit] = Editor::toPerson(rawP);
                    coreAnswer = successEdit;
                    return false;
                }
                else {
                    coreAnswer = canceledEdit;
                    return false;
                }
            }
            else {
                coreAnswer = canceledEdit;
                return false;
            }
        }
    }
    bool handler_IndexEdit(int index){
        if(index == -1)
            return true;
        Editor::RawPerson rawP = Editor::toRaw(index);
        printEditDataCap();
        Editor::core_EditPerson(rawP);
        if(rawP.isSubmit){
            persons[index] = Editor::toPerson(rawP);
            coreAnswer = successEdit;
        }
        else coreAnswer = canceledEdit;
        return false;
    }
    constexpr COORD defaultCoord = {27, 3};
    inline void printCursor(){
        cout << "->";
        moveCursor();
    }
    inline void removeCursor(){
        cout << "  ";
        moveCursor();
    }
    inline void printSelectChoiceEditModeCap(){
        moveCursor(-1, -2);
        cout << "   Способ выбора персоны?   ";
        moveCursor(1, 2);
    }
    inline void updateMenuItems(){
        moveCursor(-1, 0);
        cout << "[  ] Поля персоны            ";
        moveCursor(0, 1);
        cout << "[  ] Индекс персоны          ";
        moveCursor(0, 1);
        cout << "[  ] В главное меню          ";
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
    namespace MiniEditor {
      static_assert(getCountDigits(maxCountPersons, 0) <= 3, "Table persons will be broken");
      char index[getCountDigits(maxCountPersons, 0)+1] = {};
      constexpr COORD defaultCoord = {short(Change::defaultCoord.X + 4 + 16),
                                      short(Change::defaultCoord.Y + 1)};
      inline void printInviteToEnterIndex(){
          moveCursor(4, 0);
          cout << "Введите индекс: ";
          cursor = defaultCoord;
      }
      inline void handler_Back (){
          moveCursor(- slen(index) - 16, 0);
          cout << "Индекс персоны          ";
          moveCursor(-4, 0);
          removeCursor();
          for(auto& c: index)
              c = '\0';
      }
      inline void moveLeft(){
          if(defaultCoord.X < cursor.X)
              moveCursor(-1, 0);
          else
              moveCursor(slen(index), 0);
      }
      inline void moveRight(){
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
          int remSymPos = cursor.X - defaultCoord.X;
          if(remSymPos == slen(index)){
              editErrors = errorRemove;
              return;
          }
          Editor::removeSymbol(index, remSymPos);
      }
      void handler_BackspaceRemove(){
          int remSymPos = cursor.X - defaultCoord.X - 1;
          if(remSymPos == -1){
              editErrors = errorRemove;
              return;
          }
          moveCursor(-1, 0);
          Editor::removeSymbol(index, remSymPos);
      }
      void handler_InsertSym(char sym){
          int symPos = cursor.X - defaultCoord.X;
          if(!isdigit(sym) || slen(index)+1 > getCountDigits(maxCountPersons, 0)) {
              editErrors = errorInsert;
              return;
          }
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
                  default          : throw(__LINE__);
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
                          return cancelEnter;
                      case Down   :
                          handler_Back();
                          moveDown();
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
                          return cancelEnter;
                      case Enter     : isEditingContinue = !isIndexCorrect(); break;
                      case Backspace : handler_BackspaceRemove();  break;
                      default        :
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
        if(countPersons == 0){
            if(type == remove)
                coreAnswer = failedEdit;
            else
                coreAnswer = failedRemove;
            return;
        }
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        bool (*handler_Enter1)(int);
        bool (*handler_Enter2)(int);
        if(type == remove){
            handler_Enter1 = Remove::core_removePerson;
            handler_Enter2 = Remove::handler_IndexRemove;
            Remove::printSelectChoiceRemoveModeCap();
        }
        else {
            handler_Enter1 = core_FieldEdit;
            handler_Enter2 = handler_IndexEdit;
            printSelectChoiceEditModeCap();
        }
        updateMenuItems();
        enum {fakeArg};
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
                    case backChoice  : return;
                    default          : throw(__LINE__);
                }
        }
    }
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
            if(i + 1 != countPersons)
                Find::printSeparatorLine();
        }
        Find::printEndTable();
        system("PAUSE");
    }
  }
  namespace Search {
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
        Editor::core_EditPerson(rawP);
        if (rawP.isSubmit) {
            Find::Similar similar = Find::findSimilar(rawP);
            system("CLS");
            Find::printSimilarPersonsCap();
            Find::selectSimilarPersons_ToPrint(similar);
            system("PAUSE");
        }
        else
            coreAnswer = cancelSelectionShow;
    }
  }
  namespace Main {
    constexpr COORD defaultCoord = {27, 3};
    static_assert(defaultCoord.X == Change::defaultCoord.X &&
                  defaultCoord.Y == Change::defaultCoord.Y,
        "Размеры и положение главного меню связаны с "
        "частями добавления и удаления персоны. "
        "Изменяя здесь - измени и там."
    );
    enum MainMenuItems {
        addPerson = 3,
        changePerson,
        delPerson,
        delDB,
        seeDB,
        addons,
        leave,
        coreMessagesField = leave + 2
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
            cin.get();
            while(isspace(cin.peek()) && cin.peek() != '\n')
                cin.get();
            enterField[countSyms] = '\0';
            strcpy(personField, enterField);
        }
        Editor::RawPerson& fillRawPerson(Editor::RawPerson& rawP){
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
            cin.get();
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
            static const char cheat[] = "UDDDUDDDUUUUUUUD";
            static int n = -1;
            ++n;
            switch (key) {
                case Up   : handling_Up  (cheat, n, sizeof(cheat)-2); break;
                case Down : handling_Down(cheat, n, sizeof(cheat)-2); break;
                default   : throw (__LINE__);
            }
        }
      }
      void handler_Cheats(Keys key) {
          void (*handlers[])(Keys) = {
              StreamInput::handlerCheat
          };
          for(int i = 0; i < sizeof(handlers)/sizeof(void*); ++i)
              handlers[i](key);
      }
    }
    inline void moveUp() {
        removeCursor();
        if (cursor.Y > addPerson)
            --cursor.Y;
        else
            cursor.Y = leave;
        printCursor();
        CheatCodes::handler_Cheats(Up);
    }
    inline void moveDown() {
        removeCursor();
        if (cursor.Y < leave)
            ++cursor.Y;
        else
            cursor.Y = defaultCoord.Y;
        printCursor();
        CheatCodes::handler_Cheats(Down);
    }
    inline bool handling_Enter() {
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
            default           : throw(__LINE__);
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
                default                  : throw(__LINE__);
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
        printMainMenu();
        bool isProgramWork = true;
        while (isProgramWork) {
            PressedKey key = whatPressed();
            removeMessage();
            switch(key.code){
                case Enter   : isProgramWork = handling_Enter(); break;
                case Up      : moveUp();                         break;
                case Down    : moveDown();                       break;
                default      :                                   break;
            }
            printCoreMessage();}}}}
int main(){system("chcp 866 && cls");
    try {Menu::Main::runInterfaceDB();}
    catch(int numberString){system("CLS");cout << "Ошибка, выполнение долшло до строки " << numberString << endl;system("PAUSE");}
    return 0;
}
