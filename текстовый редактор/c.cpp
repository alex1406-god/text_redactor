#include "c.hpp"

void Editor::DrawText(int to, int from){
   if(to < 0 || to > NumberRows() || from < 0 || from > NumberRows()) return;
   window(Left, Top, Right, Bottom);
   textcolor(TextColor);
   if(to > from) swap(to, from);
   gotoxy(1, to + 1);
   for(; to <= from; to++){
      clreol();
      cprintf(Text[to].c_str());
      cprintf("\r\n");
   }
   GoToRow(CurrentNumberRow(), CurrentNumberSymbol());
}

void Editor::DeleteRow(int number = -1){
   if(number == -1) number = CurrentNumberRow();
   else if(number < 0 || number > NumberRows()) return;
   Text.erase(Text.begin() + number);
}

string Editor::GetRow(int number = -1){
   if(number == -1) number = CurrentNumberRow();
   else if(number < 0 || number > NumberRows()) return "";
   return Text[number];
}

void Editor::ReplaceRow(string s, int number = -1){
   if(number == -1) number = CurrentNumberRow();
   else if(number < 0 || number > NumberRows()) return;
   Text[number] = s;
}

Editor::Editor(int left, int top, int right, int bottom, int text_color = 0x7, int highlight_color = 0x70){
   X = Y = 0;
   TextColor = text_color;
   HighlightColor = highlight_color;
   Left = left;
   Top = top;
   Right = right;
   Bottom = bottom;
}

void Editor::GoToRow(int row, int symbol = 0){
   if(row < NumberRows() && row >= 0){
      if(symbol < 0){
         X = Text[row - 1].size();
         Y = row - 1;
      }
      else if(symbol > Text[row].size())
         if(wherey() - 1 != row){
            X = Text[row].size();
            Y = row;
         }
         else{
            if(CurrentNumberRow() == NumberRows() - 1 && Text[NumberRows() - 1].size() == CurrentNumberSymbol()) return;
            X = 0;
            Y = row + 1;
         }
      else{
         X = symbol;
         Y = row;
      }
      gotoxy(X + 1, Y + 1);
   }
}

void Editor::DeleteSymbols(int number = 1){
   if(number <= Text[CurrentNumberRow()].size() - CurrentNumberSymbol())
      Text[CurrentNumberRow()].erase(CurrentNumberSymbol(), number);
}

void Editor::HighlightRow(int to, int from){
   textbackground(HighlightColor);
   DrawText(to, from);
   textbackground(BLACK);
}

void Editor::AddSymbols(string s, int number = -1){
   if(number == -1) number = CurrentNumberRow();
   else if(number < 0 || number > NumberRows()) return;
   
   for(int i = CurrentNumberSymbol(); i < Text[number].size(); i++)
      s += Text[number][i];
   Text[number].erase(CurrentNumberSymbol(), Text[number].size() - CurrentNumberSymbol());
   Text[number] += s;
}

void Editor::AddRow(string s, int number = -1){
   if(number == -1) number = CurrentNumberRow();
   else if(number < 0 || number > NumberRows()) return;
   
   Text.resize(Text.size() + 1);
   for(int i = Text.size() - 1; i > number ; i--)
      ReplaceRow(Text[i - 1], i);
   
   ReplaceRow(s, number);
}

void Editor::Editing(){
   int c = getkbm();
   if(!isEditing && c != KEY_ESC) return;
   static bool insert = false;
   string s;
   
   if(c >= 32 && c <= 255){
      if(insert)
         DeleteSymbols();
      AddSymbols(s = c);
      DrawText(CurrentNumberRow(), CurrentNumberRow());
      GoToRow(CurrentNumberRow(), CurrentNumberSymbol() + 1);
   }
   else{
      switch(c){
         case KEY_SPECIAL + KEY_F3:{//удалить символ
            if(GetRow() == ""){
               DeleteRow();
               delline();
               break;
            }
            DeleteSymbols(1);
            DrawText(CurrentNumberRow(), CurrentNumberRow());
         }break;
         case KEY_SPECIAL + KEY_F4:{//удалить строку
            DeleteRow(-1);
            delline();
         }break;
         case KEY_SPECIAL + KEY_LEFT :{//влево
            GoToRow(CurrentNumberRow(), CurrentNumberSymbol() - 1);
         }break;
         case KEY_SPECIAL + KEY_RIGHT :{//вправо
            GoToRow(CurrentNumberRow(), CurrentNumberSymbol() + 1);
         }break;
         case KEY_SPECIAL + KEY_UP :{//вверх
            GoToRow(CurrentNumberRow() - 1, CurrentNumberSymbol());
         }break;
         case KEY_SPECIAL + KEY_DOWN :{//вниз
            GoToRow(CurrentNumberRow() + 1, CurrentNumberSymbol());
         }break;
         case KEY_SPECIAL + KEY_F10 :{//выход
            clrscr();
            exit(0);
         }break;
         case KEY_SPECIAL + KEY_F5 :{//выделить
            int start = CurrentNumberRow();
            HighlightRow(start, start);
            while((c = getkbm()) != KEY_SPECIAL + KEY_F5 ){
               if(c == KEY_SPECIAL + KEY_DOWN){
                  if(CurrentNumberRow() < start)
                     DrawText(CurrentNumberRow(), CurrentNumberRow());
                  GoToRow(CurrentNumberRow() + 1, CurrentNumberSymbol());
               }
               if(c == KEY_SPECIAL + KEY_UP){
                  if(CurrentNumberRow() > start)
                     DrawText(CurrentNumberRow(), CurrentNumberRow());
                  GoToRow(CurrentNumberRow() - 1, CurrentNumberSymbol());
               }
                  HighlightRow(start, CurrentNumberRow());
            }
            DrawText(0, NumberRows() - 1);
         }break;
         case KEY_ENTER :{//перенос строки
            s = GetRow();
            DeleteSymbols(s.size() - CurrentNumberSymbol());
            s.erase(0, CurrentNumberSymbol());
            AddRow(s, CurrentNumberRow() + 1);
            insline();
            DrawText(CurrentNumberRow(), CurrentNumberRow() + 1);
         }break;
         case KEY_SPECIAL + KEY_F6 :{//режим вставки и замены
            insert = !insert;
            if(insert) _setcursortype(_SOLIDCURSOR);
            else _setcursortype(_NORMALCURSOR);
         }break;
         default:{
            if(Func) Func(c);
         }break;
      }
   }
}