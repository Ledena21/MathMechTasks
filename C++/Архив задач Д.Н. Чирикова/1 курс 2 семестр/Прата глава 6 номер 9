#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patron {
    string name;
    double donation;
};

int main() {
    ifstream inputFile("C:\\MathMech\\C++\\patrons.txt");
    if (!inputFile) {
        cout << "ERROR" << endl;
        return 1;
    }
    int numPatrons;
    inputFile >> numPatrons;
    Patron* patrons = new Patron[numPatrons];
    for (int i = 0; i < numPatrons; i++) {
        inputFile.ignore();
        getline(inputFile, patrons[i].name);
        inputFile >> patrons[i].donation;
    }
    cout << "Grand Patrons: " << endl;
    bool grandPatronsFound = false;
    for (int i = 0; i < numPatrons; i++) {
        if (patrons[i].donation >= 10000.0) {
            cout << patrons[i].name << ": $" << patrons[i].donation << endl;
            grandPatronsFound = true;
        }
    }
    if (!grandPatronsFound) {
        cout << "none" << endl;
    }
    cout << "Patrons: " << endl;
    bool patronsFound = false;
    for (int i = 0; i < numPatrons; i++) {
        if (patrons[i].donation < 10000.0) {
            cout << patrons[i].name << ": $" << patrons[i].donation << endl;
            patronsFound = true;
        }
    }
    if (!patronsFound) {
        cout << "none" << endl;
    }
    delete[] patrons;
    inputFile.close();
    return 0;
}
