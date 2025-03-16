#include <iostream>
#include <cmath>

using namespace std;

int main() {
  double x, y, z, V, n=0.0, V0 = 88.0/105.0;
  int N;
	cout << "Enter N: ";
	cin >> N;

  for (double i = 0; i <= N; i++) {
    x = 2*i/N - 1;
    for (double j = 0; j <= N; j++) {
      y = 2*j/N - 1;
      for (double k = 0; k <=  N; k++) {
        z = 2*k/N;
        if (z <= x * x + y * y && y >= x * x && y <= 1 && z >= 0)
          n++;
      }
    }
  }
  V = 8 * n / pow(N+1, 3);
  cout << V << endl;
  cout << V0 << endl;
  return 0;
}
