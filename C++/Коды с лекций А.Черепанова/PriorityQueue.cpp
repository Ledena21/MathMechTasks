//PriorityQueue.cpp

#pragma once

#include "ArrayList.h"
/*

1 2 3 4 5 6 7

*/
class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();

	void Enqueue(int element, int priority);
	int Dequeue();

private:
	ArrayList* pArray;
};


// PriorityQueue.cpp

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
	pArray = new ArrayList();
}

PriorityQueue::~PriorityQueue()
{
	delete pArray;
}

void PriorityQueue::Enqueue(int element, int priority)
{
	pArray->InsertAt(element, priority);
}

int PriorityQueue::Dequeue()
{
	int element = pArray->Get(0);
	pArray->DeleteAt(0);
	return element;
}
