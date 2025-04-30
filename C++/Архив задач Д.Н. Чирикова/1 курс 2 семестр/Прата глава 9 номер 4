//main

#include <iostream>
#include "sales.h"

using namespace std;
using namespace SALES;

int main() {
    Sales year2023;
    Sales year2024;

    const double ar[] = {2, 5, 10};
    setSales(year2023, ar, size(ar));

    setSales(year2024);

    cout << endl << "Year 2023 sales:" << endl;
    showSales(year2023);

    cout << endl << "Year 2024 sales:" << endl;
    showSales(year2024);

    return 0;
}

//sales.h

#ifndef SALES_H
#define SALES_H

namespace SALES {
    const int QUARTERS = 4;

    struct Sales {
        double sales[QUARTERS];
        double average;
        double max;
        double min;
    };

    void setSales(Sales& s, const double ar[], int n);
    void setSales(Sales& s);
    void showSales(const Sales& s);
}

#endif

//sales.cpp

#include <iostream>
#include "sales.h"

using namespace std;

namespace SALES {
    void setSales(Sales& s, const double ar[], int n) {
        int m;
        if (QUARTERS < n) {
            m = QUARTERS;
        }
        else {
            m = n;
        }

        double maxElem = ar[0], minElem = ar[0], sumElems = 0;

        for (int i = 0; i < m; i++) {
            s.sales[i] = ar[i];
            if (maxElem < ar[i]) {
                maxElem = ar[i];
            }
            if (minElem > ar[i]) {
                minElem = ar[i];
            }
            sumElems += ar[i];
        }

        for (int i = m; i < QUARTERS; i++) {
            s.sales[i] = 0;
        }

        s.max = maxElem;
        s.min = minElem;
        s.average = sumElems / m;
    }

    void setSales(Sales& s) {
        double maxElem, minElem, sumElems = 0;

        for (int i = 0; i < QUARTERS; i++) {
            cout << "Enter sales for " << i + 1 << " quarter: ";
            cin >> s.sales[i];

            if (i == 0) {
                maxElem = minElem = s.sales[i];
            }
            else {
                if (maxElem < s.sales[i]) {
                    maxElem = s.sales[i];
                }
                if (minElem > s.sales[i]) {
                    minElem = s.sales[i];
                }
            }

            sumElems += s.sales[i];
        }

        s.max = maxElem;
        s.min = minElem;
        s.average = sumElems / QUARTERS;
    }

    void showSales(const Sales& s) {
        cout << "Sales for quarters: ";
        for (int i = 0; i < QUARTERS; i++) {
            cout << s.sales[i] << " ";
        }
        cout << endl;
        cout << "Max: " << s.max << endl;
        cout << "Min: " << s.min << endl;
        cout << "Average: " << s.average << endl;
    }
}
