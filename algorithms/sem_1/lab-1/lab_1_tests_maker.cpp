#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

int main(){
    random_device rd;
    mt19937 gen(rd());
    string alph = "qwertyuiopasdfghjklzxcvbnm"; //алфавит для создания строк
    int n = pow(10, 3); //кол-во строк
    ofstream test; //создания перемнной файла для изменения
    test.open("C:/Users/artem/Desktop/лабы/алгосы/test_1.txt"); // присваевание переменной
    test << n << endl; //ввод кол-ва строк в файл
    string str; //переменная для записи строк
    uniform_int_distribution<> distrib_size_str(1, 1000); //ссоздания генератора кол-ва символов в строке
    uniform_int_distribution<> dustrib_char(0, 25); //создания генератора для символа из алфавита

    for (int i = 0; i < n; i++){
        short size_str = distrib_size_str(gen); //переменная рандомного числа кол-ва элементво строки
        for (short j = 0; j < size_str; j++){
            short _char = dustrib_char(gen); // перемнная рандомного символа из алфавита
            str.push_back(alph[_char]); //добавления символав строку
        }
        test << str << endl; // добавление строки в файл
        str.clear(); // чистка строки
    }
    test.close(); // закрытие файла
    return 0;
}
