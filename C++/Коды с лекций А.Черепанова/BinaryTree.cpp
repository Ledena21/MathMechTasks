// BinaryTree.h

#pragma once

#include <iostream>

struct TreeNode
{
	int Key;
	int Value;
	TreeNode* pParent;
	TreeNode* pLeft;
	TreeNode* pRight;
};

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	int Search(int key);
	void Add(int key, int value);
	bool Delete(int key);
private:
	TreeNode* pRoot;
};


// BinaryTree.cpp

#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
}

int BinaryTree::Search(int key)
{
	TreeNode* pCurrentNode = pRoot;
	while (pCurrentNode != nullptr)
	{
		if (pCurrentNode->Key == key)
			return pCurrentNode->Value;

		if (key < pCurrentNode->Key)
			pCurrentNode = pCurrentNode->pLeft;
		else
			pCurrentNode = pCurrentNode->pRight;
	}
	return -1;
}

void BinaryTree::Add(int key, int value)
{
	TreeNode* pCurrentNode = pRoot;
	TreeNode* pParent = nullptr;
	while (pCurrentNode != nullptr)
	{
		if (pCurrentNode->Key == key)
		{
			pCurrentNode->Value = value;
			return;
		}
		pParent = pCurrentNode;
		if (key < pCurrentNode->Key)
			pCurrentNode = pCurrentNode->pLeft;
		else
			pCurrentNode = pCurrentNode->pRight;
	}

	TreeNode* pNewNode = new TreeNode();
	pNewNode->Key = key;
	pNewNode->Value = value;
	pNewNode->pParent = pParent;
	pNewNode->pLeft = nullptr;
	pNewNode->pRight = nullptr;

	if (pParent == nullptr) //----?????
	{
		pRoot = pNewNode;
		return;
	}

	if (pNewNode->Key < pParent->Key)
		pParent->pLeft = pNewNode;
	else
		pParent->pRight = pNewNode;
}

bool BinaryTree::Delete(int key)
{
	if (pRoot == nullptr)
		return false;

	TreeNode* pCurrentNode = pRoot;
	while (pCurrentNode != nullptr)
	{
		if (pCurrentNode->Key == key)
			break;
		
		if (key < pCurrentNode->Key)
			pCurrentNode = pCurrentNode->pLeft;
		else
			pCurrentNode = pCurrentNode->pRight;
	}

	if (pCurrentNode == nullptr)
		return false;

	if (pCurrentNode == pRoot)
	{
		//--------------------???????????????

		return true;
	}

	if (pCurrentNode->pLeft != nullptr)
	{
		//берем максимальный элемент левого поддерева
		//меняем занечения и удаляем
		auto pMax = pCurrentNode->pLeft;
		while (pMax->pRight != nullptr)
			pMax = pMax->pRight;

		pCurrentNode->Key = pMax->Key;
		pCurrentNode->Value = pMax->Value;

		pMax->pParent->pRight = pMax->pLeft;
		if (pMax->pLeft != nullptr)
			pMax->pLeft->pParent = pMax->pParent;

		delete pMax;
		return true;
	}

	if (pCurrentNode->pRight != nullptr)
	{
		//берем pRight и заменяем
		if (pCurrentNode->pParent != nullptr)
			pCurrentNode->pParent->pRight = pCurrentNode->pRight;
		else
			pRoot = pCurrentNode->pRight;
		pCurrentNode->pRight->pParent = pCurrentNode->pParent;
		delete pCurrentNode;
		return true;
	}
	//просто удаляем
	delete pCurrentNode;
	return true;
}
