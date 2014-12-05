#ifndef TRANSACTION_H
#define TRANSACTION_H
/* Ryan */
#include "header.h"

template <typename T>
class Transaction
{
private:
	T* mItems; //item list
	int mCount; //number of items
	int mID;  //transaction id

public:
	Transaction(int id, int count);
	//Transaction();
	~Transaction();
	T getItem(int index);
	int getCount();
	void setItem(int index, T item);
	void setID(int id);
	bool contains(Candidate<T>* candidate);
	int getID();
};

/*
template <typename T>
Transaction<T>::Transaction()
{

}
*/
template <typename T>
int Transaction<T>::getID()
{
	return mID;
}

template <typename T>
int Transaction<T>::getCount()
{
	return mCount;
}

template <typename T>
void Transaction<T>::setID(int id)
{
	mID = id;
}

template <typename T>
Transaction<T>::Transaction(int id, int count)
{
	mID = id;
	mItems = new int[count];
}

template <typename T>
void Transaction<T>::setItem(int index, T item)
{
	if (index >= mCount)
	{
		cout << "Index out of range...\n";
		return;
	}
	mItems[index] = item;
}

template <typename T>
T Transaction<T>::getItem(int index)
{
	if (index >= mCount)
	{
		cout << "Index out of range...\n";
		return NULL;
	}
	return mItems[index];
}

template <typename T>
bool Transaction<T>::contains(Candidate<T>* candidate)
{
	bool isIn;
	bool allAreIn = true;
	for (int i = 0; i < candidate->getCount(); i++)
	{
		isIn = false;
		for (int c = 0; c < getCount(); c++)
		{
			if (candidate->getData(i) == getItem(c))
			{
				isIn = true;
				break;
			}
		}
		if (!isIn)
		{
			allAreIn = false;
			break;
		}
	}
	return allAreIn;
}



#endif