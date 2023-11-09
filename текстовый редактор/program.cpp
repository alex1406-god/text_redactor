#include "program.hpp"

Editor editor(4, 10, 100, 100, GREEN, BLUE);
Editor help(1, 1, 100, 100, WHITE, BLUE);

void OpenFile(Editor &a, string path){
   ifstream file;
   string str;
   file.open(path);
   for(int i = 0; !file.eof(); i++){
      getline(file, str);
      a.AddRow(str, i);
   }
   file.close();
}

void Save(){
   ofstream file;
   file.open("input.txt");
   for(int i = 0; i < editor.NumberRows() - 1; i++){
      file << editor.GetRow(i) << "\n";
   }
   file << editor.GetRow(editor.NumberRows() - 1);
   file.close();
}

void Help(){
   clrscr();
   editor.setEditing(false);
   help.DrawText(0, help.NumberRows() - 1);
}

void Back(){
   clrscr();
   editor.setEditing(true);
   editor.DrawText(0, editor.NumberRows() - 1);
   gotoxy(1, editor.NumberRows() + 2); 
   cprintf("F1:������ F2:��������� F3:������� ������ F4:������� ������ F5:��������\r\nF6:����� ������� � ������ F10:�����");
   gotoxy(editor.CurrentNumberSymbol() + 1, editor.CurrentNumberRow() + 1);
}

void KeyFunc(int c){
   switch(c){
      case KEY_SPECIAL + KEY_F1://������
         Help();
      break;
      case KEY_SPECIAL + KEY_F2://���������
         Save();
      break;
      case KEY_ESC://����� �� ������� ������
         Back();
      break;
   }
}

int main(){
   clrscr();
   
   editor.setEditing(true);
   OpenFile(editor, "input.txt");
   OpenFile(help, "help.txt");
   editor.KeyboardProcessing(KeyFunc);
   
   editor.DrawText(0, editor.NumberRows() - 1);
   gotoxy(1, editor.NumberRows() + 2);
   cprintf("F1:������ F2:��������� F3:������� ������ F4:������� ������ F5:��������\r\nF6:����� ������� � ������ F10:�����");
   gotoxy(1, 1);
   
   while(true){
      editor.Editing();
   }
   return 0;
}