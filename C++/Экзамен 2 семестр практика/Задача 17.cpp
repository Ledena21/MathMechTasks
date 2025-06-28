/*В файле записана информация о вкладчике банка: ФИО, номер вклада, сумма вклада. Сформировать и
вывести в результирующий файл список вкладчиков, чей номер вклада начинается на заданную цифру, 
отсортировав его по убыванию сумм вкладов. Если нужных вкладчиков нет, выдать соответствующее сообщение. 
Написать соответствующий класс и методы.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class BankDepositor {
private:
    string fullName; // ФИО вкладчика
    string depositNumber; // номер вклада
    double depositAmount; // сумма вклада

public:
    // конструктор, который инициализирует объект переданными параметрами
    BankDepositor(string name, string number, double amount)  
        : fullName(name), depositNumber(number), depositAmount(amount) {}

    // геттеры для доступа к полям класса
    string getFullName() const { return fullName; }
    string getDepositNumber() const { return depositNumber; }
    double getDepositAmount() const { return depositAmount; }

    void printInfo() const { // функция печати
        cout << "Name: " << fullName
            << ", Deposit Number: " << depositNumber
            << ", Amount: " << depositAmount << endl;
    }
};

class Bank {
private:
    vector<BankDepositor> depositors; // список всех вкладчиков
    
    // пузырьковая сортировка вкладчиков по убыванию суммы вклада
    void sortByAmountDescending(vector<BankDepositor>& depositorsList) {
        int n = depositorsList.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (depositorsList[j].getDepositAmount() < depositorsList[j + 1].getDepositAmount()) {
                    swap(depositorsList[j], depositorsList[j + 1]);
                }
            }
        }
    }

public:
    void addDepositor(const BankDepositor& depositor) { // добавляем вкладчика
        depositors.push_back(depositor);
    }

    void readFromFile(const string& filename) {
        ifstream file(filename); // открываем файл
        if (!file.is_open()) { // не открыли, выводим ошибку
            cerr << "Error opening file!" << endl;
            return;
        }
        string line; // сюда будем считывать строки из файла
        while (getline(file, line)) { // пока есть строка
            if (line.empty()) continue; // пустую пропускаем

            size_t first_space = line.find(' '); // найдем первый пробел
            size_t last_space = line.rfind(' '); // найдем последний пробел

            string name = line.substr(0, first_space); // извлечем имя
            string number = line.substr(first_space + 1, last_space - first_space - 1); // извлечем номер вклада
            string amount_str = line.substr(last_space + 1); // извлечем сумму вклада

            double amount = stod(amount_str); // переводим сумму вклада в число
            addDepositor(BankDepositor(name, number, amount)); // сконструируем и добавим нового вкладчика
        }
        file.close();
    }

    vector<BankDepositor> getDepositorsByFirstDigit(char digit) { // передаем нужную цифру
        vector<BankDepositor> result; // результирующий массив
        for (int i = 0; i < depositors.size(); i++) {
            if (!depositors[i].getDepositNumber().empty() &&
                depositors[i].getDepositNumber()[0] == digit) { // находим тех, у которых номер на переданную цифру
                result.push_back(depositors[i]); // складываем в массив result
            }
        }
        return result;
    }

    void writeResultsToFile(const string& filename, char searchDigit) {
        ofstream file(filename); // создаем/перезаписываем файл с указанным именем
        if (!file.is_open()) { // если не получилось, выводим ошибку
            cerr << "Error writing to file!" << endl;
            return;
        }
        
        // создаем фильтрованный массив и сортируем его
        vector<BankDepositor> filteredDepositors = getDepositorsByFirstDigit(searchDigit);
        sortByAmountDescending(filteredDepositors);

        if (filteredDepositors.empty()) { // если фильтрованный массив пустой
            file << "No depositors with deposit number starting with '" << searchDigit << "'" << endl;
        }
        else {
            file << "List of depositors with deposit number starting with '" << searchDigit << "':" << endl;
            for (int i = 0; i < filteredDepositors.size(); i++) { // пишем в файл
                file << "Name: " << filteredDepositors[i].getFullName()
                    << ", Deposit Number: " << filteredDepositors[i].getDepositNumber()
                    << ", Amount: " << filteredDepositors[i].getDepositAmount() << endl;
            }
        }
        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Bank bank;

    bank.readFromFile("depositors.txt");
    char searchDigit;
    cout << "Enter the first digit of deposit number to search: ";
    cin >> searchDigit;
    bank.writeResultsToFile("result.txt", searchDigit);
    cout << "Processing completed. Results written to file result.txt" << endl;
    return 0;
}
