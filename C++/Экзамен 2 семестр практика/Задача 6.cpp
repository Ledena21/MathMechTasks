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
                if ((-1)*(debtors[j].getBalance()) > ((debtors[j + 1].getBalance()))*(-1)) {
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
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла!" << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
    
            size_t first_space = line.find(' ');
            size_t last_space = line.rfind(' ');
    
            string phone = line.substr(0, first_space);
            string fio = line.substr(first_space + 1, last_space - first_space - 1);
            string balance_str = line.substr(last_space + 1);
    
            double balance = 0.0;
            
            balance = atof(balance_str.c_str());
    
            addSubscriber(PhoneSubscriber(phone, fio, balance));
        }
        file.close();
    }

    void separateSubscribers(vector<PhoneSubscriber>& debtors,
        vector<PhoneSubscriber>& nonDebtors) const {
        for (const auto& sub : subscribers) {
            if (sub.isDebtor()) {
                debtors.push_back(sub);
            }
            else {
                nonDebtors.push_back(sub);
            }
        }
    }

    void writeResultsToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error writing!" << endl;
            return;
        }

        vector<PhoneSubscriber> debtors, nonDebtors;
        separateSubscribers(debtors, nonDebtors);

        // Сортировка
        PhoneStation* nonConstThis = const_cast<PhoneStation*>(this);
        nonConstThis->bubbleSortDebtors(debtors);
        nonConstThis->bubbleSortNonDebtors(nonDebtors);

        if (debtors.empty()) {
            file << "Должников нет" << endl;
        }
        else {
            file << "Список должников (по убыванию суммы долга):" << endl;
            for (int i = debtors.size() - 1; i >= 0; i--) {
                file << "Телефон: " << debtors[i].getPhoneNumber()
                    << ", ФИО: " << debtors[i].getFullName()
                    << ", Долг: " << debtors[i].getBalance() << endl;
            }
        }

        file << "\nСписок остальных абонентов (по алфавиту ФИО):" << endl;
        for (const auto& sub : nonDebtors) {
            if (sub.getBalance() >= 0) {
                file << "Телефон: " << sub.getPhoneNumber()
                    << ", ФИО: " << sub.getFullName()
                    << ", Баланс: " << sub.getBalance() << endl;
            }
        }

        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    PhoneStation station;

    station.readFromFile("C:/MathMech/subscribers.txt");
    station.writeResultsToFile("result.txt");

    cout << "Обработка завершена. Результаты записаны в файл result.txt" << endl;

    return 0;
}
