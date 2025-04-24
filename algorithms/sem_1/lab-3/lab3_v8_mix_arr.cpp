#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

void test_maker(int n){
    ofstream test;
    test.open("C:/Users/artem/Desktop/лабы/алгосы/test.txt");
    test << n << endl;
    int rand_int;
    for (int i = 0; i < n; i++){
        rand_int =  rand();
        test << rand_int << endl;
    }
    test.close();
}

int main(){
    test_maker(pow(10, 7));
    cout << "test have been created";
    ifstream test;
    test.open("C:/Users/artem/Desktop/лабы/алгосы/test.txt");
    int n;
    test >> n;
    vector <int> mix_arr(n);
    vector <bool> b_mix_arr(n);
    int rand_pos, element;
    long long t;
    for (int i = 0; i < n; i++){
        test >> element;
        t = rand() * time(0) * 95651;
        rand_pos = t % n;
        while (b_mix_arr[rand_pos]){
            rand_pos += 1;
            if (rand_pos == n){
                rand_pos = 0;
            }
        }
        mix_arr[rand_pos] = element;
        b_mix_arr[rand_pos] = 1;
    }
    test.close();
    ofstream ans;
    ans.open("C:/Users/artem/Desktop/лабы/алгосы/ans.txt");
    for (int i = 0; i < n; i++){
        ans << mix_arr[i] << endl;
    }
    ans.close();
    return 0;
}
