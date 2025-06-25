#define _USE_MATH_DEFINES 
#include <iostream> 
#include <cmath> 
using namespace std;
int main() {
    double a, b, c, alpha, sin_x, x;
    cout << "Enter the values of a, b, and c: ";
    cin >> a >> b >> c;
    if (abs(c) > sqrt(a * a + b * b)) {
        cout << "No roots" << endl;
    }
    else if (a == 0 && b == 0 && c == 0) {
        cout << "Infinite roots" << endl;
    }
    else if (abs(c) == sqrt(a * a + b * b)) {
        cout << "One root: x = " << M_PI/2 - acos(a / sqrt(a * a + b * b)) << endl;
    }
    else if (abs(c) < sqrt(a * a + b * b)) {
        alpha = acos(a / sqrt(a * a + b * b));
        sin_x = c / sqrt(a * a + b * b);
        x = asin(sin_x) - alpha;
        cout << "Roots of the equation:" << endl;
        cout << "x1 = " << x << endl;
        x = M_PI - x;
        cout << "x2 = " << x << endl;
    }
    return 0;
}
