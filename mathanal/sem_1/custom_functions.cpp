#include <iostream>
#include <cmath>
#include <vector>
#define double long double
#define endl '\n'
using namespace std;
struct Polinomial
{
    Polinomial() = default;
    vector<double> coefs;
    Polinomial(int deg)
    {
        this->coefs.resize(deg + 1, 0);
        for(int i = 0; i < this->coefs.size(); i++)
        {
            cout << "Enter coefficient " << i + 1 << '\n';
            cin >> coefs[i];
        }
    }
    double calculate(double x)
    {
        double result = 0;
        for(int i = 0; i < this->coefs.size(); i++)
        {
            result += coefs[i] * pow(x, i);
        }
        return result;
    }
};
struct MiddleComplexityFunction
{
    MiddleComplexityFunction() = default;
    double calculate(double x)
    {
        return pow(x - 2, 2) + sin(3 * x);
    }
};