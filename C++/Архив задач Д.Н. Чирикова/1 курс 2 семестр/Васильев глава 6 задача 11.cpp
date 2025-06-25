#include <iostream>
using namespace std;

struct Complex {
    double real;
    double imag;
};

Complex add(const Complex& a, const Complex& b) {
    Complex result = { a.real + b.real, a.imag + b.imag };
    return result;
}

Complex subtract(const Complex& a, const Complex& b) {
    Complex result = { a.real - b.real, a.imag - b.imag };
    return result;
}

Complex multiply(const Complex& a, const Complex& b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

Complex divide(const Complex& a, const Complex& b) {
    Complex result;
    double denominator = b.real * b.real + b.imag * b.imag;
    if (denominator == 0) {
        cout << "Error: Division by zero!" << endl;
        result.real = result.imag = 0;
        return result;
    }
    result.real = (a.real * b.real + a.imag * b.imag) / denominator;
    result.imag = (a.imag * b.real - a.real * b.imag) / denominator;
    return result;
}

void printComplex(const Complex& c) {
    cout << c.real;
    if (c.imag >= 0)
        cout << " + " << c.imag << "i";
    else
        cout << " - " << -c.imag << "i";
}

int main() {
    Complex num1, num2;
    cout << "Enter the real part of the 1st complex number: ";
    cin >> num1.real;
    cout << "Enter the imaginary part of the 1st complex number: ";
    cin >> num1.imag;

    cout << "Enter the real part of the 2nd complex number: ";
    cin >> num2.real;
    cout << "Enter the imaginary part of the 2nd complex number: ";
    cin >> num2.imag;

    char oper;
    do {
        cout << "Choose operation (+, -, /, * or 'q' to quit): ";
        cin >> oper;

        switch (oper) {
        case '+':
            cout << "Sum: ";
            printComplex(add(num1, num2));
            cout << endl;
            break;
        case '-':
            cout << "Difference: ";
            printComplex(subtract(num1, num2));
            cout << endl;
            break;
        case '*':
            cout << "Product: ";
            printComplex(multiply(num1, num2));
            cout << endl;
            break;
        case '/':
            cout << "Quotient: ";
            printComplex(divide(num1, num2));
            cout << endl;
            break;
        default:
            break;
        }
    } while (oper != 'q');
    return 0;
}
