/*В файле записана информация об абонентах телефонной станции. Абонент на телефонной станции представлен номером телефона,
ФИО абонента и некоторой суммой денег (если сумма <0, то это должник). Создать два списка абонентов телефонной станции:
должников упорядочить по убыванию суммы долга, остальных - по алфавиту ФИО. Оба списка записать в результирующий файл.
Выдать соответствующее сообщение, если должников нет. Написать соответствующий класс и методы.*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class PhoneSubscriber {
private:
    string phoneNumber; // номер телефона
    string fullName; // ФИО
    double balance; // баланс

public:
    PhoneSubscriber(string phone, string name, double bal) // конструктор, инициализирует поля принятыми значениями
        : phoneNumber(phone), fullName(name), balance(bal) {}

    // функции-геттеры, которые позволяют нам узнать информацию о пользователях
    string getPhoneNumber() const { return phoneNumber; }
    string getFullName() const { return fullName; }
    double getBalance() const { return balance; }

    bool isDebtor() const { return balance < 0; } // проверка на должника, если баланс <0 => должник

    void printInfo() const { // функция печатает информацию об абоненте
        cout << "Telephon: " << phoneNumber
            << ", Name: " << fullName
            << ", Balance: " << balance << endl;
    }
};

class PhoneStation {
private:
    vector<PhoneSubscriber> subscribers; // массив для хранения всех абонентов

    void bubbleSortDebtors(vector<PhoneSubscriber>& debtors) {
        int n = debtors.size(); // смотрим размер массива, т.е. количество должников
        // пузырьковая сортировка
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if ((debtors[j].getBalance()) > ((debtors[j + 1].getBalance()))) {
                    swap(debtors[j], debtors[j + 1]);
                }
            }
        }
    }

    void bubbleSortNonDebtors(vector<PhoneSubscriber>& nonDebtors) {
        int n = nonDebtors.size(); // смотрим размер массива, т.е. количество не-должников
        // пузырьковая сортировка
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (nonDebtors[j].getFullName() > nonDebtors[j + 1].getFullName()) {
                    swap(nonDebtors[j], nonDebtors[j + 1]);
                }
            }
        }
    }

public:
    void addSubscriber(const PhoneSubscriber& sub) {
        subscribers.push_back(sub); // добавляем абонента
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) { // если файл не открылся
            cerr << "Error of opening file!" << endl;
            return;
        }

        string line; // сюда будем считывать строки из файла
        while (getline(file, line)) { // пока есть строка
            if (line.empty()) continue; // пустую пропускаем

            size_t first_space = line.find(' '); // найдем первый пробел
            size_t last_space = line.rfind(' '); // найдем последний пробел

            string phone = line.substr(0, first_space); // берем номер телефона
            string fio = line.substr(first_space + 1, last_space - first_space - 1); // берем ФИО
            string balance_str = line.substr(last_space + 1); // берем баланс

            double balance = 0.0; // сюда мы положим числовое значение баланса, потому что считали мы строку
            balance = atof(balance_str.c_str()); // преобразуем си строку в число

            addSubscriber(PhoneSubscriber(phone, fio, balance)); // создаем абонента, суем в массив
        }
        file.close();
    }

    void separateSubscribers(vector<PhoneSubscriber>& debtors,
        vector<PhoneSubscriber>& nonDebtors) const { // массивы для должников и для не-должников
        for (size_t i = 0; i < subscribers.size(); i++) {
            if (subscribers[i].isDebtor()) {
                debtors.push_back(subscribers[i]);
            }
            else {
                nonDebtors.push_back(subscribers[i]);
            }
        }
    }

    void writeResultsToFile(const string& filename) {
        ofstream file(filename); // создаем/перезаписываем файл с указанным именем
        if (!file.is_open()) { // если не получилось, выводим ошибку
            cerr << "Error writing!" << endl;
            return;
        }

        vector<PhoneSubscriber> debtors, nonDebtors; // создаем два массива
        separateSubscribers(debtors, nonDebtors); // заполняем их

        bubbleSortDebtors(debtors); // сортируем должников
        bubbleSortNonDebtors(nonDebtors); // сортируем не-должников

        if (debtors.empty()) { // если должников нет, так и пишем
            file << "No debtors" << endl;
        }
        else {
            file << "List of debtors:" << endl; // выводим должников
            for (int i = 0; i < debtors.size(); i++){
                file << "Telephone: " << debtors[i].getPhoneNumber()
                    << ", FullName: " << debtors[i].getFullName()
                    << ", Debt: " << debtors[i].getBalance() << endl;
            }
        }

        file << "\nList of other subscribers:" << endl;  // выводим не-должников
        for (size_t i = 0; i < nonDebtors.size(); ++i) {
            if (nonDebtors[i].getBalance() >= 0) {
                file << "Telephone: " << nonDebtors[i].getPhoneNumber()
                    << ", FullName: " << nonDebtors[i].getFullName()
                    << ", Balance: " << nonDebtors[i].getBalance() << endl;
            }
        }

        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    PhoneStation station;

    station.readFromFile("subscribers.txt"); // читаем из файла, указываем путь к файлу
    station.writeResultsToFile("result.txt"); // записываем файл, указываем имя файла

    cout << "Processing completed. Results written to file result.txt" << endl;

    return 0;
}
