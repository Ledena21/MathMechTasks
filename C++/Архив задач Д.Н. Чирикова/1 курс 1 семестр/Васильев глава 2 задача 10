#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;
int main() {
	double res, q;
	int N;
	cout << "Enter N: ";
	cin >> N;
	q = M_PI / 2;
	res = 1;
	for (int i = 1; i < N + 1; i++) {
		q /= 2;
		res *= cos(q);
	}
	cout << "result = " << res << endl;
	cout << "true result = " << 2 / M_PI << endl;
}
