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
    for (int i = 0; i < n; i++){
        test << rand() << endl;
    }
    test.close();
    cout << "test have been created" << endl;
}

int main(){
    test_maker(pow(10, 7));
    ifstream test;
    test.open("C:/Users/artem/Desktop/лабы/алгосы/test.txt");
    int n;
    test >> n;
    vector <int> mix_arr(n);
    vector <int> free_pos;
    for (int i = 0; i < n; i++){
        free_pos.push_back(i);
    }
    int element, last_free_pos;
    long long rand_pos;
    for (int len_free_pos = (n - 1); len_free_pos >= 0; len_free_pos--){
        test >> element;
        rand_pos = ((rand() * time(0) * 95651) % (len_free_pos + 1));
        mix_arr[free_pos[rand_pos]] = element;
        last_free_pos = free_pos[len_free_pos];
        free_pos[len_free_pos] = free_pos[rand_pos];
        free_pos[rand_pos] = last_free_pos;
        free_pos.pop_back();
    }
    test.close();
    cout << "end";
    ofstream ans;
    ans.open("C:/Users/artem/Desktop/лабы/алгосы/ans.txt");
    for (int i = 0; i < n; i++){
        ans << mix_arr[i] << endl;
    }
    ans.close();
    return 0;
}
