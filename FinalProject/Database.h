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
	Transaction<T>* getIndex(int index);  //
	void appendTransaction(Transaction<T>* transaction); //add a transaction to the end //Ryan
	void load(); //load file into mDatabase  //Josh
	void writeList(DDLinkedList<Candidate<T>*>*, double);  //write L[k] and time to file //Ryan
	~Database(); //delete transactions
	void apriori(int minsup);  // Josh. calls extract then while loop which calls apriori-gen, subset and writeList
	DDLinkedList<Candidate<T>*>* extract();//get L[1] list from database  Ryan
	//void aprioriMain(DDLinkedList<Candidate<T>*>*); //pass in L[k-1] make this into a while loop
	DDLinkedList<Candidate<T>*>* aprioriGen(DDLinkedList<Candidate<T>*>*); //Ryan
	DDLinkedList<Candidate<T>*>* subset(DDLinkedList<Candidate<T>*>*, int);  //Josh
	DDLinkedList<Candidate<T>*>* prune(DDLinkedList<Candidate<T>*>* CK, int minsup); //Josh prune CK for next LK
	void initializeOutput(); //writeList only appends, we need one to overwrite and add a header //Ryan | done
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

//gets L1 which is just single sets of each item
template<typename T>
DDLinkedList<Candidate<T>*>* Database<T>::extract()
{
	DDLinkedList<Candidate<T>*>* L1 = new DDLinkedList<Candidate<T>*>;

	//fill L1 with Candidates, one for each item - N
	for (int i = 0; i < mNumberOfItems; i++)
	{
		Candidate<T>* newC = new Candidate<T>;

		//add the single item to the set
		newC->insert(i);

		L1->insert(newC);
	}

	return L1;
}


/*
Joins by checking every Candidate vs every other Candidate
Prunes by counting subsets, < k subsets means it will be pruned
*/
template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::aprioriGen(DDLinkedList<Candidate<T>*>* Lkp)
{
	DDLinkedList<Candidate<T>*>* Ck = new DDLinkedList<Candidate<T>*>;
	DDLinkedList<Candidate<T>*>* tmp = Ck;
	int k;

	//i = set, j = set to compare with
	for (int i = 0; i < Lkp->getCount() - 1; i++)
	{
		Candidate<T>* toCopy1 = Lkp->getData(i);
		DDLinkedList<Candidate<T>*>* copyTracker = new DDLinkedList<Candidate<T>*>;
		k = toCopy1->getCount() + 1;

		//fill tmp with p x q
		for (int j = i + 1; j < Lkp->getCount(); i++)
		{
			Candidate<T>* toAdd = new Candidate<T>;
			Candidate<T>* toCopy2 = Lkp->getData(j);
			for (int g = 0; g < toCopy1->getCount(); g++)
			{//fill candidates 
				toAdd->insert(toCopy1->getData(g));
				toAdd->insert(toCopy2->getData(g));
			}

			//only add if |tmp| = k and if nCp = k
			if (toAdd->getCount() == k)
			{
				if (checkEquivalent(toAdd, tmp))
					tmp->insert(toAdd);

				//also add it to tracker
				copyTracker->insert(toAdd);
			}

			//prune while joining

			for (int j = 0; j < tmp->getCount(); j++)
			{//for each member of tmp
				int copyCount = 0;
				Candidate<T>* toCheck = tmp->getData(j);
				for (int g = 0; g < copyTracker->getCount(); g++)
				{//count how many of each set are in copyTracker					
					Candidate<T>* copyCheck = copyTracker->getData(g);

					if (copyCheck->operator==(toCheck))
						copyCount++;
				}
				//add if there are (k) copies
				if (copyCount >= k)
					Ck->insert(tmp->getData(j));
			}
		}
	}
	return Ck;
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
//check if a candidate set is present in a set of sets
template <typename T>
bool checkEquivalent(Candidate<T>* s1, DDLinkedList<Candidate<T>*>* s2)
{
	for (int i = 0; i < s2->getCount(); i++)
	{
		if (s1->operator==(s2->getData(i)))
			return false;
	}

	return true;
}

template<typename T>
void Database<T>::writeList(DDLinkedList<Candidate<T>*>* itemSet, double time)
{
	ofstream outFile;
	Candidate<T>* candidate;
	int cItemSet = 0;
	outFile.open(mOutFileName.c_str(), ios::out | ios::app);

	if (itemSet->getCount() > 0)
	{
		candidate = itemSet->getData(0);
		cItemSet = candidate->getCount();
	}

	outFile << cItemSet << "-itemsets: (" << itemSet->getCount() << " in total) ";

	for (int i = 0; i < itemSet->getCount(); i++)
	{
		outFile << "{";
		candidate = itemSet->getData(i);
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
#endif