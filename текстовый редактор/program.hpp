#include "c.hpp"
#include <fstream>
#include <iostream>

void Help();//Вывод помощи на экран
void Save();//Сохранить изменения
void Back();//Возврат из функции помощи
void OpenFile(Editor &a, string path);//Запись данных из файла
void KeyFunc(int c);//Обработка клавиш