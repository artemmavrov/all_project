#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include<cmath>
#include <random>

 using namespace std;

int test_maker(int m){
    random_device rd;
    mt19937 gen(rd());
    string alph = "qwertyuiopasdfghjklzxcvbnm";
    ofstream test; //�������� ��������� ����� ��� ���������
    test.open("C:/Users/artem/Desktop/����/������/test.txt");
    test << m << endl; //���� ���-�� ����� � ����
    string str; //���������� ��� ������ �����
    uniform_int_distribution<> distrib_size_str(1, 1000); //��������� ���������� ���-�� �������� � ������
    uniform_int_distribution<> dustrib_char(0, 25); //�������� ���������� ��� ������� �� ��������

    for (int i = 0; i < m; i++){
        short size_str = distrib_size_str(gen); //���������� ���������� ����� ���-�� ��������� ������
        for (short j = 0; j < size_str; j++){
            short _char = dustrib_char(gen); // ��������� ���������� ������� �� ��������
            str.push_back(alph[_char]);
        }
        test << str << endl; // ���������� ������ � ����
        str.clear();
    }
    test.close();
    return 0;
}

 int main(){
     test_maker(pow(10, 3));
     unordered_map <string, short> repeats;
     ifstream input_file;
     input_file.open("C:/Users/artem/Desktop/����/������/test.txt");
     int n;
     input_file >> n; //+4 ����
     string str; //+25 + size_str

     for (int i = 0; i < n; i++){ //+4 �����
        getline(input_file, str);
        if (repeats.find(str) != repeats.end()){
            repeats[str]++;
        }else{
        repeats[str] = 1;
        }
        str.clear();
     }
     //+(25 + size_str + 8 + 8 + 2) * n ����

     input_file.seekg(0);
     input_file >> n;
     ofstream ans;
     ans.open("C:/Users/artem/Desktop/����/������/ans.txt");

     for (int i = 0; i < n; i++){
        getline(input_file, str);
        ans << repeats[str] << endl;
    }
    ans.close();
    return 0;
    //�� ����� 4 * n ����
    //������������ ���� ���� ����������� ����� ���������� repeats � �����
    //4 + 4 +(25 + �������(size_str) + 8 + 8 + 2) * n ����
 }
