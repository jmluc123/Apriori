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
	void apriori(int minsup);  // Josh. calls extract then while loop which calls apriori-gen, subset and writeList
	DDLinkedList<Candidate<T>*>* extract();//get L[1] list from database  Ryan
	//void aprioriMain(DDLinkedList<Candidate<T>*>*); //pass in L[k-1] make this into a while loop
	DDLinkedList<Candidate<T>*>* aprioriGen(DDLinkedList<Candidate<T>*>*); //Ryan
	DDLinkedList<Candidate<T>*>* subset(DDLinkedList<Candidate<T>*>*, int);  //Josh
	DDLinkedList<Candidate<T>*>* prune(DDLinkedList<Candidate<T>*>*); //Josh prune CK for next LK
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
			while (stream >> itemArray[count])
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

template <typename T>
void Database<T>::apriori(int minsup)
{
	DDLinkedList<Candidate<T>*>* LK_1 = extract();
	DDLinkedList<Candidate<T>*>* CK;
	DDLinkedList<Candidate<T>*>* CT;
	Candidate<T>* candidate;
	Candidate<T>* ctCandidate;
	double time;
	double compiledTime = 0;
	TimerSystem timer;
	int k = 2;
	while (!LK_1->isEmpty())
	{
		timer.startClock();
		CK = aprioriGen(LK_1);
		for (int i = 0; i < mTransactionCount; i++) //for each transaction in database
		{
			CT = subset(CK, i);
			for (int c = 0; c < CK->getCount(); c++)  //for each candidate in CK
			{
				candidate = CK->getData(c);
				for (int ctCount = 0; ctCount < CT->getCount(); ctCount++) //test if candidate is in CT
				{
					ctCandidate = CT->getData(ctCount);
					if (candidate->compare(ctCandidate)) candidate->mRepeatCount++; //if there is a match increment mRepeatCount for CK candidate
				}
			}
			delete CT;
		}
		delete LK_1;
		LK_1 = prune(CK, minsup); //prune all lists from CK that don't have the required mRepeatCount
		time = timer.getTime();
		writeList(LK_1, time);
		compiledTime = compiledTime + time;
		delete CK;
		k++;
	}
	delete LK_1;
}

template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::extract()
{
	return new DDLinkedList<Candidate<T>*>();
}

template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::aprioriGen(DDLinkedList<Candidate<T>*>* ddlinkedlist)
{
	return new DDLinkedList<Candidate<T>*>();
}

template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::subset(DDLinkedList<Candidate<T>*>* CK, int index)
{
	DDLinkedList<Candidate<T>*>* CT = new DDLinkedList<Candidate<T>*>();
	BSTHashTable<T>* bsthashtable = new BSTHashTable(mAverageSize % 100);
	Transaction<T>* transaction = mDatabase[index];
	for (int i = 0; i < CK->mCount(); i++)
	{
		bsthashtable->add(CK->getData(i));
	}
	bsthashtable->prune(transaction, CT);
	return CT;
}

template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::prune(DDLinkedList<Candidate<T>*>* CK, int minsup)
{
	for (int i = 0; i < CK->getCount(); i++)
	{
		if (CK->getData(i)->mRepeatCount < minsup)
		{
			CK->removeAt(i);
		}
	}
	return CK;
}

template <typename T>
void Database<T>::writeList(DDLinkedList<Candidate<T>*>* ddlinkedlist, double time)
{

}

#endif