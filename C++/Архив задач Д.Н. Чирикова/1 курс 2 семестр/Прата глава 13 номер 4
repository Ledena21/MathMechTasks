//main.cpp

#include "port.h"
#include <iostream>
using namespace std;

int main() {
    Port p1("Gallo", "tawny", 20);
    Port p2 = p1;
    p1.Show();
    cout << p2 << endl;

    p1 += 5;
    cout << "After operation +5: " << p1 << endl;
    p1 -= 3;
    cout << "After operations -3: " << p1 << endl;

    VintagePort vp1("Gallo", 10, "The Noble", 1994);
    VintagePort vp2 = vp1;
    vp1.Show();
    cout << vp2 << endl;

    return 0;
}


//port.h

#pragma once
#ifndef PORT_H
#define PORT_H

#include <iostream>
using namespace std;

class Port {
private:
    char* brand;
    char style[20];
    int bottles;
public:
    Port(const char* br = "none", const char* st = "none", int b = 0);
    Port(const Port& p);
    virtual ~Port();
    Port& operator=(const Port& p);
    Port& operator+=(int b);
    Port& operator-=(int b);
    virtual void Show() const;
    friend ostream& operator<<(ostream& os, const Port& p);
};

class VintagePort : public Port {
private:
    char* nickname;
    int year;
public:
    VintagePort();
    VintagePort(const char* br, int b, const char* nn, int y);
    VintagePort(const VintagePort& vp);
    ~VintagePort();
    VintagePort& operator=(const VintagePort& vp);
    void Show() const;
    friend ostream& operator<<(ostream& os, const VintagePort& vp);
};

#endif


//port.cpp

#include "port.h"
#include <cstring>

Port::Port(const char* br, const char* st, int b) {
    brand = new char[strlen(br) + 1];
    strcpy_s(brand, strlen(br) + 1, br);
    strcpy_s(style, 19, st);
    bottles = b;
}

Port::Port(const Port& p) { 
    brand = new char[strlen(p.brand) + 1];
    strcpy_s(brand, strlen(p.brand) + 1, p.brand);
    strcpy_s(style, p.style);
    bottles = p.bottles;
}

Port::~Port() {
    delete[] brand;
}

Port& Port::operator=(const Port& p) {
    if (this != &p) {
        delete[] brand;
        brand = new char[strlen(p.brand) + 1];
        strcpy_s(brand, strlen(p.brand) + 1, p.brand);
        strcpy_s(style, p.style);
        bottles = p.bottles;
    }
    return *this;
}

Port& Port::operator+=(int b) {
    bottles += b;
    return *this;
}

Port& Port::operator-=(int b) {
    if (bottles >= b) {
        bottles -= b;
    }
    else {
        cout << "Error: uncorrect amount of bottles" << endl;
    }
    return *this;
}

void Port::Show() const {
    cout << "Brand: " << brand << endl;
    cout << "Kind: " << style << endl;
    cout << "Bottles: " << bottles << endl;
}

ostream& operator<<(ostream& os, const Port& p) {
    os << p.brand << ", " << p.style << ", " << p.bottles;
    return os;
}

VintagePort::VintagePort() : Port("none", "vintage", 0), year(0) {
    nickname = new char[1];
}

VintagePort::VintagePort(const char* br, int b, const char* nn, int y)
    : Port(br, "vintage", b), year(y) {
    nickname = new char[strlen(nn) + 1];
    strcpy_s(nickname, strlen(nn) + 1, nn);
}

VintagePort::~VintagePort(){
    delete[] nickname;
}

VintagePort::VintagePort(const VintagePort& vp) : Port(vp) {
    nickname = new char[strlen(vp.nickname) + 1];
    strcpy_s(nickname, strlen(vp.nickname) + 1, vp.nickname);
    year = vp.year;
}

VintagePort& VintagePort::operator=(const VintagePort& vp) {
    if (this != &vp) {
        Port::operator=(vp);
        delete[] nickname;
        nickname = new char[strlen(vp.nickname) + 1];
        strcpy_s(nickname, strlen(vp.nickname) + 1, vp.nickname);
        year = vp.year;
    }
    return *this;
}

void VintagePort::Show() const {
    Port::Show();
    cout << "Nickname: " << nickname << endl;
    cout << "Year: " << year << endl;
}

ostream& operator<<(ostream& os, const VintagePort& vp) { //оператор вывода
    os << (const Port&)vp << ", " << vp.nickname << ", " << vp.year;
    return os;
}
