#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    const int N = 10000;
    int n = 0;
    double x, y;
    for (int i = 0; i <= N; i++) {
        x = -1 + 2.0 * i / N;
        for (int j = 0; j <= N; j++) {
            y = -1 + 2.0 * j / N;
            if ((y * y + x * x) < 1) {
                n++;
            }
        }
    }
    cout << "True result: " << M_PI << endl;
    cout << "Our result: " << n * 4.0 / pow(N+1,2) << endl;
    return 0;
}
