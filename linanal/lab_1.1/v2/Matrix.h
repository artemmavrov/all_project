#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "best_file.cpp"

using namespace std;

class Matrix {
private:
    void write_matrix();
    void read_matrix(fstream& file);
public:
    int n, m;
    double scalar = 1.0;
    vector<double> elements;
    vector<int> indexI;
    vector<int> indexJ;

    Matrix() = default;
    Matrix(int n, int m, vector<double> elements = {}, vector<int> indexI = {}, vector<int> indexJ = {}, string path = "");

    int get_trace();
    int get_element(int i, int j);
};

void write_map(Matrix& A, map<pair<int, int>, double>& map);
Matrix sum_of_matrix(Matrix& A, Matrix& B);
void multiply_scalar(int scalar, Matrix& A);
vector<double> get_vertical(Matrix& A, int j);
vector<double> get_horizontal(Matrix& A, int i);
double multiply_vectors(vector<double>& a, vector<double>& b);
Matrix multiply_matrix(Matrix& A, Matrix& B);

#endif // MATRIX_H
