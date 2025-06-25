#define _USE_MATH_DEFINES_
#include <iostream>
#include <cmath>
using namespace std;
int main() {
	double x, s;
	char op;
	cout << "Enter number: ";
	cin >> x;
	s = x;
	while (true) {
		cout << "Enter operation: ";
		cin >> op;
		if (op == '=') {
			cout << "---> " << s << endl;
			exit(0);
		}
		cout << "Enter number: ";
		cin >> x;
		switch (op) {
		case '+':
			s += x;
			break;
		case '-':
			s -= x;
			break;
		case '*':
			s *= x;
			break;
		case '/':
			s /= x;
			break;
		case '^':
			s = pow(s, x);
			break; //последний ставить необязательно
		}
	}
	return 0;
}
