#include <iostream>
#include <string>
using namespace std;

struct AllPatrons {
    string name;
    double donation;
};

int main() {
    int numPatrons;
    cout << "Enter the amount of patrons: ";
    cin >> numPatrons;
    AllPatrons* patrons = new AllPatrons[numPatrons];
    for (int i = 0; i < numPatrons; i++) {
        cin.get();
        cout << "Enter name " << i + 1 << ": ";
        getline(cin, patrons[i].name);
        cout << "Enter donation: ";
        cin >> patrons[i].donation;
    }
    cout << "GRAND PATRONS: " << endl;
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
    cout << "PATRONS: " << endl;
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
    return 0;
}
