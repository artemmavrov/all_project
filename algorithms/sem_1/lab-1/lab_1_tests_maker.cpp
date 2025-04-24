#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

int main(){
    random_device rd;
    mt19937 gen(rd());
    string alph = "qwertyuiopasdfghjklzxcvbnm"; //������� ��� �������� �����
    int n = pow(10, 3); //���-�� �����
    ofstream test; //�������� ��������� ����� ��� ���������
    test.open("C:/Users/artem/Desktop/����/������/test_1.txt"); // ������������ ����������
    test << n << endl; //���� ���-�� ����� � ����
    string str; //���������� ��� ������ �����
    uniform_int_distribution<> distrib_size_str(1, 1000); //��������� ���������� ���-�� �������� � ������
    uniform_int_distribution<> dustrib_char(0, 25); //�������� ���������� ��� ������� �� ��������

    for (int i = 0; i < n; i++){
        short size_str = distrib_size_str(gen); //���������� ���������� ����� ���-�� ��������� ������
        for (short j = 0; j < size_str; j++){
            short _char = dustrib_char(gen); // ��������� ���������� ������� �� ��������
            str.push_back(alph[_char]); //���������� �������� ������
        }
        test << str << endl; // ���������� ������ � ����
        str.clear(); // ������ ������
    }
    test.close(); // �������� �����
    return 0;
}
