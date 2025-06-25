//main.cpp
#include "fractions.h"
#include <iostream>
using namespace std;

int main() {
    Rational a, b;
    char op;

    cout << "Fraction calculator (a/b operation c/d)" << endl;
    cout << "Available operations: + - * / (or 'q' to quit)" << endl;

    cout << "Enter the first fraction (format a or a/b): ";
    cin >> a;

    cout << "Enter the second fraction (format a or a/b): ";
    cin >> b;

    do {
        cout << "Choose operation (+, -, *, / or 'q' to quit): ";
        cin >> op;

        switch (op) {
        case '+':
            cout << "Sum: " << a << " + " << b << " = " << a + b << endl;
            break;
        case '-':
            cout << "Difference: " << a << " - " << b << " = " << a - b << endl;
            break;
        case '*':
            cout << "Product: " << a << " * " << b << " = " << a * b << endl;
            break;
        case '/':
            cout << "Quotient: " << a << " / " << b << " = " << a / b << endl;
            break;
        case 'q':
            break;
        default:
            cout << "Invalid operation! Please try again." << endl;
            break;
        }
    } while (op != 'q');

    return 0;
}


//fractions.h

#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <iostream>

class Rational {
private:
    int Num;
    int Den;
    int nod(int a, int b);
    void reduce();

public:
    Rational(int numerator = 0, int denominator = 1);
    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);
};

#endif // FRACTIONS_H#pragma once


//fractions.cpp

#include "fractions.h"
#include <iostream>

int Rational::nod(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Rational::reduce() {
    int mynod = nod(Num, Den);
    if (mynod != 0) {
        Num /= mynod;
        Den /= mynod;
    }
}

Rational::Rational(int numerator, int denominator) : Num(numerator), Den(denominator) {
    if (Den == 0) {
        std::cout << "Error: Denominator cannot be zero" << std::endl;
        Den = 1;
    }
    reduce();
}

Rational Rational::operator+(const Rational& other) const {
    return Rational(Num * other.Den + other.Num * Den, Den * other.Den);
}

Rational Rational::operator-(const Rational& other) const {
    return Rational(Num * other.Den - other.Num * Den, Den * other.Den);
}

Rational Rational::operator*(const Rational& other) const {
    return Rational(Num * other.Num, Den * other.Den);
}

Rational Rational::operator/(const Rational& other) const {
    if (other.Num == 0) {
        std::cout << "Error: Cannot divide by zero" << std::endl;
        return Rational(0, 1);
    }
    return Rational(Num * other.Den, Den * other.Num);
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.Den < 0) {
        os << r.Num*(-1);
        if (r.Den != 1) {
            os << '/' << r.Den*(-1);
        }
    }
    else {
        os << r.Num;
        if (r.Den != 1) {
            os << '/' << r.Den;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, Rational& r) {
    int num, den = 1;
    is >> num;
    if (is.peek() == '/') {
        is.ignore() >> den;
    }

    if (den == 0) {
        std::cout << "Error: Denominator cannot be zero" << std::endl;
        den = 1;
    }

    r = Rational(num, den);
    return is;
}
