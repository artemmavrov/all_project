#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "custom_functions.cpp"
#define double long double
#define endl '\n'
using namespace std;
const double error_rate = 0.01;
double ditohomy(double A, double B, double epsilon)
{
   
    //Пример использования другой функции 
    //cout << "Enter the highest degree of a polynomial \n";
    //int deg;
    //cin >> deg;
    //Polinomial function = Polinomial(deg);
    MiddleComplexityFunction function;
    double a_next = 0;
    double b_next = 0;
    while (true)
    {
        double y = (A - epsilon + B) / 2.0;
        double z = (A + epsilon + B) / 2.0;
        if(function.calculate(y) <= function.calculate(z))
        {
            a_next = A;
            b_next = z;
        }else
        {
            a_next = y;
            b_next = B;
        }
        double L2_power = (b_next - a_next);
        if(L2_power <= epsilon + error_rate)
        {
            return (a_next + b_next) / 2.0;
        }
        A = a_next;
        B = b_next;
        cout << A << ' ' << B << L2_power << endl;
    }
    return 0;
}
void ditohomy_init()
{
    double A, B;
    cout << "Enter the left and right boundaries of the uncertainty  \n";
    cin >> A >> B;

    double epsilon;
    cout << "Enter epsilon \n";
    cin >> epsilon;
    cout << ditohomy(A, B, epsilon);
}
int main()
{
    cout << fixed << setprecision(20);
    ditohomy_init();
}
