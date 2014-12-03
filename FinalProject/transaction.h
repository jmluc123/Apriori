#ifndef TRANSACTION_H
#define TRANSACTION_H
/* Ryan */
#include "header.h"

template <typename T>
class Transaction
{
private:
	int* mItems; //item list
	int mCount; //number of items
	int mID;  //transaction id

public:
	Transaction(int id, int count);
	Transaction();
	~Transaction();
	int getItem(int index);
	int getCount(int index);
	void setItem(int index, int item);
	void setID(int id);
	void clear();
};

/*
template <typename T>
Transaction<T>::Transaction()
{

}
*/

template <typename T>
Transaction<T>::Transaction(int id, int count)
{

}

template <typename T>
void Transaction<T>::setItem(int index, int item)
{
}





#endif