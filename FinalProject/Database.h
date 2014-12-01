#ifndef DATABASE_H
#define DATABASE_H

#include "header.h"

template <typename T>
class Database
{
	Transaction** mDatabase; //array of transaction pointers
	int mTransactionCount; //number of transactions
	int mAverageSize;  //average size of transactions
public:
	Database(int count, int average);
	Transaction* getIndex(int index);
	void setIndex(Transaction*& transaction, int index);
	void appendTransaction(Transaction* transaction); //add a transaction to the end
	void clear();
	~Database();
};


#endif