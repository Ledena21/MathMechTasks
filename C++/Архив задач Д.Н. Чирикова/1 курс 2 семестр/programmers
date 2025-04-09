#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Programmer {
    string name;
    string date;
    int y, m, d;
};

void parseDate(Programmer& p) {
    string months[12] = { "January","February","March","April","May","June",
                      "July","August","September","October","November","December" };
    int space = p.date.find(' '); //нашли первый пробел
    string month = p.date.substr(0, space); //взяли название месяца (с начала до пробела)

    p.m = 1;
    for (int i = 0; i < 12; i++) {
        if (months[i] == month) {
            p.m = i + 1;
            break;
        }
    }

    int comma = p.date.find(','); //нашли запятую
    p.d = stoi(p.date.substr(space + 1, comma - space - 1)); //берем день
    p.y = stoi(p.date.substr(comma + 2)); //две позиции после запятой, берем год
}

void sortProgrammers(Programmer list[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j].y > list[j + 1].y) {
                swap(list[j], list[j + 1]);
            }
            else if (list[j].y == list[j + 1].y && list[j].m > list[j + 1].m) {
                swap(list[j], list[j + 1]);
            }
            else if (list[j].y == list[j + 1].y && list[j].m == list[j + 1].m && list[j].d > list[j + 1].d) {
                swap(list[j], list[j + 1]);
            }
        }
    }
}

int main() {
    ifstream in("programmers.txt");
    if (!in) {
        cout << "Error of opening file!" << endl;
        return 1;
    }

    int count = 0;
    string line;
    while (getline(in, line)) {
        if (line.find('\t') != string::npos) {
            count++;
        }
    }
    in.clear();
    in.seekg(0);

    Programmer* list = new Programmer[count];

    int index = 0;
    while (getline(in, line)) {
        int tab = line.find('\t');
        if (tab == string::npos) {
            continue;
        }
        list[index].name = line.substr(0, tab); // взяли имя
        list[index].date = line.substr(tab + 1); // взяли дату
        parseDate(list[index]);
        index++;
    }
    in.close();

    sortProgrammers(list, count);

    ofstream out("sorted_programmers.txt");
    if (!out) {
        cout << "Error!" << endl;
        delete[] list;
        return 1;
    }
    for (int i = 0; i < count; i++) {
        out << list[i].name << "\t" << list[i].date << endl;
    }
    out.close();

    delete[] list;

    cout << "File sorted!" << endl;
    return 0;
}
