// LinkedList.h

#pragma once

struct Node
{
	int Data;

	Node* pNext;
	//Node* pPrev;

	/*
	~Node()
	{
		if (pNext != nullptr)
			delete pNext;
	}
	*/
};

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void Append(int element);
	void InsertAfter(int element, Node* node);
	void InsertBefore(int element, Node* node);
	void DeleteAfter(Node* node);
	int DeleteHead();

private:
	Node* pHead;
	Node* pTail;
};


// LinkedList.cpp

#include "LinkedList.h"

LinkedList::LinkedList()
{
	pHead = nullptr;
	pTail = nullptr;
}

LinkedList::~LinkedList()
{
	Node* pTemp = pHead;
	while (pTemp != nullptr)
	{
		Node* pDeleteNode = pTemp;
		pTemp = pTemp->pNext;
		delete pDeleteNode;
	}
}

void LinkedList::Append(int element) //O(1)
{
	Node* pNewNode = new Node();
	pNewNode->Data = element;
	pNewNode->pNext = nullptr;

	if (pTail == nullptr)
	{
		pHead = pNewNode;
		pTail = pNewNode;
		return;
	}

	pTail->pNext = pNewNode;
	pTail = pNewNode;
}

void LinkedList::InsertAfter(int element, Node* node) // O(1)
{
	if (node == nullptr)
		return;

	if (node == pTail)
	{
		Append(element);
		return;
	}

	Node* pNewNode = new Node();
	pNewNode->Data = element;
	pNewNode->pNext = nullptr;

	pNewNode->pNext = node->pNext;
	node->pNext = pNewNode;
}

void LinkedList::InsertBefore(int element, Node* node)
{
}

void LinkedList::DeleteAfter(Node* node)
{
	if (node == nullptr)
		return;

	Node* pDeleteNode = node->pNext;
	node->pNext = node->pNext->pNext;

	if (pDeleteNode == pTail)
		pTail = node;

	delete pDeleteNode;
}

int LinkedList::DeleteHead()
{
	if (pHead == nullptr)
		return 0;

	int element = pHead->Data;
	Node* pDeleteNode = pHead;
	pHead = pHead->pNext;
	delete pDeleteNode;
	return element;
}

