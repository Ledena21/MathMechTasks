#include <iostream>
using namespace std;
int main() {
	char c;
	int flag = 0;
	while ((c = cin.get()) != '.') {
		if (flag == 0) {
			if (c == '/')
				flag = 1;
			else
				cout.put(c);
		}
		else if (flag == 1) {
			if (c == '*') {
				flag = 2;
			}
			else if (c == '/') {
				flag = 4;
			}
			else {
				cout.put('/');
				cout.put(c);
				flag = 0;
			}
		}
		else if (flag == 2) {
			if (c == '*') {
				flag = 3;
			}
		}
		else if (flag == 3) {
			if (c == '/') {
				flag = 0;
			}
			else {
				flag = 2;
			}
		}
		else if (flag == 4) {
			if (c == '\n') {
				flag = 0;
				cout.put('\n');
			}
		}
	}
	return 0;
}
