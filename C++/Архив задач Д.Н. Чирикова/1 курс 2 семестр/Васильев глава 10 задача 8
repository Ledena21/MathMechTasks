//main.cpp

#include "qexpression.h"
#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Enter max degree N: ";
    cin >> N;
    N++;

    QExpression q1(N), q2(N);

    cout << "For 1st expression:\n";
    cin >> q1;

    cout << "For 2nd expression:\n";
    cin >> q2;

    cout << "\nExpression 1: " << q1 << endl;
    cout << "Expression 2: " << q2 << endl;

    QExpression q3 = q1 + q2;
    cout << "Sum: " << q3 << endl;

    QExpression q4 = q1 - q2;
    cout << "Difference: " << q4 << endl;

    double mult_num;
    cout << "\nEnter number for multiplication: ";
    cin >> mult_num;
    QExpression q5 = q1 * mult_num;
    cout << "Multiplication by " << mult_num << ": " << q5 << endl;

    double div_num;
    cout << "Enter number for division: ";
    cin >> div_num;
    QExpression q6 = q2 / div_num;
    cout << "Division by " << div_num << ": " << q6 << endl;

    double x;
    cout << "\nEnter x to calculate Q1(x): ";
    cin >> x;
    cout << "Q1(" << x << ") = " << q1.calc(x) << endl;

    return 0;
}


//qexpression.h

#ifndef QEXPRESSION_H
#define QEXPRESSION_H

#include <iostream>

class QExpression {
private:
    double* coeffs;
    int n;

public:
    QExpression(int size);
    QExpression(const QExpression& other);
    ~QExpression();

    double calc(double x);

    QExpression operator+(const QExpression& other);
    QExpression operator-(const QExpression& other);
    QExpression operator*(double num);
    QExpression operator/(double num);

    friend std::ostream& operator<<(std::ostream& os, const QExpression& q);
    friend std::istream& operator>>(std::istream& is, QExpression& q);
};

#endif // QEXPRESSION_H


//qexpressions.cpp

#include "qexpression.h"
#include <iostream>

QExpression::QExpression(int size) : n(size) {
    coeffs = new double[n];
    for (int i = 0; i < n; i++) coeffs[i] = 0;
}

QExpression::QExpression(const QExpression& other) : n(other.n) {
    coeffs = new double[n];
    for (int i = 0; i < n; i++) {
        coeffs[i] = other.coeffs[i];
    }
}

QExpression::~QExpression() {
    delete[] coeffs;
}

double QExpression::calc(double x) {
    double res = 0;
    double x_pow = 1;

    for (int i = 0; i < n; i++) {
        res += coeffs[i] / x_pow;
        x_pow *= x;
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const QExpression& q) {
    os << "Q(x) = ";
    for (int i = 0; i < q.n; i++) {
        if (i == 0)
            os << q.coeffs[i];
        else
            os << " + " << q.coeffs[i] << "/x^" << i;
    }
    return os;
}

std::istream& operator>>(std::istream& is, QExpression& q) {
    std::cout << "Enter " << q.n << " coefficients (from a0 to a" << q.n - 1 << "): ";
    for (int i = 0; i < q.n; i++) {
        is >> q.coeffs[i];
    }
    return is;
}

QExpression QExpression::operator+(const QExpression& other) {
    int max_n = n > other.n ? n : other.n;
    QExpression res(max_n);

    for (int i = 0; i < max_n; i++) {
        double a = i < n ? coeffs[i] : 0;
        double b = i < other.n ? other.coeffs[i] : 0;
        res.coeffs[i] = a + b;
    }
    return res;
}

QExpression QExpression::operator-(const QExpression& other) {
    int max_n = n > other.n ? n : other.n;
    QExpression res(max_n);

    for (int i = 0; i < max_n; i++) {
        double a = i < n ? coeffs[i] : 0;
        double b = i < other.n ? other.coeffs[i] : 0;
        res.coeffs[i] = a - b;
    }
    return res;
}

QExpression QExpression::operator*(double num) {
    QExpression res(n);
    for (int i = 0; i < n; i++)
        res.coeffs[i] = coeffs[i] * num;
    return res;
}

QExpression QExpression::operator/(double num) {
    if (num == 0) {
        std::cout << "Error: Division by zero!" << std::endl;
        return *this;
    }
    QExpression res(n);
    for (int i = 0; i < n; i++)
        res.coeffs[i] = coeffs[i] / num;
    return res;
}
