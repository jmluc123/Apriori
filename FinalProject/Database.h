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
	void load(); //load file into mDatabase
	void write(DDLinkedList<Candidate<T>*>*, double);  //write L[k] and time to file
	void clear();
	~Database();
	void apriori();
	DDLinkedList<Candiate<T>*>* extract();//get L[1] list from database
	//void aprioriMain(DDLinkedList<Candidate<T>*>*); //pass in L[k-1] make this into a while loop
	DDLinkedList<Candidate<T>*>* aprioriGen(DDLinkedList<Candidate<T>*>*);
	DDLinkedList<Candidate<T>*>* subset(DDLinkedList<Candidate<T>*>*, int);
	
};


#endif