#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

double min_metric = 1e9;  // 8 ����
array<vector<double>, 5> ans; //5 * 24 �����
int n; //4 �����

pair <short int, vector <double>> test_maker(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(-2147483647, 2147483646);

    short int n = (rand() * time(0)) % 16; //����������� ���� �������� � 25 �� 16, �� 5^25 ����� ���������� ������� �����; 2 �����
    if (n < 5){
        n = 5;
    }
    n = 9;
    vector <double> elements(n); //24 �����

    for (short int i = 0; i < n; i++){
        double random_element = dist(gen); //8 ����
        elements[i] = random_element;
    }

    return make_pair(n, elements); // 24 + 4 �����
}

void print_clusters(array<vector<double>, 5> clusters){
    for (short int i = 0; i < 5; i++){
        cout << "[";
        for (short int j = 0; j < clusters[i].size(); j++){ //2 �����
            if (j == clusters[i].size() - 1){
                cout << clusters[i][j] << "]";
            }else{
                cout << clusters[i][j] << ", ";
            }
        }
        if (i != 4){
            cout << ", ";
        }
    }
}

double mean(const vector<double> &v){
    double sum = 0; //8 ����

    for (const double &x: v){ //O(N), N - ������ ��������
        sum += x;
    }

    return sum / v.size();
}

double cluster_metric(const vector<double> &v){
    double metric = 0; //8 ����
    const double current_mean = mean(v); //8 ����
    for (const double &x: v){
        metric += std::abs((x - current_mean)); //O(N), N - ������ ��������
    }
    return metric;
}

double clusters_metric(const array<std::vector<double>, 5> &cluster_distribution){
    double metric = 0; //8 ����

    for (const vector<double> &cluster: cluster_distribution){ //O(N), N - ������ ��������
        metric += cluster_metric(cluster);
    }

    return metric;
}

void enumerate_clusters(array<vector<double>, 5> clusters, const vector<double> elements, int index){ //O(5^N), N - ������ ��������
    if (index == elements.size()) {
        double size_metric = clusters_metric(clusters); //8 ����
        if (min_metric > size_metric){
            min_metric = size_metric;
            ans = clusters;
        }

        return;
    }
    for (short int i = 0; i < 5; i++) { //2 �����
        clusters[i].push_back(elements[index]);
        enumerate_clusters(clusters, elements, index + 1);
        clusters[i].pop_back();
    }
}

int main() {
    pair <short int, vector <double>> input_data = test_maker();
    n = input_data.first;
    vector<double> elements = input_data.second;
    array<vector<double>, 5> clusters;

    enumerate_clusters(clusters, elements, 0);
    print_clusters(ans);
    return 0;
}
//����� ������������ ������ � ������ �������� 228 * 5^N, N - ������ ��������
//����� ��������� O(5^N * L), N - ������ ��������, L - ��������� �������� �������

