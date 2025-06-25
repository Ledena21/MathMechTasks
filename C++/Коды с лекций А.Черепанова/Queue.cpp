// Queue.h

#pragma once

#include "LinkedList.h"

class Queue
{
public:
	Queue();
	~Queue();

	void Enqueue(int element);
	int Dequeue();

private:
	LinkedList* pList;
};


// Queue.cpp

#include "Queue.h"

Queue::Queue()
{
	pList = new LinkedList();
}

Queue::~Queue()
{
	delete pList;
}

void Queue::Enqueue(int element)
{
	pList->Append(element);
}

int Queue::Dequeue()
{
	int element = pList->DeleteHead();
	return element;
}
