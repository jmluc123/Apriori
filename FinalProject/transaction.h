/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  ddlinkedList.h
*
*  Description:
*      This is the Candidate item which is a basic association rule.
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/
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
	int mSize;  //size of mItems
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
	void appendItem(T item);
};

/*
template <typename T>
Transaction<T>::Transaction()
{

}
*/
/*
*	Pre: A transaction is initialized
*	Post: Add an item to the transaction
*	Purpose: Add an item to the transaction
*/
template <typename T>
void Transaction<T>::appendItem(T item)
{
	if (mCount >= mSize)
	{
		cout << "Too may items for this transaction...";
		return;
	}
	mItems[mCount] = item;
	mCount++;
}

/*
*	Pre:  A transaction has been initialized and setID has been called
*	Post: return the id of the transaction
*	Purpose: get id of transaction
*/
template <typename T>
int Transaction<T>::getID()
{
	return mID;
}

/*
*	Pre: A transaction has been initialized
*	Post: returns number of items in transaction
*	Purpose: get how many items are actually in transaction
*/
template <typename T>
int Transaction<T>::getCount()
{
	return mCount;
}

/*
*	Pre:  Transaction is initialized
*	Post:  set the transaction id for the transaction object
*	Purpose: Set the transaction id to what is in the database
*/
template <typename T>
void Transaction<T>::setID(int id)
{
	mID = id;
}

/*
*	Pre:  Constructor for transaction object
*	Post:  transaction is initialized with id and maximum size
*	Purpose: Initialize the transaction object
*/
template <typename T>
Transaction<T>::Transaction(int id, int size)
{
	mID = id;
	mItems = new int[size];
	mSize = size;
	mCount = 0;
}

/*
*	Pre:  set an item in the transaction
*	Post: item is set
*	Purpose: set an item
*/
template <typename T>
void Transaction<T>::setItem(int index, T item)
{
	if (index >= mCount)
	{
		cout << "Transaction Index out of range (setItem)...\n";
		return;
	}
	mItems[index] = item;
}

/*
*	Pre: transaction is initialized
*	Post: return an item
*	Purpose: return an item from the transaction
*/
template <typename T>
T Transaction<T>::getItem(int index)
{
	if (index >= mCount)
	{
		cout << "Transaction Index out of range (getItem)...\n";
		return NULL;
	}
	return mItems[index];
}

/*
*	Pre: 
*	Post:
*	Purpose:  Experimental
*/
template <typename T>
bool Transaction<T>::contains(Candidate<T>* candidate)
{
	bool allAreIn = false;
	int itemsPresent = 0;
	for (int i = 0; i < candidate->getCount(); i++)//for each item in candidate compare against transaction
	{
		for (int c = 0; c < getCount(); c++)//for every item in transaction if item in candidate is in transaction, return true
		{
			if (candidate->getData(i) == getItem(c))
			{
				itemsPresent++;
				break;
			}
		}
	}
	//if (itemsPresent != candidate->getCount()) cout << "returning False...\n";
	return itemsPresent == candidate->getCount();
}



#endif