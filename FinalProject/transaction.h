#ifndef TRANSACTION_H
#define TRANSACTION_H
/* Ryan */
#include "header.h"

class Transaction
{
private:
	int* mItems; //item list
	int mCount; //number of items
	int mID;  //transaction id

public:
	Transaction(int id, int count);
	~Transaction();
	int getItem(int index);
	int getCount(int index);
	void setItem(int index, int item);
	void clear();
};





#endif