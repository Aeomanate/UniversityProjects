// ������� �� � ���� ��� ���

// ��:
// �������, ���, ����⢮, ��� ஦�����, ���
// �������: �������� ��稭

// ����:
// ���������� �����, ।���஢���� �����,
// 㤠����� �����, 㤠����� ��� ����ᥩ, ��ᬮ�� ��

// P.S. �஡���� �⮣� �஥��
// 1.  ���ᥭ�� �������⥫쭮�� ����� �������� �� ᮡ�� ᮧ����� ��������
//     �����᪨ �㭪権. ������ �㭪樨 �믮����� ࠧ���, �� �ਭ樯� ࠡ���
//     ���������. ��������� �� ��ꥤ����� �� ��� ����� ��砫��,
//     �� ᫨誮� ����� ����ᨬ��⥩ �㦭� �㤥� �������.
//     �����᪨, �㦭� ��९���� ��������� ���� ����� Editor, � �६� ���������.

// 2.  Find-�㭪樨 ���� �� ࠧ������, �� ������⭮ ���� ��

// 3.  Editor ������ �� ���譨� �᫮���.
//     ���� ����砫쭮 �� ����ᥫ: ���譨� 蠯�� � ���譨� ᮮ�饭��
//     ������ ���⨭� ����.
//     �����, �⮨�� �� ᤥ���� ��ࠡ��稪 ��� ��� ���譨� ᮡ�⨩?

// 4.  ����� �㭪権, �믮������ ��宦�� ࠡ���,
//     ஧����� �� ���� � �����. Print, Show, See - ???

// 5.  ���������� �� 䠩�� �� ����稫���. �祭� ����� ����ᨬ��⥩.
//     ��������, CLion �� ᫨誮� ���⭮ ॠ����� �� ᨭ⠪�� ࠧ�������.

// 6.  inline. �� �����. ��, �� �������� ������, ����� �㭪樨
//     ������, � ����� - �����.

// 7.  ���������� ��� 㤠����� ������ ���� � �� ���ॡ�� ������ �ࠢ��
//     ��-�� ������ ࠧ��� ���樠⨢��� ����⠭�, �⢥���� ��
//     �ᯮ������� ����� �� �࠭� � � ���ᨢ��.
//     �㦭� �뫮 ᮧ���� ⮫쪮 ��� ���樠⨢��� ����᫥���,
//     ����� �� 㤮���⢮ਫ� �� �㭪樨 ����.

// 8.  ���� �����᪨� �᫠ ⨯� ��ப "��稭�", �� ������ ������
//     �㦭� �㤥� ��ᬮ���� ��᪮�쪮 ����, � �� ����.
//     �९������ ���ୠ樮������樨 �ணࠬ��.

// 9.  � ।���� �ᯮ������ ᨬ���쭮� ।���஢���� ���� ���ᮭ�, ���
//     ��४���⥫� �룫拉� �� ��ᨢ�� � ࠡ�⠫ �� ����॥.

// 10. ���誮� ����� ����⨯��� �㭪権 ��� ��६�饭�� �����:
//     �㦭� �뫮 ᤥ���� ��騩 ��ࠡ��稪, � ����� ���뫠�� �������� �࠭���
//     � �����⥫� ��������� �����. ��� � ����, � ����⭥�.
//
//
//

// ������ ��⨭�:
// 1. COORD cursor � ���᮫� �易�� ⮫쪮 �� �ணࠬ���� � ���᮫�,
//    ���⭮� �� ��୮ - ���᮫� �� ������� cursor (lol).

// 2. �� ��� ᯥ樠��� ������ �������� 2 ����.
//    ���� ᯥ檫���� ᮢ������ � ����묨 ��, 祬 �।����������.
// 3. ����祭�� ��� � ����࠭�祭��� enum - ���譠� ����.
//    � ᫥���騩 ࠧ �㦭� �㤥� �ᯮ�짮���� enum class.
//    � �롨��� ����� ����⠭� ����.

// 4. ���������� �⢥��⢥����� �㭪権 ᯮᮡ���� ����஬� ���ᥭ��
//    ��������� � ���஢���� �ணࠬ��. ������ ࠧ������ ����訥 �㭪樨
//    �� ⠪��, ����� �� �ॡ����� ���� ��㬥�⮢ � �믮��﫨 ����� ࠡ���.

// 5. ���誮� ��भ�� ࠧ������ ������ �� ������ �㭪樨 ����� ���񧭮
//    㢥����� ������⢮ �㭪権.
//    ���� �맢��� �� ����室��� �㭪樨 ��࠭��, � ��⮬ ������� ��.
//    ����� �㤥� �᪫��� ����⮪ �㭪権.

// 6. ����� ᮧ������ ������ ��� �㭪権, ����� �믮����� ��⨢��������
//    ����⢨�. (��. �㭪� 5).
#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
using namespace std;

enum Constants{
    maxLength = 40, // ���ᨬ� ᨬ����� ��� ����� � ।����
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
    
    // ���ᮭ� ����� �� ����� �����-� �����.
    // �� �⮬ ᢨ��⥫����� ����� ���ᨢ.
    
    // �㦥� ��� ���᪠ ���ᮭ� �� ������ ��� ��᪮�쪨�
    // ������� ���祭��, �, ��� ᫥��⢨�,
    // �㦥� ��� �뢮�� ���ઠ �� ���� ���������饣� ����.
    
    // [0] - �������.
    // [1] - ���.
    // [2] - ����⢮.
    // [3] - ��� ஦�����.
    // [4] - ���.
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
      // ����⪠ ��� �㭪樥� WinAPI.
      // �� �������� x ��� y ᬥ頥� �����.
      
      // �� �맮�� ��� ��㬥�⮢ ���� ��⠭��������
      // ���� ���न����.
      
      // �� �맮�� � ��㬥�⮬ set, � �� move,
      // ����� ��६�饭�� �� �������� ������⢮
      // ����権 �ந�������� ��⠭���� �����
      // �� ������� ����樨.
      
      static HANDLE consoleID = GetStdHandle(STD_OUTPUT_HANDLE);
      
      if(mode == move) {
          if (x != 0)
              cursor.X += short(x); // �⮫���
          
          if (y != 0)
              cursor.Y += short(y); // ��ப�
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
      // ������ �������?
      key.code = char(_getch());
      
      // �� �뫠 ᯥ樠�쭠� ������?
      if (_kbhit()) {
          key.isSpecial = true;
          key.code = char(_getch());
      }
      
      return key;
  }
  
  
  namespace Editor {
    // Editor - �����ன��.
    // Editor ᮢ��頥� ��騥 ��楤��� ।���஢���� �����
    // ��� ���������� � ��������� �������饩 ���ᮭ�.
    struct RawPerson {
        // ���� �������� ���ଠ��
        // [0] - �������
        // [1] - ���
        // [2] - ����⢮
        // [3] - ��� ஦�����
        // [4] - ���
        char fields[5][maxLength] = {};
        
        // ���짮��⥫� ���⥫ �������� � ������� ����
        // ��� �� ��࠭�� ।����㥬�� ���ᮭ�?
        bool isSubmit = false;
    };
    enum EditFields {
        surName,
        name,
        middleName,
        birthday,
        gender
    };
    
    constexpr COORD defaultCoord = {27, 2}; // ������ "䠬����"
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
        submitError, // �� ��࠭���� ���ᮭ�.
        tooLongField,
        wrongSymbol,
        comboWrong, // � ᨬ��� ������, � ���� ��� ��� ��⠢��.
        nothingRemove, // �᫨ ���������� 㤠���� ᨬ���.
    } editError;
    enum ExternalErrors {
        noExternalErrors,
        similarPersonNotFound
    } externalError;
    
    inline void printEditMenu() {
        // ����� ���� ��뢠��� ��楤��
        //      "                       �   ������ ���ᮭ�   �                       "
        
        //      "                       �     ���� 㤠�塞?    �                       "
        
        //      "                       �   ���� ।����㥬?  �                       "
        //      "                       � ��������� ���ᮭ� �                       "
        
        //      "                       �   ���ਨ �롮ન   �                       "
        cout << "  ������������������������������������������������������������������Ļ" << endl;
        cout << "  �               �������:                                           �" << endl;
        cout << "  �                   ���:                                           �" << endl;
        cout << "  �              ����⢮:                                           �" << endl;
        cout << "  � �������� (��.��.����):                                           �" << endl;
        cout << "  � ��� (��稭�|���騭�):                                           �" << endl;
        cout << "  ������������������������������������������������������������������Ķ" << endl;
        cout << "  �                                                                  �" << endl;
        cout << "  ������������������������������������������������������������������Ķ" << endl;
        cout << "  �               [ ] ����� � ����   [ ] ���⢥न��                 �" << endl;
        cout << "  ������������������������������������������������������������������ļ" << endl;
        //      "             �訡��. ���� �� ����������� ����� �����४⭮            "
        
        cursor = defaultCoord;
        moveCursor();
    }
    
    /* --- ��� ��६�頥� ����� �� ।����㥬� ���� � ������� ।���� --- */
    inline void handling_ShiftUp_OnLastName() {
        // ��६��⨬ ����� �� �ࠢ���騥 ������
        // � ���⠢�� ���� ���������.
        moveCursor(backCoordX, controlButtons, set);
        cout << 'x';
        moveCursor(); // ���� � ��砫쭮� ���������, �� x.
    }
    inline void handling_ShiftUp_OnMiddle(const RawPerson& rawP) {
        --cursor.Y;
        int nextField = cursor.Y - surNameY; // ����稬 ������ ⥪�饣� raw-���� ���ᮭ�.
        
        cursor.X = defaultCoord.X + slen(rawP.fields[nextField]);
        moveCursor();
    }
    inline void handling_ShiftUp_OnControl(const RawPerson& rawP) {
        // ������ �⬥�� �� "�����" ��� "���⢥न��".
        // �.�. ����� ��⠭���������� �� �� ����
        // 㦥 � �㦭�� ����樨, � ���� ���� ᨬ���:
        cout << ' ';
        
        // ��६��⨬�� �� ���� ���� ���ᮭ�,
        // �� ��᫥���� ������� �㪢�.
        moveCursor(defaultCoord.X + slen(rawP.fields[gender]), genderY, set);
    }
    void shiftUp(const RawPerson& rawP) {
        if (cursor.Y == controlButtons) // ���ᮭ �� ������ "�����" ��� "�⬥��"
            handling_ShiftUp_OnControl(rawP);
        
        else if (cursor.Y > surNameY) // ���-� � �।��� ����
            handling_ShiftUp_OnMiddle(rawP);
        
        else  // ��筮 �� ��ࢮ� �㭪�
            handling_ShiftUp_OnLastName();
    }
    
    inline void handling_ShiftDown_OnMiddle(const RawPerson& rawP) {
        ++cursor.Y;
        
        int nextField = cursor.Y - surNameY; // ����稬 ������ ⥪�饣� ���� � ���ᨢ�.
        cursor.X = defaultCoord.X + slen(rawP.fields[nextField]);
        moveCursor();
    }
    inline void handling_ShiftDown_OnPreControl() {
        // ��६��⨬ ����� � ���⠢�� ���� ��������� �����
        moveCursor(backCoordX, controlButtons, set);
        cout << 'x';
        moveCursor(); // ���� ����� �� ᨬ��� x.
    }
    inline void handling_ShiftDownEnter_OnPreControl(){
        // ��६��⨬ ����� � ���⠢�� ���� ��������� �����
        moveCursor(submitCoordX, controlButtons, set);
        cout << 'x';
        moveCursor(); // ���� ����� �� ᨬ��� x.
    }
    inline void handling_ShiftDown_OnControl() {
        // ������ �⬥�� �� "�����" ��� "���⢥न��".
        // �.�. ����� ��⠭���������� �� �� ����
        // 㦥 � �㦭�� ����樨, � ���� ���� ᨬ���:
        cout << ' ';
        
        cursor = defaultCoord;
        moveCursor();
    }
    void shiftDownEnter(const RawPerson& rawP){
        // ��� � �� ᠬ��, �� � � �㭪樨 ����.
        // �������� ⮫쪮 ��ࠡ�⪠ preControl.
        
        if (cursor.Y < genderY) // ���-� � �।��� ����
            handling_ShiftDown_OnMiddle(rawP);
        
        else if (cursor.Y == genderY) // �� ��᫥���� �㭪�
            handling_ShiftDownEnter_OnPreControl();
        
        else // ����� ��⠭����� �� "�����" ��� "�⬥��"
            handling_ShiftDown_OnControl();
    }
    void shiftDown(const RawPerson& rawP) {
        if (cursor.Y < genderY) // ���-� � �।��� ����
            handling_ShiftDown_OnMiddle(rawP);
        
        else if (cursor.Y == genderY) // �� ��᫥���� �㭪�
            handling_ShiftDown_OnPreControl();
        
        else // ����� ��⠭����� �� "�����" ��� "�⬥��"
            handling_ShiftDown_OnControl();
    }
    
    inline void handling_MoveLeft_Field(const RawPerson& rawP) {
        if (defaultCoord.X < cursor.X) // ����� � �।��� ����
            --cursor.X;
        
        else if (defaultCoord.X == cursor.X)  // ����� � ��砫� ����
            cursor.X = defaultCoord.X + slen(rawP.fields[cursor.Y - surNameY]);
        
        moveCursor();
    }
    inline void handling_MoveLeft_ControlButtons() {
        // ������ ����� ���� �����, ���⠢�� �����.
        cout << ' ';
        
        if (cursor.X == backCoordX) // �� �� ������ "�����"
            cursor.X = submitCoordX;
        else
            cursor.X = backCoordX;
        
        moveCursor(); // ��६��⨬ �� ����� ����.
        cout << 'x';
        moveCursor(); // ���� ����� ���⭮ �� ᨬ��� x.
        
    }
    void moveLeft(const RawPerson& rawP) {
        if (cursor.Y < controlButtons) // ����� ���-� �� ।����㥬�� ����
            handling_MoveLeft_Field(rawP);
        
        else // ����� �� �ࠢ����� ������� ।���஢����
            handling_MoveLeft_ControlButtons();
    }
    
    inline void handling_MoveRight_Field(const RawPerson& rawP) {
        if (defaultCoord.X + slen(rawP.fields[cursor.Y - surNameY]) > cursor.X)
            ++cursor.X; // ����� �� ���-� � �।��� ���� ।���஢����
        
        else // ����� �� � ���� ���� ।���஢����
            cursor.X = defaultCoord.X;
        
        moveCursor();
    }
    inline void handling_MoveRight_ControlButtons() {
        // ������ ����� �⬥�� ��������� ����� � ��⠭���� �����
        cout << ' ';
        
        if (cursor.X == submitCoordX) // �� �� ������ "���⢥न��"
            cursor.X = backCoordX;
        else
            cursor.X = submitCoordX;
        
        moveCursor(); // �� ����� ���� ᤢ����.
        cout << 'x';
        moveCursor(); // ���� ����� �� ᨬ��� x.
        
    }
    void moveRight(const RawPerson& rawP) {
        if (cursor.Y < controlButtons) // ����� ���-� �� ।����㥬�� ����
            handling_MoveRight_Field(rawP);
        
        else // ����� �� �ࠢ����� �������
            handling_MoveRight_ControlButtons();
        moveCursor();
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* ---           �������� ᨬ����� �� �����            --- */
    inline void removeSymbol(char field[], int remSymPos){
        // ����� ��室���� "�" 㤠�塞�� ᨬ����, �.�. ��। ���.
        for (int i = remSymPos; i < slen(field); ++i)
            field[i] = field[i + 1];
        
        // ������� ��������� ��ப�.
        cout << &field[remSymPos];
        
        // ����襬 � ���� �஡��, �⮡� ����᪨ ����� ��⠢訩�� ᨬ���.
        cout << ' ';
        
        // ���� ����� ���⭮, �.�. �� ᤢ����� ��᫥ �뢮�� �஡���.
        moveCursor();
    }
    
    void handler_DeleteRemove(RawPerson& rawP){
        // ��������� ᨬ���� � ���ᨢ�, ����� �㦭� 㤠����
        int remSymPos = cursor.X - defaultCoord.X;
        int curField = cursor.Y - surNameY;
        
        // ��᫥ ����� ������ ���� ��� �� ���� ᨬ���.
        // �����, ������ 㤠�塞��� ᨬ���� �� ������
        // ��뫠���� �� ��᫥���� ����� ��ப�.
        if(remSymPos == slen(rawP.fields[curField]) || cursor.Y == controlButtons){
            editError = nothingRemove;
            return;
        }
        
        // ������ � � ���᮫�, � � ���ᨢ�.
        removeSymbol(rawP.fields[curField], remSymPos);
    }
    void handler_BackspaceRemove(RawPerson& rawP){
        // ����稬 ��������� ᨬ���� � ���ᨢ�.
        int remSymPos = cursor.X - defaultCoord.X - 1;
        
        // ��। ����஬ ������ ���� ��� �� ���� ᨬ���.
        // �� �� ����� ��室����� � ��砫� ����.
        // �����, �᫨ ������ 㤠�塞��� ᨬ���� -1, � �� �訡��.
        int curField = cursor.Y - surNameY;
        if(remSymPos == -1 || cursor.Y == controlButtons){
            editError = nothingRemove;
            return;
        }
        
        // �.�. ����� ᥩ�� ��᫥ 㤠�塞��� ᨬ����,
        moveCursor(-1, 0); // ��६��⨬ ��� �� 㤠�塞� ᨬ���.
        
        // ������ ᨬ��� � � ���᮫�, � � ���ᨢ�.
        removeSymbol(rawP.fields[curField], remSymPos);
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    /* ---           ���������� ᨬ����� � ����            --- */
    void insertSym(char field[], int symPos, char sym) {
        // ��। �맮��� �⮩ �㭪樨 �㦭� �஢����
        // ����������� ��⠢�� ᨬ����.
        
        // �⮤����� ᨬ���� ��ࠢ�.
        for (int i = slen(field); i >= symPos; --i)
            field[i + 1] = field[i];
        
        // ��⠢�� ᨬ���.
        field[symPos] = sym;
        
        // �뢥��� ᨬ���� ��᫥ ��⠢������� �����⥫쭮.
        cout << field + symPos;
        
        moveCursor(1, 0); // ��६��⨬ ����� ��᫥ ��⠢������� ᨬ����.
    }
    
    inline bool isCorrectSymbol(char sym) {
        return isalpha(sym) || isdigit(sym) ||
               ('�' <= sym && sym <= '�')   ||
               sym == '�' || sym == '�'   ||
               sym == '.' || sym == '-'   ||
               sym == ' ';
    }
    inline bool isSpaceFree(char field[], int rightLength){
        return slen(field) < rightLength;
    }
    bool setInsertErrors(RawPerson& rawP, char sym, int rightBorder){
        int curField = cursor.Y - surNameY; // ������ ���� �� ⥪�饬 ��������� �����.
        
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
        // ����饥 ��������� ����� - ���� ��⠢�� ᨬ���� � ���ᨢ.
        int symPos = cursor.X - defaultCoord.X;
        int curField = cursor.Y - defaultCoord.Y;
        
        // ����⢨� ��⠢��:
        // 1) �஢�ਬ, ���४�� �� ᨬ���.
        // 2) �஢�ਬ, �� ���� ��� ��⠢�� ��� ����.
        if(setInsertErrors(rawP, sym, maxLength))
            return; // ���� �訡��? �⬥��� ��⠢��.
        
        // 3) �᫨ ��� ���, � ��⠢�� ᨬ��� ᭠砫�
        //    � ���ᨢ, � ��⮬ ���� ���ᨢ�, ��稭�� �
        //    ������� ᨬ����, �ᯥ�⠥�.
        insertSym(rawP.fields[curField], symPos, sym);
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* --- ��� ��ࠡ��뢠�� ����⨥ Enter � ����� ।���� � �� ������� --- */
    inline bool checkDate(int day, int month, int year) {
        // TODO: ������ ࠡ���� � ⥪�饩 ��⮩.
        return 1 <= day && day <= 31 &&
               1 <= month && month <= 12 &&
               1800 <= year && year <= currentYear;
    }
    inline bool checkGender(const char* gender) {
        return myStrCmp(gender, "��稭�") || myStrCmp(gender, "���騭�");
    }
    bool isCorrectInfo(RawPerson& rawP) {
        int day, month, year;
        int numbersInDate = sscanf(rawP.fields[birthday], "%d.%d.%d", &day, &month, &year);
        
        // ��⠢�塞 ����������� �� ��������� �� ����
        
        // �᫨ ��� �� ������� (numbersInDate == 0), �����,
        // ��� �㤥� �ய�饭� �� ᮧ����� ���ᮭ�.
        if(slen(rawP.fields[birthday]) > 0 || numbersInDate == 3)
            if (!checkDate(day, month, year))
                return false; // �訡�� � ᨭ⠪�� ����.
        
        if(slen(rawP.fields[gender]) != 0)
            if (!checkGender(rawP.fields[gender]))
                return false;
        
        return true; // ��� � �� ���� ���४��.
    }
    
    bool handler_Enter(RawPerson& rawP){
        // ��।����, ��࠭��� �� ��ꥪ�.
        // �����, ����⨢��, ����⨥ Enter ������ �஢��஢���
        // ���室 �� ᫥���饥 ����; �� "���⢥ত����"
        // ����� �� ��᫥���� ����, �㦭� ��ॡ���� ���짮��⥫�
        // �� ������ ��࠭���� ���ᮭ�.
        
        // �㭪�� ��।����, �ॡ���� �� �த������ ।���஢���� ���ᮭ�.
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
                    throw(__LINE__); // �� ������ �ᯮ�짮������
            }
        else {
            shiftDownEnter(rawP);
            
            isEdit = true;
        }
        
        return isEdit;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* --- ������ ��ࠡ��稪 ����⢨� ���짮��⥫� � ।����  --- */
    inline void printDoneData(const RawPerson& rawP){
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        for(int i = surName; i <= gender; ++i) {
            cout << rawP.fields[i];
            moveCursor(0, 1);
        }
        // ��६��⨬ ����� � ����� ��ࢮ�� ����.
        moveCursor(defaultCoord.X + slen(rawP.fields[surName]), defaultCoord.Y, set);
    }
    
    inline void setExternalErrors(){{}
        if(externalError != noExternalErrors) {
            COORD tempCoord = cursor;
            
            moveCursor(errorCoordX, errorCoordY, set);
            switch (externalError) {
                case similarPersonNotFound          :
                    cout << "     �訡��. ���ᮭ� � ������묨 ����묨 �� ������� � ��     ";
                    break;
                default :
                    throw(__LINE__); // �� ������ �ᯮ�짮������
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
                    cout << "   �訡��. ���� ��� ��᪮�쪮 �� ����������� ����� �����४⭮  ";
                    break;
                case tooLongField                 :
                    cout << "           �訡��. ����񭭠� ���ଠ�� ᫨誮� ������          ";
                    break;
                case wrongSymbol                  :
                    cout << "              �訡��. �������⨬� ᨬ��� ��� �����             ";
                    break;
                case comboWrong :
                    cout << "   �訡��. �������⨬� ᨬ��� ��� �����; ��� ���� ��� �����   ";
                    break;
                case nothingRemove                :
                    cout << "                   �訡��. ��祣� ��� 㤠����                   ";
                    break;
                default                           :
                    throw(__LINE__); // �� ������ �ᯮ�짮������
            }
            
            moveCursor(tempCoord.X, tempCoord.Y, set);
        }
    }
    inline void removeErrors() {
        // ����� �訡�� �� ᫥���饬 ����⨨ ������
        if(editError != noEditErrors || externalError != noExternalErrors) {
            COORD tempCoord = cursor;
            
            moveCursor(errorCoordX, errorCoordY, set); // ��頥� ��� ���� �訡�� ।����
            cout << "                                                                " << endl;
            moveCursor(tempCoord.X, tempCoord.Y, set);
            
            editError = noEditErrors;
            externalError = noExternalErrors;
        }
    }
    void core_EditPerson(RawPerson& rawP) {
        printEditMenu();
        // ����� �������� �� �६���� ��ꥪ� ���㪢����,
        // ���⮬� ����� ���������⥩ ��� ।���஢���� � �� ������ �����.
        // ��⮢� ��� � ������ ��࠭����� �� ���४⭮��.
        
        // ����� ��६���� ����� �� ।����㥬��� ����.
        // ����� ��६���� ����� �� ࠧ�� ����,
        // �� �⮬ ����񭭮� ��࠭����.
        // ����� ��⠢����/㤠���� �㪢�.
        
        // �᫨ �� �室 ������ 㦥 ����������� ���ᮭ�, �뢥��� �� ����.
        if(rawP.isSubmit)
            printDoneData(rawP);
        
        // ������ ��ࠡ��稪 ।���஢����.
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
                    default        : // �᫨ �� ����� �� ���� �ࠢ����� ������
                        handler_InsertSym(rawP, key.code);
                        break;
                }
            
            setErrors();
            
        }
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* ---     �������⥫�� �㭪樨, �ᯮ����騥 ।����     --- */
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
    // "����७���" �㭪樨 ���᪠ ����� ���ᮭ� �� ��᪮�쪨� ��宦��
    
    /* --- ��� ��室�� ������� ���ᮭ, �������� ������ --- */
    inline bool checkSimilar(const Person& person, const RawPerson& rawP) {
        // �஢�ਬ, �����筠 �� �᪮��� ��筮��� ������
        // ���� false, ��� ⮫쪮 ��� �� ���� �� ����������� �����
        // �� �㤥� ᮮ⢥��⢮���� �������饬� ��ꥪ��
        
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
        
        // �ன���� �� �ᥬ �������騬 ���ᮭ�� � �ࠢ��� �� � ������
        for (int i = 0; i < countPersons; ++i)
            if (checkSimilar(persons[i], rawP))
                similar.number[similar.n++] = i;
        
        return similar;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* --- ��� ��ᨢ� �뢮��� ᯨ᮪ �������� ���ᮭ --- */
    inline void printTablePersonsCap(){
        cout << "  ���������������������������������������������������������������������������Ļ" << endl
             << "  �  #  �    �������    �      ���      �      ����⢮      �  �����  � ��� �" << endl
             << "  ���������������������������������������������������������������������������Ķ" << endl;
    }
    inline void printSeparatorLine(){
        cout << "  ���������������������������������������������������������������������������Ķ" << endl;
    }
    inline void printEndTable(){
        cout << "  ���������������������������������������������������������������������������ļ" << endl;
    }
    
    enum LimitsField {
        maxSurNameLength = 15,
        maxNameLength = 15,
        maxMiddleNameLength = 20,
        maxBirthdayLength = 10,
        maxGenderLength = 5
    };
    string reformName(const char* name, LimitsField limit){
        // �� ����頥��� ��� � ����? ��ࠢ�� �����.
        string str = name;
        
        if(str.size() > limit) {
            str[limit - 0] = '\0';
            str[limit - 1] = '.';
            str[limit - 2] = '.';
            str[limit - 3] = '.';
        }
        else // �������� �஡����� ���� ��� ���४⭮�� �⮡ࠦ����
            while(str.size() < limit)
                str += ' ';
        
        return str.c_str();
    }
    string reformDate(const char date[]){
        int day, month, year;
        sscanf(date, "%d.%d.%d", &day, &month, &year);
        
        // �� 墠⠥� ����饣� ���? �������, ��� �����.
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
        return (myStrCmp(gender, "��稭�") ? "  �  " : "  �  ");
    }
    string centerDash(LimitsField limit){
        // � ����ᨬ��� �� ��⭮�� ����� ����,
        // �⤠� ���� ����, ���� ��� ���ઠ.
        string str;
        
        if(limit%2 == 0){
            for(int i = 0; i < limit/2 - 1; ++i)
                str += ' ';
            str += "��";
            for(int i = limit/2 + 1; i < limit; ++i)
                str += ' ';
        }
        else {
            
            for(int i = 0; i < limit/2 ; ++i)
                str += ' ';
            str += "�";
            for(int i = limit/2 + 1; i < limit; ++i)
                str += ' ';
        }
        
        return str;
    }
    void printPerson(Person& curPerson, int index){
        // FIXME: ������� �㭪��.
        // �뢮� ��������� ����� ���ᮭ�.
        // ���������騥 ���� �����塞 ���ઠ�� � 業���㥬 ��.
        
        static_assert(getCountDigits(maxCountPersons, 0) <= 3, "Table persons will be broken");
        printf("  � %3d �", index);
        
        if(curPerson.isFieldAviable[Editor::surName])
            cout << reformName(curPerson.surName, maxSurNameLength);
        else cout << centerDash(maxSurNameLength);
        cout << '�';
        
        if (curPerson.isFieldAviable[Editor::name])
            cout << reformName(curPerson.name, maxNameLength);
        else cout << centerDash(maxNameLength);
        cout << '�';
        
        if (curPerson.isFieldAviable[Editor::middleName])
            cout << reformName(curPerson.middleName, maxMiddleNameLength);
        else cout << centerDash(maxMiddleNameLength);
        cout << '�';
        
        if(curPerson.isFieldAviable[Editor::birthday])
            cout << reformDate(curPerson.birthday);
        else cout << centerDash(maxBirthdayLength);
        cout << '�';
        
        if(curPerson.isFieldAviable[Editor::gender])
            cout << reformGender(curPerson.gender);
        else cout << centerDash(maxGenderLength);
        cout << '�' << endl;
    }
    
    void selectSimilarPersons_ToPrint (Similar& similar){
        printTablePersonsCap();
        
        for(int i = 0; i < similar.n; ++i){
            Person& curPerson = persons[similar.number[i]];
            printPerson(curPerson, similar.number[i]);
            if(i + 1 != similar.n) // �⮡� ⠡��� ��ᨢ� �����稢�����
                printSeparatorLine();
        }
        
        printEndTable();
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* --- ��� ��� ���짮��⥫� ����� ���� �� ��宦�� ���ᮭ --- */
    static const COORD defaultCoord = {0, 6};
    inline void printSimilarPersonsCap(){
        cout << "                              ��宦�� ���ᮭ�:                                " << endl;
    }
    
    inline void printCursor(){
        cout << "->"; // ��ꥪ� cursor �� ������.
        
        // �� ����᪨ ��� ��������� ����������, ���� ���⭮.
        moveCursor();
    }
    inline void removeCursor(){
        // ���⪠ 㦥 � �㦭�� ��������� ��� ��࠭�� �����
        cout << "  "; // ��ꥪ� cursor �� ������.
        
        // �� ����᪨ ��� ��������� ����������, ���� ���⭮.
        moveCursor();
    }
    
    inline void moveUp(Similar& similar){
        removeCursor();
        
        // ��।������ �࠭�筠� ���न���,
        // �� ���ன ����� ���� �����
        short downBorder = short(defaultCoord.Y + similar.n*2 - 2);
        
        if(cursor.Y > defaultCoord.Y)
            moveCursor(0, -2);
        else
            moveCursor(defaultCoord.X, downBorder, set);
        
        printCursor();
    }
    inline void moveDown(Similar& similar){
        removeCursor();
        
        // ��।������ �࠭�筠� ���न���,
        // �� ���ன ����� ���� �����
        short downBorder = short(defaultCoord.Y + similar.n*2 - 2);
        
        if(cursor.Y < downBorder)
            moveCursor(0, 2);
        else
            moveCursor(defaultCoord.X, defaultCoord.Y, set);
        
        printCursor();
    }
    
    inline int handlingEnter(Similar& similar){
        // �����頥� ������ ��࠭��� ���ᮭ�.
        
        // /2, �.�. ���ᮭ� �ᯮ�������� �१ ࠧ����⥫�.
        return similar.number[(cursor.Y - defaultCoord.Y) / 2];
    }
    
    enum UserChoice {
        cancelChoice = -1,
    };
    int core_RefineChoice(Similar &similar){
        printSimilarPersonsCap(); // ���ᠭ�� ⠡����.
        
        selectSimilarPersons_ToPrint(similar);
        
        // ��⠭���� ����� �� ��ࢮ� ��� ⠡����.
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        printCursor();
        
        while(true){
            PressedKey key = whatPressed();
            
            // ��� ��� ᮢ������� ����� ������ ᯥ樠���� � ������ ������.
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
        cout << "                       �   ������  ���ᮭ�   �                       " << endl;
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
        
        // ���⢥न� �� ���짮��⥫�, �� ���
        // �������� ���ᮭ� � �� ��� ���⥫ �������� ���⭮ � ����?
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
    /* --- �㭪樨 㤠����� ���ᮭ�, 㪠������ ���짮��⥫�� --- */
    
    inline void printEnterRemoveCap() {
        system("CLS");
        cout << "                       �     ���� 㤠�塞?    �                       " << endl;
    }
    inline void printChoiceSimilarRemoveCap(){
        system("CLS");
        cout << "                        ����� ���ᮭ� ᫥��� 㤠����?                        " << endl << endl;
    }
    
    inline void removePerson(int whoRemove) {
        // �������� �ᥬ ���ᮭ ���� ������ �� ���.
        for(int i = whoRemove; i < countPersons-1; ++i)
            persons[i] = persons[i+1];
        
        --countPersons;
    }
    bool core_removePerson (int) {
        if(countPersons == 0){
            coreAnswer = failedRemove;
            return true; // � ���� �롮� ��⮤� �롮�
        }
        
        // �ਭ樯 ࠡ���:
        //
        // I.   ������� ����� �� �᪮��� ���ᮭ� ��� 㤠�����
        //      �� ���짮��⥫�.
        //    * �� �⪠�� ������� �����, �����訬 ��楤���.
        //
        // II.  ������� ������⢮ ��宦�� ���ᮭ
        //      1) �� ������⢨� ��宦�� ���ᮭ,
        //         ������� ������⨬ �� �⮬ � ।����,
        //         ��३�� � �㭪�� I.
        //      *  �� �⪠�� �� �롮�, ���� ���짮��⥫�
        //         �� �㭪� I.
        //      2) �᫨ ���ᮭ� ����, �������� �� ������.
        //      3) �᫨ ��宦�� ���ᮭ ����� �����,
        //         ����� ���짮��⥫� ����� �㦭��.
        //
        // III. ������� ���ᮭ�, �������� � ������� ����.
        
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
                    continue; // ����ᨬ ���४�� ����� ��� ࠧ.
                }
                
                // II. 2)
                if(similar.n == 1) {
                    whoRemove = similar.number[0];
                    break; // ��३�� � 蠣� III.
                }
                    
                    // II. 3)
                else if(similar.n > 1){
                    // ������� ���짮��⥫� ����� ����
                    printChoiceSimilarRemoveCap();
                    // ����稬 �⢥� �� ���짮��⥫�
                    whoRemove = Find::core_RefineChoice(similar);
                    
                    // II. 3) *
                    if(whoRemove == Find::UserChoice::cancelChoice)
                        continue; // ����ᨬ ����� ��� ࠧ.
                    else
                        break; // � ������� ����.
                }
                
                throw(__LINE__); // �� ������ �ᯮ�짮������
            }
            else {
                // I. *
                coreAnswer = canceledRemove;
                return true; // � ������� ����, �⬥�� �롮� ��⮤� �롮�.
            }
        }
        
        // III.
        removePerson(whoRemove);
        coreAnswer = successRemove;
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* --- �㭪樨 ��� 㤠����� ���ᮭ� �१ �� ������ --- */
    bool handler_IndexRemove(int index){
        // �த������ �롮� ��⮤� �롮� ��� �롮� ���ᮭ� 㦥 ᤥ���?
        if(index == -1)
            return true; // �த������ �롮� ��⮤� �롮�.
        
        removePerson(index);
        coreAnswer = successRemove;
        
        return false; // � ������� ���� ������.
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* --- �㭪樨 ��� �롮� ��⮤� �롮� 㤠����� ���ᮭ� --- */
    inline void printSelectChoiceRemoveModeCap(){
        moveCursor(-1, -2); // �� defaultCoord � 蠯��.
        cout << "  ���ᮡ 㤠����� ���ᮭ�?  ";
        moveCursor(1, 2); // ���⭮ � defaultCoord.
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
  }
  namespace Change {
    /* �㭪樨 ��� ���᪠ ���ᮭ� �१ �� ���� */
    inline void printEnterDataCap() {
        system("CLS");
        cout << "                       �   ���� ।����㥬?  �                       " << endl;
    }
    inline void printSimilarEditCap(){
        system("CLS");
        cout << "              ����� ���ᮭ� �� ��� ।����㥬? [Esc: ��������]              "   << endl << endl;
    }
    inline void printEditDataCap() {
        system("CLS");
        cout << "                       � ��������� ���ᮭ� �                       " << endl;
    }
    
    bool core_FieldEdit(int){
        
        // �ਭ樯 ࠡ���:
        //
        // I.   ������� ����� �� �᪮��� ���ᮭ� ��� ।���஢����
        //      �� ���짮��⥫�.
        //    * �� �⪠�� ������� �����, �����訬 ��楤���.
        //
        // II.  ������� ������⢮ ��宦�� ���ᮭ
        //      1) �� ������⢨� ��宦�� ���ᮭ,
        //         ������� ������⨬ �� �⮬ � ।����,
        //         ��३�� � �㭪�� I.
        //      *  �� �⪠�� �� �롮�, ��३�� ���⭮ � ������� ����.
        //      2) �᫨ ���ᮭ� ����, �������� �� ������.
        //      3) �᫨ ��宦�� ���ᮭ ����� �����,
        //         ����� ���짮��⥫� ����� �㦭��.
        //
        // III. ������� ���� ।���஢���� ��࠭��� ���ᮭ�.
        //      ���� ���ᮭ� ������ �� �६�����, �ॢ�⨢ � "�����".
        //    * �� �⪠�� ���짮��⥫� �� ।���஢���� ���ᮭ�,
        //      ������ � �㭪�� I.
        //
        // IV.  ���࠭���� ���ᮭ� �����⢨��� �� ������ 䫠�� isSubmit,
        //      ����� ��⠭���� ����� Editor::cookData.
        //    * �� �⪠�� �� ��࠭���� ��������� � �������饩 ���ᮭ�,
        //      �멤�� � ������� ����.
        
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
                    continue; // ����ᨬ ���४�� ����� ��� ࠧ.
                }
                    
                    // II. 2)
                else if(similar.n == 1)
                    whoEdit = similar.number[0];
                    // ��३�� � 蠣� III.
                    
                    // II. 3)
                else if(similar.n > 1){
                    // ������� ���짮��⥫� ���� �롮� ��宦�� ���ᮭ.
                    printSimilarEditCap();
                    // ����稬 �⢥� �� ���짮��⥫�.
                    whoEdit = Find::core_RefineChoice(similar);
                    
                    // II. 3) *
                    if(whoEdit == Find::UserChoice::cancelChoice) {
                        coreAnswer = canceledEdit;
                        return false; // ������ � ����.
                    }
                    // else // ��३�� � 蠣� III.
                }
                
                if(whoEdit < 0)
                    throw(__LINE__); // �� ������ �믮�������.
                // III.
                rawP = Editor::toRaw(whoEdit);
                printEditDataCap();
                Editor::core_EditPerson(rawP);
                
                // IV.
                if(rawP.isSubmit) {
                    persons[whoEdit] = Editor::toPerson(rawP);
                    coreAnswer = successEdit;
                    return false; // ����� �㭪樨 �����祭�, � ������� ����.
                }
                else { // IV. *
                    coreAnswer = canceledEdit;
                    return false; // � ������� ����.
                }
                
            }
            else {
                // I. *
                coreAnswer = canceledEdit;
                return false; // � ������� ����.
            }
        }
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    /* �㭪樨 ��� ।���஢���� ���ᮭ� �१ �� ������ */
    bool handler_IndexEdit(int index){
        // �த������ �롮� ��⮤� �롮� ��� �롮� ���ᮭ� 㦥 ᤥ���?
        if(index == -1)
            return true; // �த������ �롮� ��⮤� �롮�.
        
        Editor::RawPerson rawP = Editor::toRaw(index);
        printEditDataCap();
        // ��� �롮� ᤥ���, ������� ���� ।���஢����
        // ��࠭��� ���ᮭ�.
        Editor::core_EditPerson(rawP);
        
        if(rawP.isSubmit){
            persons[index] = Editor::toPerson(rawP);
            coreAnswer = successEdit;
        }
        else coreAnswer = canceledEdit;
        
        return false; // � ������� ���� ������.
    }
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    
    
    /* ���� � �롮஬ ०��� �롮� ���ᮭ� */
    constexpr COORD defaultCoord = {27, 3}; // "���� ���ᮭ�"
    
    inline void printCursor(){
        cout << "->"; // COORD cursor �� ���������.
        moveCursor(); // � default-���������.
    }
    inline void removeCursor(){
        cout << "  "; // COORD cursor �� ���������.
        moveCursor(); // ���� � ��஥ ���������.
    }
    
    inline void printSelectChoiceEditModeCap(){
        moveCursor(-1, -2); // �� defaultCoord � 蠯��.
        cout << "   ���ᮡ �롮� ���ᮭ�?   ";
        moveCursor(1, 2); // ���⭮ � defaultCoord.
    }
    inline void updateMenuItems(){
        moveCursor(-1, 0); // ��������� �� ���� ����� ᪮���.
        
        // � ����㥬 �� �㭪�� ������ ����.
        cout << "[  ] ���� ���ᮭ�            ";
        
        moveCursor(0, 1);
        // HINT:      �������� ����� ���ᮭ�
        cout << "[  ] ������ ���ᮭ�          ";
        
        moveCursor(0, 1);
        cout << "[  ] � ������� ����          ";
        
        // ������ ���� �� "�������", 㤠��� ��� �㭪��.
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
    
    
    namespace MiniEditor { // NOTE: ����ᠭ� ⮫쪮 ࠤ� ��࠭���� ������� ����䥩�.
      // WHITE: �� ᠬ�� ���� ��� ����� 㦠� � ��� ����ᨬ��⥩.
      // ��� ����ᠭ ��ࠡ��稪 ����� ���짮��⥫�� ������ ���ᮭ�.
      // FIXME: �� - �������� Editor, ⮫쪮 � ����� ����.
      
      // NOTE: �� - �⮡� ����� �㦭� �뫮 ������ �� ��������� ������⢠ ���ᮭ.
      static_assert(getCountDigits(maxCountPersons, 0) <= 3, "Table persons will be broken");
      char index[getCountDigits(maxCountPersons, 0)+1] = {};
      constexpr COORD defaultCoord = {short(Change::defaultCoord.X + 4 + 16),
                                      short(Change::defaultCoord.Y + 1)};
      
      inline void printInviteToEnterIndex(){
          // HINT: [  ] ������ ���ᮭ�
          // HINT:  ^
          moveCursor(4, 0); // ��������� �� ��५�窨 ᫥��.
          cout << "������ ������: "; // cursor ��� ��� ��室���� �� +4 ����樨 �� ��५�窨.
          cursor = defaultCoord; // ���९�� ����� ���������.
      }
      inline void handler_Back (){
          // ��६��⨬ ����� �� ⥪���� �������, ��९�襬 �� �� �।�����.
          moveCursor(- slen(index) - 16, 0);
          cout << "������ ���ᮭ�          ";
          
          moveCursor(-4, 0); // ���� ����� ���⭮ �� ����� ��५���.
          removeCursor(); // � 㤠��� ��� ᫥���.
          
          // ���⨬ ������ ������
          for(auto& c: index)
              c = '\0';
      }
      
      inline void moveLeft(){
          // ��६�饭�� ����� ����� � ᪠窮� ��ࠢ�.
          if(defaultCoord.X < cursor.X)
              moveCursor(-1, 0);
          else
              moveCursor(slen(index), 0);
      }
      inline void moveRight(){
          // ��६�饭�� ����� ��ࠢ� � ᪠窮� �����.
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
          // ��������� ᨬ���� � ���ᨢ�, ����� �㦭� 㤠����
          int remSymPos = cursor.X - defaultCoord.X;
          
          // ��᫥ ����� ������ ���� ��� �� ���� ᨬ���.
          // �����, ������ 㤠�塞��� ᨬ���� �� ������
          // ��뫠���� �� ��᫥���� ����� ��ப�.
          if(remSymPos == slen(index)){
              editErrors = errorRemove;
              return;
          }
          
          // ������ � � ���᮫�, � � ���ᨢ�.
          Editor::removeSymbol(index, remSymPos);
      }
      void handler_BackspaceRemove(){
          // ����稬 ��������� ᨬ���� � ���ᨢ�.
          int remSymPos = cursor.X - defaultCoord.X - 1;
          
          // ��। ����஬ ������ ���� ��� �� ���� ᨬ���.
          // �� �� ����� ��室����� � ��砫� ����.
          // �����, �᫨ ������ 㤠�塞��� ᨬ���� -1, � �� �訡��.
          if(remSymPos == -1){
              editErrors = errorRemove;
              return;
          }
          
          // �.�. ����� ᥩ�� ��᫥ 㤠�塞��� ᨬ����,
          moveCursor(-1, 0); // ��६��⨬ ��� �� 㤠�塞� ᨬ���.
          
          // ������ ᨬ��� � � ���᮫�, � � ���ᨢ�.
          Editor::removeSymbol(index, remSymPos);
      }
      void handler_InsertSym(char sym){
          // ����饥 ��������� ����� - ���� ��⠢�� ᨬ���� � ���ᨢ.
          int symPos = cursor.X - defaultCoord.X;
          
          // ����⢨� ��⠢��:
          // 1) �஢�ਬ, ���४�� �� ᨬ���.
          // 2) �஢�ਬ, �� ���� ��� ��⠢�� ��� ����.
          if(!isdigit(sym) || slen(index)+1 > getCountDigits(maxCountPersons, 0)) {
              editErrors = errorInsert;
              return; // ���� �訡��? �⬥��� ��⠢��.
          }
          
          // 3) �஢�ઠ ��� �ᯥ譠? ��⠢�� ᨬ��� ᭠砫�
          //    � ���ᨢ, � ��⮬ ���� ���ᨢ�, ��稭�� �
          //    ������� ᨬ����, �ᯥ�⠥�.
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
                  case errorInsert : cout << "������ �� ����� ���� ����� "; break;
                  case errorEnter  : cout << "������ ������ �����४⥭"; break;
                  case errorRemove : cout << "  ���������� 㤠���� ᨬ��� "; break;
                  default          : throw(__LINE__); // �� ������ �ᯮ�������.
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
          // ����� ����ᠭ�� ���짮��⥫�� ������ ���ᮭ�.
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
                          // �����頥��� � �롮�� ᯮᮡ� �롮�
                          return cancelEnter;
                      case Down   :
                          handler_Back();
                          moveDown();
                          // �����頥��� � �롮�� ᯮᮡ� �롮�
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
                          // �����頥��� � �롮�� ᯮᮡ� �롮�
                          return cancelEnter;
                      case Enter     : isEditingContinue = !isIndexCorrect(); break;
                      case Backspace : handler_BackspaceRemove();  break;
                      default        : // �᫨ �� ����� �� ���� �ࠢ����� ������
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
        if(countPersons == 0){ // �� ���짮��⥫� �⥫ ��������?
            if(type == remove)
                coreAnswer = failedEdit;
            else
                coreAnswer = failedRemove;
            
            return; // � ������� ����.
        }
        
        // ��⠭���� ����� � 蠯�� �������� ����.
        moveCursor(defaultCoord.X, defaultCoord.Y, set);
        
        // ���� ��ࠡ��稪 ��࠭���� ���짮��⥫�� ᮡ���.
        bool (*handler_Enter1)(int);
        bool (*handler_Enter2)(int);
        
        if(type == remove){
            handler_Enter1 = Remove::core_removePerson;
            handler_Enter2 = Remove::handler_IndexRemove;
            Remove::printSelectChoiceRemoveModeCap(); // ������� 蠯��
        }
        else {
            handler_Enter1 = core_FieldEdit;
            handler_Enter2 = handler_IndexEdit;
            printSelectChoiceEditModeCap(); // ������� 蠯��
        }
        
        
        updateMenuItems(); // ������� �㭪�� 㦥 �� �������� ����.
        
        // ���ந� ��ࠡ��� ����⢨� ���짮��⥫� � ������� �롮�.
        enum {fakeArg}; // ��� �맮�� ����⢨�, ���஥ ��ࠫ ���짮��⥫�, ������.
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
                    case backChoice  : return; // ����� � ������� ����
                    default          : throw(__LINE__); // �� ������ �ᯮ�������.
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
        cout << "                                  �� ���ᮭ�:                                " << endl;
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
            if(i + 1 != countPersons) // �⮡� ⠡��� ��ᨢ� �����稢�����
                Find::printSeparatorLine();
        }
        
        Find::printEndTable();
        system("PAUSE");
    }
  }
  namespace Search {
    // ���� � �뢮� �� �� ��� �� ������ ᮢ�����饬� �����.
    inline void printSearchCap(){
        system("CLS");
        cout << "                       �   ���ਨ �롮ન   �                       " << endl;
    }
    
    void core_SimilarSelection() {
        if(countPersons == 0){
            coreAnswer = failedSearch;
            return;
        }
        
        Editor::RawPerson rawP;
        printSearchCap();
        Editor::core_EditPerson(rawP); // ����稬 ���ਨ �⡮� �� ���짮��⥫�.
        
        if (rawP.isSubmit) {
            Find::Similar similar = Find::findSimilar(rawP);
            
            // ������� �� ���� � �� �� �⨬ �����.
            system("CLS"); // �.�. �㭪�� ���� �⮣� �� ������
            Find::printSimilarPersonsCap();
            Find::selectSimilarPersons_ToPrint(similar);
            
            system("PAUSE");
        }
        else
            coreAnswer = cancelSelectionShow;
    }
  }
  
  namespace Main {
    // �ᥣ�� 㪠�뢠�� �� ���� �㭪� �������� ����
    constexpr COORD defaultCoord = {27, 3};
    static_assert(defaultCoord.X == Change::defaultCoord.X &&
                  defaultCoord.Y == Change::defaultCoord.Y,
                  "������� � ��������� �������� ���� �易�� � "
                          "���ﬨ ���������� � 㤠����� ���ᮭ�. "
                          "������� ����� - ������ � ⠬."
                 );
    
    enum MainMenuItems {
        addPerson = 3, //defaultCoord.Y,
        changePerson,
        delPerson,
        delDB,
        seeDB,
        addons,
        leave,
        coreMessagesField = leave + 2 // �.�. ���� ࠧ����⥫쭠� �����
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
        cout << "                        ������������������������������ͻ" << endl;
        cout << "                        �         ������� ����         �" << endl;
        cout << "                        ������������������������������Ķ" << endl;
        cout << "                        � [  ] �������� ���ᮭ� � ��   �" << endl;
        cout << "                        � [  ] �������� ����� ���ᮭ� �" << endl;
        cout << "                        � [  ] �������� ���ᮭ� �� ��  �" << endl;
        cout << "                        � [  ] ���⪠ ��              �" << endl;
        cout << "                        � [  ] ��ᬮ�� �ᥩ ����      �" << endl;
        cout << "                        � [  ] ���� �� �����       �" << endl;
        cout << "                        � [  ] ��室                   �" << endl;
        cout << "                        ������������������������������ĳ" << endl;
        cout << "                        �                              �" << endl;
        cout << "                        ������������������������������ͳ" << endl;
        cout << "                        � ���ᮭ � ���� ������:        �" << endl;
        cout << "                        ������������������������������ͼ" << endl;
        
        moveCursor(defaultCoord.X + 21, defaultCoord.Y + 10, set);
        cout << countPersons;
        
        cursor = defaultCoord;
        printCursor();
        
    }
    
    namespace CheatCodes {
      namespace StreamInput {
        inline void printExplanation(){
            system("CLS");
            cout << "����� ����� ����� ᯨ᮪ ���ᮭ � ⠪�� �ଠ�: "<< endl;
            cout << "�������, ���, ����⢮, ��� ஦�����(��.��.����), ��� (�\\�);" << endl;
            
            cout << "�� ᮮ⢥��⢨� �ଠ� �⢥砥� ���짮��⥫�." << endl;
            cout << "��室 � ������� ���� �� ������ Enter. ������ ᯨ᮪ ���ᮭ: " << endl;
        }
        
        inline void getNextField(char* personField, char separator){
            char enterField[maxLength];
            int countSyms = 0;
            
            while(cin.peek() != separator){
                enterField[countSyms++] = char(cin.get());
            }
            cin.get(); // ������㥬 ࠧ����⥫�.
            
            // ����� �� �஡��� ��᫥ ����⮩.
            while(isspace(cin.peek()) && cin.peek() != '\n')
                cin.get();
            
            // �����訬 �ਭ�⨥ ���� ���ᮭ�.
            enterField[countSyms] = '\0';
            strcpy(personField, enterField);
        }
        Editor::RawPerson& fillRawPerson(Editor::RawPerson& rawP){
            // �������, ��� ����⢮, ��� ஦����� � ��� � ����� 䫠����.
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
            
            cin.get(); // ������ \n �� ��⮪� ��᫥ ����� ��� ���ᮭ.
            
            // ���� ���� ���⭮, �.�. ��᫥ ������ ��५��
            // �� �뫮 �������஢��� ������ 祣�-����.
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
            // �������� ��४������� � ��⮪��� ���� ���ᮭ.
            
            // ��ଠ� ����� ������:
            // �������, ���, ����⢮, ��� ஦�����(��.��.����), ��� (�\�);
            
            // ��室 � ������� ���� �����⢫���� ��᫥
            // ������ Enter.
            static const char cheat[] = "UDDDUDDDUUUUUUUD";
            static int n = -1; // �������� ����� ��.
            
            ++n;
            switch (key) {
                case Up   : handling_Up  (cheat, n, sizeof(cheat)-2); break;
                case Down : handling_Down(cheat, n, sizeof(cheat)-2); break;
                default   : throw (__LINE__); // �� ������ �ᯮ�짮������
            }
            
        }
      }
      
      void handler_Cheats(Keys key) {
          // ��ࠢ�� ������� ������� �� �� ��ࠡ��稪� �⮢.
          
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
            --cursor.Y; // ����� �� ���� ��ப�
        
        else // �᫨ � ᠬ�� �����
            cursor.Y = leave;
        
        printCursor();
        
        CheatCodes::handler_Cheats(Up);
    }
    inline void moveDown() {
        removeCursor();
        
        if (cursor.Y < leave)
            ++cursor.Y; // ���� �� ���� ��ப�
        
        else // �᫨ � ᠬ�� ����
            cursor.Y = defaultCoord.Y;
        
        printCursor();
        
        CheatCodes::handler_Cheats(Down);
    }
    
    inline bool handling_Enter() {
        // ��ࠡ�⠥� �롮� ���짮��⥫�.
        // ����� �⢥�, �த������ �� ࠡ��� ��.
        
        // ��᫥ �믮������ ࠡ��� �㭪樨, ���� ������� ���� ���⭮
        
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
            default           : throw(__LINE__); // �� ������ �ᯮ�짮������
        }
        
    }
    
    inline void printCoreMessage(){
        
        if(coreAnswer != nothingHappens){
            COORD tempCoord = cursor;
            moveCursor(defaultCoord.X - 1, coreMessagesField, set);
            
            switch (coreAnswer) {
                case successAdd          : cout << "  ����� ���ᮭ� ���������   "; break;
                case failedAdd           : cout << "      ���� ����� ���      "; break;
                case successEdit         : cout << "      ���ᮭ� ��������      "; break;
                case failedEdit          : cout << "      ������ ��������       "; break;
                case successRemove       : cout << "      ���ᮭ� 㤠����       "; break;
                case failedRemove        : cout << "      ������ 㤠����        "; break;
                case successRemoveDB     : cout << "    ���� ������ ��饭�     "; break;
                case failedRemoveDB      : cout << "       ��祣� �����       "; break;
                case failedSee           : cout << "     ���� ������ ����      "; break;
                case failedSearch        : cout << "       ������ �᪠��        "; break;
                
                case canceledAdd         : cout << "    ���������� �⬥����     "; break;
                case canceledEdit        : cout << "  ������஢���� �⬥����   "; break;
                case canceledRemove      : cout << " �������� ���ᮭ� �⬥����  "; break;
                
                case cancelSelectionShow : cout << "  �롮��� ����� �⬥��  "; break;
                
                default                  : throw(__LINE__); // �� ������ �ᯮ�짮������
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
        // ������� ���� �ࠢ����� ��
        printMainMenu();
        bool isProgramWork = true;
        
        while (isProgramWork) {
            PressedKey key = whatPressed();
            removeMessage();
            
            // ��� ��� ᮢ������� ����� ������ ᯥ樠���� � ������ ������.
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
        cout << "�訡��, �믮������ ���諮 �� ��ப� " << numberString << endl;
        system("PAUSE");
    }
    return 0;
}