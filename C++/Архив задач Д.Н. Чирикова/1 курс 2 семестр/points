//main.cpp

#include "points.h"
#include <iostream>
using namespace std;

int main() {
    Point* Points = nullptr; // создаем указатель на массив точек nullptr, чтобы не обратиться к неинициализированной памяти
    int pointCount = 0;
    double R = 0; 
    Point point; //создаем объект point класса Point, чтобы вызывать его методы

    point.read("points.txt", Points, pointCount, R); //читаем файл

    int filterCount = point.filter(Points, pointCount, R); //сортируем массив и получаем его длину
    Point* filterPoints = new Point[filterCount]; //создаем новый массив с отфильтрованными точками
    for (int i = 0; i < filterCount; i++) {
        filterPoints[i] = Points[i]; //туда копируем отфильтрованные точки
    }
    delete[] Points; //удаляем старый массив
    Points = nullptr; //присваиваем Points значение nullptr для безопасности, чтобы не использовать удаленный указатель

    int num1 = -1, num2 = -1;
    double maxDistance = 0;
    point.distantPoints(filterPoints, filterCount, num1, num2, maxDistance); //находим наиболее удаленные точки

    cout << "Points in R-neighborhood (R = " << R << "): " << filterCount << endl;
    for (int i = 0; i < filterCount; i++) {
        filterPoints[i].show();
    }
    if (filterCount >= 2) {
        cout << "Two furthest points: " << num1 << " and " << num2 << endl;
        cout << "Distance between them: " << maxDistance << endl;
    }
    else {
        cout << "Not enough points in R-neighborhood to find a pair." << endl;
    }
    delete[] filterPoints; //удаляем массив с отфильтрованными точками
    return 0;
}


//point.h

#ifndef POINTS_H
#define POINTS_H

#include <fstream>
#include <string>
#include <cmath>

class Point {
private:
    int number;
    double x, y, z;

public:
    Point();
    Point(int num, double xx, double yy, double zz);

    double distanceToOrigin() const;
    double distance(const Point& other) const;

    void read(const std::string& filename, Point*& points, int& count, double& R);
    void show() const;

    int filter(Point* arr, int lenarray, double R) const;
    void distantPoints(const Point* points, int size, int& index1, int& index2, double& maxDist) const;
};

#endif


//points.cpp

#include "points.h"
#include <iostream>
#include <fstream>

Point::Point() : number(0), x(0), y(0), z(0) {}//по умолчанию пусть все кооординаты и номер - нули

Point::Point(int num, double xx, double yy, double zz)
    : number(num), x(xx), y(yy), z(zz) {} //заполняем поля объекта данными

double Point::distanceToOrigin() const {
    return sqrt(x * x + y * y + z * z);//ищем расстояние до начала координат
}

double Point::distance(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return sqrt(dx * dx + dy * dy + dz * dz); //находим расстояние до другой точки
}

void Point::read(const std::string& filename, Point*& points, int& count, double& R) {
    std::ifstream file(filename); //открыли файл
    if (!file.is_open()) { //не открывается, значит ошибка
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string rline; //строчка с R
    std::getline(file, rline);  //читаем строку
    int equal = rline.find("="); //находим позицию равно
    R = stod(rline.substr(equal + 1)); //от равно и дальше берем число 

    count = 0;
    std::string line;
    std::getline(file, line); //глотаем заголовок
    while (std::getline(file, line)) { //идем по строкам файла
        if (!line.empty()) { //если в них что-то есть
            count++; //считаем их
        }
    }

    file.clear(); //чистим флаги, чтобы можно было снова открыть файл
    file.seekg(0); //переходим снова в начало файла
    std::getline(file, line); //пропускаем R
    std::getline(file, line); //пропускаем заголовок

    points = new Point[count]; //создаем массив длиной во столько точек, сколько насчитали
    int num;
    double x, y, z;
    for (int i = 0; i < count && file >> num >> x >> y >> z; i++) {
        points[i] = Point(num, x, y, z); //собираем массив из объектов Point
    }
    file.close(); //закрываем файл
}

void Point::show() const {
    std::cout << number << "\t" << x << "\t" << y << "\t" << z << std::endl; //просто вывод через таб
}

int Point::filter(Point* arr, int lenarray, double R) const {
    int filterCount = 0; //новый размер массива
    for (int i = 0; i < lenarray; i++) {
        if (arr[i].distanceToOrigin() <= R) { //если расстояние до начала координат меньше радиуса
            arr[filterCount] = arr[i]; //то точка подходит, копируем ее в начало массива
            filterCount++; //и считаем ее
        }
    }
    return filterCount; //возвращаем количество точек
}

void Point::distantPoints(const Point* points, int size, int& num1, int& num2, double& maxDist) const {
    for (int i = 0; i < size; i++) { //перебираем i-тые точки
        for (int j = i + 1; j < size; j++) { //перебираем j-тые точки
            double dist = points[i].distance(points[j]); //растояние между ними
            if (dist > maxDist) { //если оно больше максимума
                maxDist = dist; //обновляем его
                num1 = points[i].number; //запоминаем номера точек
                num2 = points[j].number;
            }
        }
    }
}
