#define _USE_MATH_DEFINES
#include<iostream>
#include <cmath>

using namespace std;

int main() {
	const double i = 1;
	double R, x, y, r, z1, z2, phi, Xz1, Xz2, Yz1, Yz2;
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
	phi = atan2(y, x) / 2;
	r = sqrt(pow(x, 2) + pow(y, 2));
	R = sqrt(r);
	Xz1 = R * cos(phi);
	Yz1 = R * sin(phi);
	Xz2 = R * cos(phi + M_PI);
	Yz2 = R * sin(phi + M_PI);
	cout << "Real part z1: " << Xz1 << endl;
	cout << "Imaginary part z1: " << Yz1 << endl;
	cout << "Real part z2: " << Xz2 << endl;
	cout << "Imaginary part z2: " << Yz2 << endl;
	return 0;
}
