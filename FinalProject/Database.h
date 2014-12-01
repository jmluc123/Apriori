#ifndef DATABASE_H
#define DATABASE_H

#include "header.h"

template <typname T>
class Database
{
	Transaction** mDatabase; //array of transaction pointers
	int mTransactionCount; //number of transactions
	int mAverageSize;  //average size of transactions
public:
	Database(int count, int average);
	Transaction* getIndex(int index);
	setIndex(Transaction*& transaction, index);
	appendTransaction(Transaction* transaction); //add a transaction to the end
	clear();
	~Database();
};


#endif