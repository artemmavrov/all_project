#include <iostream>
#include <fstream>
#include <random>

using namespace std;

void create_test(int number) {
    int n = 1e4;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1e4);

    ofstream test;
    test.open("test" + to_string(number) + ".txt");
    long long sum = 0;
    int element;

    for (int i = 0; i < n - 1; ++i) {
        element = dis(gen);
        sum += element;
        test << element << ", ";
    }

    int last_number = dis(gen);
    if ((sum + last_number) % n != 0) {
        last_number += n - (sum + last_number) % n;
    }
    test << last_number;
    test.close();
}

int main() {
    int numbers;
    cin >> numbers;

    for (int i = 0; i < numbers; ++i) {
        create_test(i);
    }
    return 0;
}
