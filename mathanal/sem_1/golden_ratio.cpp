#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "custom_functions.cpp"
#define double long double
#define endl '\n'
using namespace std;
const double ratio = (3.0 - sqrt(5)) / 2.0;
double golden_ratio(double A, double B, double epsilon)
{
    // Начальные вычисления
    double y = A + ratio * (B - A);
    double z = A + B - y;
    //Пример использования другой функции 
    //cout << "Enter the highest degree of a polynomial \n";
    //int deg;
    //cin >> deg;
    //Polinomial function = Polinomial(deg);
    MiddleComplexityFunction function;
    while (true)
    {
        // Вычисляем значения функции в y и z
        double f_y = function.calculate(y);
        double f_z = function.calculate(z);

        if (f_y <= f_z)
        {
            // на этом моменте в описании лабораторной работы ошибка
            // там yk+1 вычисляется по Bk, но нужно по Bk+1 (как в этом коде)
            B = z;
            z = y;
            y = A + B - z; 
        }
        else
        {
            A = y;
            y = z;
            z = A + B - y;
        }
        if (abs(B - A) <= epsilon)
        {
            return (A + B) / 2.0;
        }        
    }
    return 0;
}
void golden_ratio_init()
{
    double A, B;
    cout << "Enter the left and right boundaries of the uncertainty  \n";
    cin >> A >> B;

    double epsilon;
    cout << "Enter epsilon \n";
    cin >> epsilon;
    cout << golden_ratio(A, B, epsilon);
}
int main()
{
    cout << fixed << setprecision(20);
    golden_ratio_init();
}
