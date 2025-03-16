#include <iostream>
#include <cmath>
using namespace std;
const int N = 30;
int main() {
	double x, res, q;
	cout << "Enter x: ";
	cin >> x;
	res = q = x;
	for (int i = 1; i < N; i++) {
		q *= -x;
		res += q / (i + 1);
	}
	cout << "result = " << res << endl;
	cout << "true result = " << log(x+1) << endl;
	return 0;
}
