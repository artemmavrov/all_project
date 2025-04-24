#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>

using namespace std;


void generate_test(int test_number, int max_days, int max_price, int max_k) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> days_dist(1, max_days);
    uniform_int_distribution<int> price_dist(1, max_price);
    uniform_int_distribution<int> k_dist(1, max_k);

    int n = days_dist(gen);
    int k = k_dist(gen);

    vector<int> prices(n);
    for (int i = 0; i < n; i++) {
        prices[i] = price_dist(gen); // Заполняем цены
    }

    // Сохраняем тест в файл
    ofstream test_file("test" + to_string(test_number) + ".txt");
    test_file << k << endl; // Записываем k
    for (int price : prices) {
        test_file << price << ", "; // Записываем цены
    }
    test_file << endl;
    test_file.close();
}

// Основная программа
int main() {
    int num_tests; // Количество тестов
    cout << "Enter number of tests: ";
    cin >> num_tests;

    int max_days, max_price, max_k;
    cout << "Enter max days, max price, and max k: ";
    cin >> max_days >> max_price >> max_k;

    for (int i = 1; i <= num_tests; i++) {
        generate_test(i, max_days, max_price, max_k);
    }

    cout << "Tests generated!" << endl;
    return 0;
}
