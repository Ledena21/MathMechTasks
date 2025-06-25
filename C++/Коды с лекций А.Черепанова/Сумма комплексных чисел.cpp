//complex.h

#pragma once
#include <string>

namespace Calculator {
	namespace Number // вложенное пространство имён для типов чисел
	{
	  struct Int // пустая структура для целых чисел
		{};
		struct Double
		{};
		struct Short
		{};
		struct Float
		{};
	}

	struct Complex // структура для комплексных чисел
  { 
	public:
		Complex(int re, int im); // конструктор (реальная + мнимая части)
		~Complex(); // деструктор

		std::string Get() const; // метод для строкового представления числа


	private:
		int Re; // действительная часть
		int Im; // мнимая часть
	};

}


//complex.cpp

#include "complex.h"

using namespace std;

namespace Calculator
{
	Complex::Complex(int re, int im) {} // конструктор, который почему-то не инициализирует поля
// рабочий конструктор Complex::Complex(int re, int im) : Re(re), Im(im) {}

	Complex::~Complex() // деструктор пустой, так как динамическую память не выделяли
	{

	}

	std::string Complex::Get() const
	{
		std::string s = std::to_string(Re) + "+i" + to_string(Im); //преобразуем re и im в строки и добавляем +i к мнимой части
		return s;
	}
}


//sum.h

#pragma once
int Sum(int x, int y); // объявление функции суммы


//sum.cpp

int Sum(int x, int y) //функция складывает x и y
{
	return x + y;
}


//main.cpp

#include <iostream>

#include "sum.h"
#include "complex.h"

using namespace std;
using namespace Calculator;

int main()
{
	Calculator::Complex complex(1,3); // создаем комплексное число 1 + 3i
	{
		using Calculator::Complex; //используем пространство имен Calculator
		Complex complex1(1, 2);
		Complex complex2(3, 4);
    // complex1 и complex2 существуют только внутри этого блока { }.
    // после выхода из блока они автоматически уничтожаются (вызываются их деструкторы).
	}
	Complex complex3(3, 4); создаем комплексное число 3 + 4i


	int k = Sum(1, 2); // суммируем
	cout << k << endl; // выводим результат
}
