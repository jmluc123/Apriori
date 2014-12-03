#ifndef DATABASE_H
#define DATABASE_H

#include "header.h"

template <typename T>
class Database
{
	Transaction<T>** mDatabase; //array of transaction pointers
	int mTransactionCount; //number of transactions
	int mAverageSize;  //average size of transactions
public:
	Database(int count, int average);  //Josh
	Transaction<T>* getIndex(int index);  //Ryan
	void appendTransaction(Transaction<T>* transaction); //add a transaction to the end //Ryan
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
	mDatabase = new Transaction<T>*[count];
	mTransactionCount = count;
	mAverageSize = average;
}

template <typename T>
Database<T>::~Database()
{
	delete[] mDatabase;
}

template <typename T>
void Database<T>::load()
{
	ifstream theFile("transactions.txt");
	if (theFile.is_open())
	{
		string line;
		int count = 0;
		int i = 0;
		while (getline(theFile, line))
		{
			int* itemArray = new int[mAverageSize * 20];
			count = 0;
			stringstream stream(line);
			while (stream >> itemArray[i])
			{
				count++;
			}
			Transaction<T>* transaction = new Transaction<T>(itemArray[0],count);
			for (int iterate = 1; iterate <= count; iterate++) transaction->setItem(iterate - 1, itemArray[iterate]);
			mDatabase[i] = transaction;
			delete[] itemArray;
			i++;
		}
	}
	else
	{
		cout << "Error opening file...\n";
	}
}
#endif