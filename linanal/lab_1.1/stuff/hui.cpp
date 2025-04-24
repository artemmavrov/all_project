#include <iostream>
#include "lab1-linal.cpp"

using namespace std;

int main() {
    Matrix a = Matrix(0, 0, {}, {}, {}, "name_file1.txt");
    Matrix b = Matrix(0, 0, {}, {}, {}, "name_file2.txt");
    multiply_scalar(2.0, a);
    Matrix c = sum_of_matrix(a, b);
}
int get_trace_correct(int& n, int& m, array<array<int, m>, n>& matrix) {
    long long trace = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m.size(); j++) {
            trace += matrix[i][j];
        }
    }

    return trace;
}

int get_element_correct(int& n, int& m, array<array<int, m>, n>& matrix, int& i, int& j,) {
    return matrix[i - 1][j - 1];
}

array<array<int, m>, n> sum_of_matrix_correct(int& n1, int& m1, array<array<int, m>, n>& matrix1, int& n2, int& m2, array<array<int, m>, n>& matrix2) {
    if (n1 != n2 || m1 != m2) {
        return throw invalid_argument("Matrix dimensions do not match for multiplication");
    }

    array<array<int, m>, n> result;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

array<array<int, m>, n> multiply_scalar_correct(int& n1, int& m1, array<array<int, m>, n> matrix, int& scalar) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] *= scalar;
        }
    }

    return matrix;
}

array<array<int, m>, n> multiply_matrix_correct(int& n1, int& m1, array<array<int, m>, n>& matrix1, int& n2, int& m2, array<array<int, m>, n>& matrix2) {
    if (n1 != n2 || m1 != m2) {
        return throw invalid_argument("Matrix dimensions do not match for multiplication");
    }

    array<array<int, m>, n> result;

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; ++j) {
            for (int k = 0; k < n1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}
