#include <vector>
#include <string>
#include <coniow.h>

using namespace std;

class Editor{
   int X, Y;
   vector<string> Text;//����� ��� ��������������
   bool isEditing;//���� true �� ����� �������������� ����� ���������
   int HighlightColor;//���� ���������
   int TextColor;//���� ������
   int Left, Top, Right, Bottom;// ������� ����
   void (*Func)(int);
   
   public:
   Editor(int left, int top, int right, int bottom, int text_color, int highlight_color);//����������� 
   void Editing();//��������������
   void setEditing(bool a){isEditing = a;}//����� ������ ��������� ��� ��������������   
   int NumberRows(){return Text.size();}//���������� ����� 
   int CurrentNumberRow(){return Y;}//����� ������� ������ 
   int CurrentNumberSymbol(){return X;}//����� �������� ������� � ������ 
   void  GoToRow(int row, int symbol);// ������� �� ������ � ������� number
   string GetRow(int number);//�������� ������ � ������� number 
   void ReplaceRow(string s, int number);//�������� ������ c ������� number  
   void DeleteRow(int number);//������� ������ � ������� number   
   void AddRow(string s, int number);//�������� ������ � ������ number     
   void AddSymbols(string s, int number);//�������� �������   
   void DeleteSymbols(int number);//������� ������� ������� � ��������   
   void HighlightRow(int to, int from);//�������� ������ ������� � to � ���������� from   
   void KeyboardProcessing(void (*f)(int)){Func = f;};//��������� ������   
   void DrawText(int to, int from);//��������� ������
};