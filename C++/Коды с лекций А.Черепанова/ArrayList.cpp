// ArrayList.h

#pragma once

class ArrayList
{
public:
	ArrayList();
	~ArrayList();
	 
	int Length();
	void Add(int element);
	bool InsertAt(int element, int index);
	bool DeleteAt(int index);

	int Get(int index);
	bool TryGet(int index, int& outValue);

	//int& operator[](int index);
	int operator[](int index);

private:
	void Resize();
	void Copy(int* pTemp);

	int* pData;
	int capacity;
	int size;

	/*
	* int left;
	* int right;
	*/

	int growFactor;
};


// ArrayList.cpp

#include <iostream>
#include "ArrayList.h"

using namespace std;

ArrayList::ArrayList()
{
	size = 0;
	capacity = 4;
	growFactor = 2;
	pData = new int[capacity];
}

ArrayList::~ArrayList()
{
	delete[] pData;
}

int ArrayList::Length()
{
	return size;
}

void ArrayList::Add(int element) // O(1 + a)
{
	if (size > capacity) //???
		Resize();

	pData[size++] = element;
}

bool ArrayList::InsertAt(int element, int index)//O(n)
{
	if (index < 0 || index > size - 1)
		return false;

	if (size > capacity) //???
		Resize();

	for (int i = size; i > index; --i)
		pData[i] = pData[i - 1];

	pData[index] = element;
	++size;
	return true;
}

bool ArrayList::DeleteAt(int index)
{
	if (index < 0 || index > size - 1)
		return false;

	for (int i = index; i < size; ++i)
		pData[i] = pData[i + 1];
	
	return true;
}

int ArrayList::Get(int index)
{
	if (index < 0 || index > size)
	{
		cout << "error" << endl;
		return 0;
	}

	return pData[index];
}

bool ArrayList::TryGet(int index, int& outValue)
{
	if (index < 0 || index > size)
	{
		cout << "error" << endl;
		return false;
	}
	outValue = pData[index];
	return true;
}

int ArrayList::operator[](int index)
{
	return Get(index);
}

void ArrayList::Resize()
{
	capacity = capacity * growFactor;
	int* pTemp = new int[capacity];
	Copy(pTemp);
	delete[] pData;
	pData = pTemp;
}

void ArrayList::Copy(int* pTemp)
{
	//for (int i = 0; i < size; ++i)
		//pTemp[i] = pData[i];

	int sizeInBytes = size * sizeof(pData[0]);
	memcpy_s(pTemp, sizeInBytes, pData, sizeInBytes);
}


//main.cpp

#include <iostream>
#include "ArrayList.h"

using namespace std;

int main()
{
	/*
	int* pInt = new int[3];
	pInt[0] = 1;
	pInt[1] = 1;
	pInt[2] = 1;
	

	ArrayList* pArray = new ArrayList();
	ArrayList arr;
		
	int i = arr[0];

	*/
	//arr[0] = i;


	//delete pArray;

	/*
	
	for(auto& i : arr)
		int temp = i;
		temp = -temp;
	
	*/
}
