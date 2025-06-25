//main.cpp

#include <iostream>
#include "golf.h"
using namespace std;

int main() {
    Golf player("player Birdfree", 24);
    player.show();
    Golf player2;

    cout << "\nEnter data for a new player\n";
    if (!player2.setGolf()) {
        cout << "Error: name not entered" << endl;
        return 1;
    }
    int ch;
    cout << "\nEnter handicap change:\n";
    cin >> ch;
    player2.setHandicap(ch);
    cout << "\nAfter handicap change:\n";
    player2.show();

    return 0;
}


// golf.cpp

#include <iostream>
#include <cstring>
#include "golf.h"
using namespace std;

Golf::Golf(const char* name, int hc) {
    strncpy_s(fullname, name, Len - 1);
    handicap = hc;
}

bool Golf::setGolf() {
    char tempName[Len];
    int tempHc;
    cout << "Enter player name: ";
    cin.getline(tempName, Len);
    if (tempName[0] == '\0'){
        cout << "Error: name not entered" << endl;
        return 0;
    }
    cout << "Enter player handicap: ";
    cin >> tempHc;
    cin.ignore();
    *this = Golf(tempName, tempHc);
    return 1;
}

void Golf::setHandicap(int hc) {
    handicap = hc;
}

void Golf::show() const {
    cout << "Name: " << fullname << ", Handicap: " << handicap << endl;
}


//golf.h

#pragma once
class Golf {
private:
    static const int Len = 40;
    char fullname[Len];
    int handicap;

public:
    Golf(const char* name = "", int hc = 0);
    bool setGolf();
    void setHandicap(int hc);
    void show() const;
};
