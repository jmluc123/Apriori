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
	Database(int count, int average);  //Josh
	Transaction* getIndex(int index);  //Ryan
	void appendTransaction(Transaction* transaction); //add a transaction to the end //Ryan
	void load(); //load file into mDatabase  //Josh
	void writeList(DDLinkedList<Candidate<T>*>*, double);  //write L[k] and time to file //Ryan
	~Database(); //delete transactions
	void apriori();  // Josh. calls extract then while loop which calls apriori-gen, subset and writeList
	DDLinkedList<Candidate<T>*>* extract();//get L[1] list from database  Ryan
	//void aprioriMain(DDLinkedList<Candidate<T>*>*); //pass in L[k-1] make this into a while loop
	DDLinkedList<Candidate<T>*>* aprioriGen(DDLinkedList<Candidate<T>*>*); //Ryan
	DDLinkedList<Candidate<T>*>* subset(DDLinkedList<Candidate<T>*>*, int);  //Josh
	
};

template <typename T>
Database<T>::Database(int count, int average)
{
	mDatabase = new Transaction[count];
	mTransactionCount = count;
	average = mAverageSize;
}

template <typename T>
Database<T>::~Database()
{
	delete[] mDatabase;
}
#endif