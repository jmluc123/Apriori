#ifndef DATABASE_H
#define DATABASE_H

#include "header.h"

template <typename T>
class Database
{
	Transaction<T>** mDatabase; //array of transaction pointers
	int mTransactionCount; //number of transactions D
	int mAverageSize;  //average size of transactions T
	int mNumberOfItems; //N
	float mMinSupp; //S
	string mOutFileName;
public:
	Database(int count, int average, int numItems, float minSupp);  //Josh | done
	Transaction<T>* getIndex(int index);  //Ryan | done
	void appendTransaction(Transaction<T>* transaction); //add a transaction to the end //Ryan | done
	void load(); //load file into mDatabase  //Josh | done
	void writeList(DDLinkedList<Candidate<T>*>*, double);  //write L[k] and time to file //Ryan | done
	void initializeOutput(); //writeList only appends, we need one to overwrite and add a header //Ryan | done
	~Database(); //delete transactions | done
	void apriori();  // Josh. calls extract then while loop which calls apriori-gen, subset and writeList |
	DDLinkedList<Candidate<T>*>* extract();//get L[1] list from database  Ryan | done
	//void aprioriMain(DDLinkedList<Candidate<T>*>*); //pass in L[k-1] make this into a while loop
	DDLinkedList<Candidate<T>*>* aprioriGen(DDLinkedList<Candidate<T>*>*); //Ryan | 
	DDLinkedList<Candidate<T>*>* subset(DDLinkedList<Candidate<T>*>*, int);  //Josh | 
	
};

template <typename T>
Database<T>::Database(int count, int average, int numItems, float minSupp)
{
	mDatabase = new Transaction<T>*[count];
	mTransactionCount = count;
	mAverageSize = average;
	mNumberOfItems = numItems;
	mMinSupp = minSupp;

	mOutFileName = toString(average) + "_" + toString(count) + "_" + toString(numItems)
		+ "_" + toString(minSupp) + "_Output.txt";

	initializeOutput();
}

template <typename T>
Database<T>::~Database()
{
	delete[] mDatabase;
}

template <typename T>
Transaction<T>* Database<T>::getIndex(int index)
{
	return mDatabase[index];
}

template <typename T>
void Database<T>::appendTransaction(Transaction<T>* transaction)
{
	Transaction<T>** newDatabase = new Transaction<T>[++mTransactionCount];
	int i;
	for (i = 0; i < mTransactionCount - 1; i++)
		newDatabase[i] = mDatabase;
	newDatabase[i] = transaction;
	mDatabase = newDatabase;
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

template<typename T>
void Database<T>::initializeOutput()
{
	ofstream outFile;
	outFile.open(mOutFileName.c_str(), ios::out);
	
	outFile << "T = " << mAverageSize
		<< ", N = " << mNumberOfItems
		<< ", D = " << mTransactionCount
		<< ", S = " << mMinSupp
		<< endl << endl
		<< "----------------------------------------------------"
		<< endl;

	outFile.close();
}

//get the current itemset# in here somehow
template<typename T>
void Database<T>::writeList(DDLinkedList<Candidate<T>*>* itemSet, double time)
{
	ofstream outFile;
 
	outFile.open(mOutFileName.c_str(), ios::out | ios::app);
	
	int cItemSet = -1;
	outFile << cItemSet << "-itemsets: (" << itemSet->getCount() << " in total) ";
	
	for (int i = 0; i < itemSet->getCount(); i++)
	{
		outFile << "{";
		Candidate<T>* candidate = itemSet->getData(i);
		for (int j = 0; j < candidate->getCount(); j++)
		{
			if (j > 0 && j < candidate->getCount() - 1)
				outFile << ",";
			outFile << candidate->getData(j);
			
		}
		outFile << "} ";	
	}
	outFile << endl
		<< "Time for " << cItemSet << "-itemsets: " << time << endl;

	outFile.close();
}

//gets L1 which is just single sets of each item
template<typename T>
DDLinkedList<Candidate<T>*>* Database<T>::extract()
{
	DDLinkedList<Candidate<T>*>* L1 = new DDLinkedList<Candidate<T>*>; 

	//fill L1 with Candidates, one for each item - N
	for (int i = 0; i < mNumberOfItems; i++)
	{
		Candidate<T>* newC = new Candidate<T>;

		for (int j = 0; j < 5; j++)
		{
			//add the single item to the set
			newC->insert(j * 9);
		}
		

		L1->insert(newC);
	}
	writeList(L1, 0);

	return L1;
}
#endif