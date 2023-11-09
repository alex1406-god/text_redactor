#include <vector>
#include <string>
#include <coniow.h>

using namespace std;

class Editor{
   int X, Y;
   vector<string> Text;//текст для редактирования
   bool isEditing;//если true то режим редактирования иначе просмотра
   int HighlightColor;//цвет выделения
   int TextColor;//цвет текста
   int Left, Top, Right, Bottom;// размеры окна
   void (*Func)(int);
   
   public:
   Editor(int left, int top, int right, int bottom, int text_color, int highlight_color);//конструктор 
   void Editing();//редактирование
   void setEditing(bool a){isEditing = a;}//Выбор режима просмотра или редактирования   
   int NumberRows(){return Text.size();}//количество строк 
   int CurrentNumberRow(){return Y;}//номер текущей строки 
   int CurrentNumberSymbol(){return X;}//номер текущего символа в строке 
   void  GoToRow(int row, int symbol);// перейти на строку с номером number
   string GetRow(int number);//Получить строку с номером number 
   void ReplaceRow(string s, int number);//заменить строку c номером number  
   void DeleteRow(int number);//удалить строку с номером number   
   void AddRow(string s, int number);//добавить строку с нмером number     
   void AddSymbols(string s, int number);//добавить символы   
   void DeleteSymbols(int number);//удалить символы начиная с текущего   
   void HighlightRow(int to, int from);//выделить строки начиная с to и заканчивая from   
   void KeyboardProcessing(void (*f)(int)){Func = f;};//обработка клавиш   
   void DrawText(int to, int from);//отрисовка текста
};