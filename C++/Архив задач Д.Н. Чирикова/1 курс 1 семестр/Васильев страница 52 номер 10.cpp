#define _USE_MATH_DEFINES_
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    const double G = 6.672e-11, M = 5.96e24, R = 6.37e6;
    int h;
    double g;
    cout << "Enter h: ";
    cin >> h;
    g = G * M / pow(R + h, 2);
    cout << "g = " << g << endl;
    return 0;
}
