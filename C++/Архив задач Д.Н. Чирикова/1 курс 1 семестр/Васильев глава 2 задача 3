#include <iostream>
#include <cmath>
using namespace std;
const int N = 20;
int main()
{
    int k = 1;
    double x, q = 1, res = 1;
    cout << "Enter x: ";
    cin >> x;
    for (int i = 1; i < N; i++) {
        q *= x;
        res += (i + 1) * q;
    }
    cout << "result1: " << 1 / pow(1 - x, 2) << endl;
    cout << "result2: " << res << endl;
    return 0;
}
