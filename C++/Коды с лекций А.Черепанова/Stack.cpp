// Stack.h

#pragma once

#include "ArrayList.h"

class Stack
{
public:
	Stack();
	~Stack();

	void Push(int element);
	int Pop();
	int Peek();

private:
	ArrayList* pArray;
};


// Stack.cpp

#include "Stack.h"

Stack::Stack()
{
	pArray = new ArrayList();
}

Stack::~Stack()
{
	delete pArray;
}

void Stack::Push(int element)
{
	pArray->Add(element);
}

int Stack::Pop()
{
	int element = Peek();
	pArray->DeleteAt(pArray->Length() - 1);
	return element;
}

int Stack::Peek()
{
	return pArray->Get(pArray->Length() - 1);
}
