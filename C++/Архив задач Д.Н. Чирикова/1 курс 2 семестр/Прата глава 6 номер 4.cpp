#include <iostream> 
using namespace std;

const int strsize = 100;

struct bop {
    char fullname[strsize];
    char title[strsize];
    char bopname[strsize];
    int preference;
};

int main() {
    const int lenght = 5;
    bop Inf[lenght] = { {"Wimp Macho", "Junior Programmer", "MIPS", 0},
        {"Raki Rhodes", "Analyst Trainee", "LOOPY", 1}, 
        {"Celia Laiter", "Senior Developer", "RAZOR", 2}, 
        {"Hoppy Hipman", "Project Manager", "PAT HAND", 1}, 
        {"Pat Hand", "Director", "BIG BOSS", 2} };
    char choice;
    do {
        cout << "Benevolent Order of Programmers Report" << endl;
        cout << "a. display by name" << endl;
        cout << "b. display by title" << endl;
        cout << "c. display by bopname" << endl;
        cout << "d. display by preference" << endl;
        cout << "q. quiet" << endl;
        cin >> choice;
        switch (choice) {
        case 'a':
            for (int i = 0; i < lenght; i++) {
                cout << Inf[i].fullname << endl;
            }
            break;
        case 'b':
            for (int i = 0; i < lenght; i++) {
                cout << Inf[i].title << endl;
            }
            break;
        case 'c':
            for (int i = 0; i < lenght; i++) {
                cout << Inf[i].bopname << endl;
            };
            break;
        case 'd':
            for (int i = 0; i < lenght; i++) {
                switch (Inf[i].preference) {
                case 0:
                    cout << Inf[i].fullname << endl;
                    break;
                case 1:
                    cout << Inf[i].title << endl;
                    break;
                case 2:
                    cout << Inf[i].bopname << endl;
                    break;
                }
            };
            break;
        case 'q':
            cout << "Bye!" << endl;
            break;
        }
    } while (choice != 'q');
    return 0;
}
