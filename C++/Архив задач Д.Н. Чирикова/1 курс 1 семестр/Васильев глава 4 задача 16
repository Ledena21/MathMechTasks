#include <cmath>
using namespace std;
const double epsilon = 10e-6;

double getPolinom(double x, int N, double* a){
 double result = a[0], q = 1;
 for (int i = 1; i <= N; i++){
  q *= x;
  result += a[i] * q;
 }
 return result;
}

double dPolinom(double x, int N, double* a){
 double result = 0, q = 1;
 for (int i = 1; i <= N; i++){
  result += i * a[i] * q;
  q *= x;
 }
 return result;
}

void methodNewton(double x, int N, double* a){
 double polinom, d;
 do {
  polinom = getPolinom(x, N, a);
  d = dPolinom(x, N, a);
  x -= polinom / d;
 } while (abs(polinom) > epsilon);
 cout << "F(x) = " << polinom << endl;
 cout << "x = " << x << endl;
}

int main(){
 double x, *a, polinom, d;
 int N;
 cout << "Enter N: ";
 cin >> N;
 a = new double[N+1];
 cout << "Enter " << N+1 << " values: " << endl;
 for (int i = 0; i < N+1; i++){
  cout << ">>> ";
  cin >> a[i];
 }
 cout << "Enter x: ";
 cin >> x;
 methodNewton(x, N, a);
 delete[] a;
 return 0;
}
