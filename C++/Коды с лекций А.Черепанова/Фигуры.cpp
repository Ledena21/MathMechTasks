// Circle.h

#pragma once

#include <iostream>
#include "Figure.h"

class Circle : public Figure
{
public:
	void Draw()
	{
		std::cout << "I am Circle" << std::endl;
	}
//private:
	//double S;
};


// Figure.h

#pragma once

class Figure
{
public:
	virtual void Draw() {};
	int internalField;
	
	double S;

protected:
	void DoSome(){}
};


// RationalNumber.h

#pragma once

#include <iostream>
#include <string>

class RationalNumber
{
public:
	RationalNumber(int p, int q):
		P(p),
		Q(q)
	{
		//this->P = q;
	}

	~RationalNumber()
	{

	}

	/*
	void SetQ(int q)
	{
		if (q == 0)
			return;
		Q = q;
	}
	*/
	std::string ToString()
	{
		return  std::to_string(P) + "/" + std::to_string(Q);
	}
	
private:
	const int P;
	const int Q;
};

// Rectangle.h

#pragma once

#include <iostream>
#include "Figure.h"

class Rectangle : public Figure
{
public:
	Rectangle(int m, int n)
	{
		this->M = m;
		this->N = n;
		this->internalField = 0;
	}

	int GetM()
	{
		this->DoSome();
		return M;
	}

	int GetN()
	{
		return N;
	}

	void Draw()
	{
		std::cout << "I am Rectangle" << std::endl;
	}

private:
	double S;


	int M;
	int N;
};


// Square.h

#pragma once

#include "Rectangle.h"

class Square : public Rectangle
{
public:
	Square(int n):
		Rectangle(n, n)
	{
		pRect = new Rectangle(n, n);
	}

	int GetEdge()
	{
		return pRect->GetN();
	}

	void Draw()
	{
		std::cout << "I am Square" << std::endl;
	}
private:
	Rectangle* pRect;
};


//main.cpp

// Lection13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RationalNumber.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

using namespace std;

int main()
{
	RationalNumber number1(1, 3);
	cout << number1.ToString() << endl;

	RationalNumber number2(4, 7);
	cout << number2.ToString() << endl;

	Circle* circle = new Circle();
	
	Rectangle* rectangle = new Rectangle(1,2);
	Square* square = new Square(3);
	Figure* pFigure = square;

	//Figure* pFigure = new Figure();
	//int i = square->GetM();
	//int j = square->GetN();

	int n = 3;
	Figure** list = new Figure*[n];
	list[0] = rectangle;
	list[1] = square;
	list[2] = circle;
	
	for (int i = 0; i < n; ++i)
	{
		Figure* pFigure = list[i];
		Circle* pCircle = (Circle*)pFigure;

		pFigure->Draw();
	}		
}
