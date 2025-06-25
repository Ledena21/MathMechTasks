// Dictionary.h

#pragma once
#include <string>

struct Holder
{
	std::string Key;
	int Value;
	Holder* pNext;
};

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	void Add(std::string key, int value);
	
	int Get(std::string key);
	bool Contains(std::string key);
	bool Remove(std::string key);

private:
	int Hash(std::string key);
	void Resize();
	void Transfer(Holder** pNewBuckets, int oldBucketSize);
	void Add(Holder** pTempBuckets, std::string key, int value);
	void Add(Holder** pTempBuckets, Holder* pBucket);

	Holder** pBuckets;

	int bucketSize;
	int bucketCapacity;
	double growFactor;
	int threshold;
};

// Dicrionary.cpp

#include "Dictionary.h"

Dictionary::Dictionary()
{ 
	bucketSize = 0;
	bucketCapacity = 17;
	growFactor = 0.75;
	threshold = (int)(growFactor * bucketCapacity);
	pBuckets = new Holder * [bucketCapacity];
	memset(pBuckets, 0, bucketCapacity * sizeof(pBuckets[0]));
}

Dictionary::~Dictionary()
{
	for (int i = 0; i < bucketCapacity; ++i)
	{
		Holder* pBucket = pBuckets[i];
		while (pBucket != nullptr)
		{
			Holder* pDeleteNode = pBucket;
			pBucket = pBucket->pNext;
			delete pDeleteNode;
		}
	}
	delete[] pBuckets;
}

int Dictionary::Hash(std::string key)
{
	return 0;
}
 //0 - n-1 => 0 - 2*(n-1)
/*
0 1 2 3 4 5 6 7
0   2   4
*/
void Dictionary::Resize()
{
	int oldBucketCapacity = bucketCapacity;
	bucketCapacity *= 2;
	threshold = (int)(growFactor * bucketCapacity);
	Holder** pNewBuckets = new Holder * [bucketCapacity];
	memset(pNewBuckets, 0, bucketCapacity * sizeof(pNewBuckets[0]));
	Transfer(pNewBuckets, oldBucketCapacity);
	delete[] pBuckets;
	pBuckets = pNewBuckets;

}

void Dictionary::Transfer(Holder** pNewBuckets, int oldBucketCapacity)
{
	for (int i = 0; i < oldBucketCapacity; ++i)
	{
		Holder* pBucket = pBuckets[i];
		if (pBucket == nullptr)
			continue;

		while (pBucket != nullptr)
		{
			int idx = Hash(pBucket->Key);
			
			//pNewBuckets[idx] = pBucket; // -???
			Add(pNewBuckets, pBucket);
			pBucket = pBucket->pNext;
		}
	}
}

void Dictionary::Add(Holder** pTempBuckets, std::string key, int value)
{
	int idx = Hash(key);
	Holder* pBucket = pBuckets[idx];
	while (pBucket != nullptr)
	{
		if (pBucket->Key == key)
		{
			pBucket->Value = value;
			return;
		}
		pBucket = pBucket->pNext;
	}

	Holder* pNewHolder = new Holder();
	pNewHolder->Key = key;
	pNewHolder->Value = value;

	Add(pTempBuckets, pNewHolder);
}

void Dictionary::Add(Holder** pTempBuckets, Holder* pNewHolder)
{
	int i = Hash(pNewHolder->Key);
	/* Вставляем в конец O(1+a)*/
	Holder* pBucket = pTempBuckets[i];
	if (pBucket == nullptr)
	{
		pTempBuckets[i] = pNewHolder;
		++bucketSize;
		return;
	}

	while (pBucket->pNext != nullptr)
		pBucket = pBucket->pNext;
		
	pBucket->pNext = pNewHolder;

	/* Подменяем голову O(1)
	if (pBuckets[i] == nullptr)
		++bucketSize;
	pNewHolder->pNext = pTempBuckets[i];
	pTempBuckets[i] = pNewHolder;
	*/
}

void Dictionary::Add(std::string key, int value)
{
	if (bucketSize >= threshold)
		Resize();

	Add(pBuckets, key, value);
}

int Dictionary::Get(std::string key)
{
	int idx = Hash(key);
	Holder* pBucket = nullptr;
	return 0;
}
