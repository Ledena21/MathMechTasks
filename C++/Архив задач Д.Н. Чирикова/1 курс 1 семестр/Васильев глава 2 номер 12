#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double g = 9.8, dt = 0.001;
    double v, alpha, t, V, u, x = 0, y = 0, gam, m, k, T;
    int n = 0;
    cout << "enter V: ";
    cin >> V;
    cout << "enter alpha: ";
    cin >> alpha;
    alpha *= M_PI / 180;
    cout << "enter t: ";
    cin >> t;
    cout << "enter gamma: ";
    cin >> gam;
    cout << "enter weight: ";
    cin >> m;
    k = gam / m;
    v = V * cos(alpha);
    u = V * sin(alpha);
    do {
        n++;
        x += v * dt;
        y += u * dt;
        v -= k * v * dt;
        u -= dt * (g + k * u);
    } while (n * dt < t);
    cout << "y = " << y << endl;
    cout << "y = " << (g / k + V * sin(alpha)) / k * (1 - exp(-k * t)) - g * t / k << endl;
    cout << "x = " << x << endl;
    cout << "x = " << V * cos(alpha) / k * (1 - exp(-k * t)) << endl;
    return 0;
}
