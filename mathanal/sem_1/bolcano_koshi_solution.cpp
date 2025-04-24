#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "custom_functions.cpp"
#define double long double
#define INF 1e9
#define endl '\n'
using namespace std;
const double epsilon = 0.0001;
const double delta = 0.0002;
double calculateStandardDeviation(double correctAnswer, double algorithmAnswer) {
    double mean = (correctAnswer + algorithmAnswer) / 2.0;
    double stdDev = sqrt((pow(correctAnswer - mean, 2) + pow(algorithmAnswer - mean, 2)) / 2.0);
    return stdDev;
}
int getSign(MiddleComplexityFunction &function, double &arg)
{
    return function.calculate(arg) >= 0 ? 1 : -1;
}
double bolcano_koshi(double A, double B, MiddleComplexityFunction &function)
{  
    int leftsign = getSign(function, A);
    int rightsign = getSign(function, B);
    if(leftsign == rightsign)
    {
        return INF;
    }
    while (true)
    {
        double mid = (A + B) / 2.0;
        double result = function.calculate(mid);
        bool condition = leftsign == -1 && rightsign == 1 ? result < 0 : result >= 0;
        if(condition)
        {
            A = mid;
        }
        else
        {
            B = mid;
        }
        if(abs(B - A) <= epsilon)
        {
            return mid;
        }
    }
    
    return INF;
}
void alg(double A, double B)
{
    vector<double> ans;
    double bound = A + delta;
    MiddleComplexityFunction function = MiddleComplexityFunction();
    while (bound < B)
    {
        if(getSign(function, A) != getSign(function, bound))
        {
            ans.push_back(bolcano_koshi(A, bound, function));
        }
        A = bound;
        bound += delta;
    }
    cout << "Roots: ";
    for(int i = 0; i < ans.size(); i++)
    {  
        if(ans[i] != INF)
        {
            cout << ans[i] << ' ';
        }
    }
    cout << '\n';
    
}
void bolcano_koshi_init()
{
    double A, B;
    cout << "Enter the left and right boundaries of the uncertainty  \n";
    cin >> A >> B;
    alg(A, B);
}
int main()
{
    cout << fixed << setprecision(20);
    bolcano_koshi_init();
}
