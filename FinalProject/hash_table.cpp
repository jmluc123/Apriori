#include "header.h"

BSTHashTable::BSTHashTable(int listSize)
{
	mSize = listSize;
	bucket = new BST_Node_Candidate*[mSize];
}


BSTHashTable::~BSTHashTable()
{
	delete[] bucket;
}


void BSTHashTable::add(Candidate<int>* candidate)
{
	int index = hash(candidate);
	bucket[index]->add(candidate);
}


bool BSTHashTable::contains(Candidate<int>* candidate)
{
	int index = hash(candidate);
	if (bucket[index] == NULL)
	{
		return false;
	}
	else
	{
		return bucket[index]->isExist(candidate);
	}
}

void BSTHashTable::prune(Transaction<int>* transaction, DDLinkedList<Candidate<int>*>* CT)
{
	for (int i = 0; i < mSize; i++)
	{
		bucket[i]->prune(transaction, CT, bucket[i]);
	}
}

int BSTHashTable::hash(Candidate<int>* candidate)
{
	return candidate->getData(0) % mSize;
}
