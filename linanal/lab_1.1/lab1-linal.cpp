#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <windows.h>
#include <stdexcept>
#include "best_file.cpp"

using namespace std;

class dense_matrix { // Плотная матрица для проверки
private:
    int rows, cols; // Размеры матрицы
    vector<vector<double>> matrix; // Матрица

public:
    // Конструктор, загружающий плотную матрицу из файла
    dense_matrix(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file");
        }

        file >> rows >> cols; // Чтение размеров матрицы
        matrix.resize(rows, vector<double>(cols));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> matrix[i][j];
            }
        }

        file.close();
    }

    // Получение следа плотной матрицы
    double get_tace_dense() const {
        if (rows != cols) {
            throw invalid_argument("Trace is defined only for square matrices");
        }
        int trace = 0;
        for (int i = 0; i < rows; ++i) {
            trace += matrix[i][i];
        }
        return trace;
    }

    // Получение элемента плотной матрицы по индексу (индексация с 1)
    double get_element_dense(int i, int j) const {
        if (i < 1 || i > rows || j < 1 || j > cols) {
            throw out_of_range("Index out of range");
        }
        return matrix[i - 1][j - 1];
    }

    // Сложение плотных матриц
    dense_matrix addition_matrix_dense(const dense_matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions do not match for addition");
        }

        dense_matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    // Умножение плотной матрицы на скаляр
    dense_matrix multiply_scalar_dense(double scalar) const {
        dense_matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.matrix[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    // Умножение плотных матриц
    dense_matrix multiply_matrix_dense(const dense_matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication");
        }

        dense_matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    dense_matrix(int r, int c) : rows(r), cols(c) {
        matrix.resize(rows, vector<double>(cols, 0));
    }

     vector<vector<double>> to_vector_dense() const {
        return matrix;
    }
};

void write_matrix(vector<vector<double>>& matrix, int& n, int& m) {
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
	}
}

int main()
{
	Matrix a = Matrix(0, 0, {}, {}, {}, "C:/Users/artem/Desktop/labs/linanal/lab_1/tests/matrix_0.txt");
	Matrix b = Matrix(0, 0, {}, {}, {}, "C:/Users/artem/Desktop/labs/linanal/lab_1/tests/matrix_1.txt");
    int n = 10;
    int m = 10;
    pair<double, string> hui = get_determinant(a);

    cout << hui.first;
    cout << hui.second;

}

