#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    const double g = 9.8;
    double H, v, alpha, t, T, x, y;
    cout << "H = ";
    cin >> H;
    cout << "v = ";
    cin >> v;
    cout << "alpha = ";
    cin >> alpha;
    cout << "t = ";
    cin >> t;
    alpha = alpha * M_PI / 180;
    T = v * sin(alpha) / g * (1 + sqrt(1 + 2 * g * H / pow(v, 2) / pow(sin(alpha), 2)));
    x = t < T ? v * t * cos(alpha) : v * T * sin(alpha);
    y = t < T ? H + v * t * sin(alpha) - g * pow(t, 2) / 2 : 0;
    cout << "x(t) = " << x << "; y(t) = " << y << "." << endl;
    return 0;
}
