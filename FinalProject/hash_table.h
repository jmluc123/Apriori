#include "header.h"

template <typename T>
class BSTHashTable
{
private:
	int size;
	BST_Node_Candidate* bucket;
	int hash(Candidate<T>* candidate);
public:
	BSTHashTable(int listSize);
	~BSTHashTable();
	void add(Candidate<T>* candidate);
	void prune(Transaction<T>* transaction, DDLinkedList<Candidate<int>*>* CT);
};

template <typename T>
int hash(Candidate<T>* candidate)
{
	return candidate->getData(0) % size;
}

template <typename T>
BSTHashTable<T>::BSTHashTable(int listSize)
{
	size = listSize;
	bucket = new BST_Node_Candidate[size];
}

template <typename T>
BSTHashTable<T>::~BSTHashTable()
{
	delete[] bucket;
}

template<typename T>
void BSTHashTable<T>::add(Candidate<T>* candidate)
{
	int index = hash(candidate);
	if (bucket[index])
		bucket[index]->add(candidate);
	else
		bucket[index]->add(candidate);
}

template <typename T>
bool BSTHashTable<T>::contains(Candidate<T>* candidate)
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

template <typename T>
void BSTHashTable<T>::prune(Transaction<T>* transaction, DDLinkedList<Candidate<int>*>* CT)
{
	for (int i = 0; i < size; i++)
	{
		CT = bucket[i]->prune(transaction, CT, bucket[i]);
	}
}


