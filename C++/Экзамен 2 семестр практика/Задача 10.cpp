/*В файле записаны сведения о владельце автомобиля: фамилия, марка автомобиля (строки), номер автомобиля (целое число). 
Получить и вывести в результирующий файл список владельцев автомобилей указанной марки, отсортированные по возрастанию 
номеров автомобилей. Выдать соответствующее сообщение, если автомобилей данной марки нет. 
Написать соответствующий класс и методы.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class CarOwner {
private:
    string lastName; // фамилия владельца
    string carBrand; // марка автомобиля
    int carNumber; // номер автомобиля

public:
    CarOwner(string name, string brand, int number) // конструктор, который инициализирует объект переданными параметрами
        : lastName(name), carBrand(brand), carNumber(number) {}

    // геттеры для доступа к данным
    string getLastName() const { return lastName; }
    string getCarBrand() const { return carBrand; }
    int getCarNumber() const { return carNumber; }

    void printInfo() const { // функция вывода
        cout << "Owner: " << lastName
            << ", Car: " << carBrand
            << ", Number: " << carNumber << endl;
    }
};

class CarRegistry {
private:
    vector<CarOwner> owners;  // массив всех владельцев

    // пузырьковая сортировка по номеру автомобиля
    void sortByNumber(vector<CarOwner>& ownersToSort) {
        int n = ownersToSort.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (ownersToSort[j].getCarNumber() > ownersToSort[j + 1].getCarNumber()) {
                    swap(ownersToSort[j], ownersToSort[j + 1]);
                }
            }
        }
    }

public:
    void addOwner(const CarOwner& owner) { // добавить владельца
        owners.push_back(owner);
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line; // сюда будем считывать строки из файла
        while (getline(file, line)) { // пока есть строка
            if (line.empty()) continue; // пустую пропускаем

            size_t first_space = line.find(' '); // найдем первый пробел
            size_t second_space = line.rfind(' '); // найдем последний пробел

            string name = line.substr(0, first_space); // извлекаем имя
            string carBrand = line.substr(first_space + 1, second_space - first_space - 1); // извлекаем марку
            int carNumber = stoi(line.substr(second_space + 1)); // извлекаем номер машины и преобразуем си строку в число

            addOwner(CarOwner(name, carBrand, carNumber)); // конструируем и добавляем нового владельца
        }
        file.close();
    }

    void findOwnersByBrand(const string& brand, vector<CarOwner>& result) {
        for (size_t i = 0; i < owners.size(); ++i) { // идем по массиву
            if (owners[i].getCarBrand() == brand) { // нашли нужную марку
                result.push_back(owners[i]);
            }
        }
    }

    void writeResultsToFile(const string& filename, const string& targetBrand) {
        ofstream file(filename); // создаем/перезаписываем файл с указанным именем
        if (!file.is_open()) { // если не получилось, выводим ошибку
            cerr << "Error writing to file!" << endl;
            return;
        }

        vector<CarOwner> foundOwners; // создаем массив для нужной нам марки
        findOwnersByBrand(targetBrand, foundOwners); // заполняем его

        if (foundOwners.empty()) { // если не нашли ни одного владельца нужной марки, сообщаем
            file << "No owners found for brand: " << targetBrand << endl;
        }
        else {
            sortByNumber(foundOwners); // сортируем по номеру и пишем в файл
            file << "Owners of " << targetBrand << " cars (sorted by number):" << endl;
            for (size_t i = 0; i < foundOwners.size(); ++i) {
                file << "Owner: " << foundOwners[i].getLastName()
                    << ", Number: " << foundOwners[i].getCarNumber() << endl;
            }
        }

        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    CarRegistry registry;
    string targetBrand;

    registry.readFromFile("car_owners.txt");

    cout << "Enter car brand to search: "; // ввод нужной марки
    cin >> targetBrand;

    registry.writeResultsToFile("result.txt", targetBrand);

    cout << "Processing completed. Results written to file result.txt" << endl;

    return 0;
}
