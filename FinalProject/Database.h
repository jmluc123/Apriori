/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  database.h
*
*  Description:
*      This is the database object and the central component to the application.
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/
#ifndef DATABASE_H
#define DATABASE_H

#include "header.h"

template <typename T>
class Database
{
	Transaction<T>** mDatabase; //array of transaction pointers
	int mSize;
	int mTransactionCount; //number of transactions D
	int mAverageSize;  //average size of transactions T
	int mNumberOfItems; //N
	float mMinSupp; //S
	string mOutFileName;
public:
	Database(int size, int average, int numItems, float minSupp);  //Josh | done
	Transaction<T>* getIndex(int index);  //get transaction object from mDatabase
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


/*
* Pre: Data has been generated.  Size is the number of transactions requested from the generator.  Average is the average size per transactions.  numItems are the total
number of distinct items.  minsupp is used for the pruning function
* Post: A database is initialized as well as the file to write to.  
* Purpose:  Initialize a database.  
*/
template <typename T>
Database<T>::Database(int size, int average, int numItems, float minSupp)
{
	mDatabase = new Transaction<T>*[size];
	mSize = size;
	mTransactionCount = 0;
	mAverageSize = average;
	mNumberOfItems = numItems;
	mMinSupp = minSupp;

	mOutFileName = toString(average) + "_" + toString(mTransactionCount) + "_" + toString(numItems)
		+ "_" + toString(minSupp) + "_Output.txt";

	initializeOutput();
}


/*
*	Pre:	
*	Post:
*	Purpose: Deconstructor
*/
template <typename T>
Database<T>::~Database()
{
	delete[] mDatabase;
}


/*
*	Pre:  Database is initialized
*	Post: returns Transaction item from the database
*	Purpose: Get a transaction from the database for analysis
*/
template <typename T>
Transaction<T>* Database<T>::getIndex(int index)
{
	return mDatabase[index];
}

/*
*	Pre:  Database is initialized
*	Post: adds a transaction to the end of the database
*	Purpose: add a transaction to the database
*/
template <typename T>
void Database<T>::appendTransaction(Transaction<T>* transaction)
{
	mDatabase[mTransactionCount] = transaction;
	mTransactionCount++;
}

/*
*	Pre: Database is initialized
*	Post:  Data is loaded into a file
*	Purpose: load data from transactions.txt
*/
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
			Transaction<T>* transaction = new Transaction<T>(itemArray[0],count - 1);
			for (int iterate = 1; iterate < count; iterate++)
			{
				transaction->appendItem(itemArray[iterate]);
			}
			appendTransaction(transaction);
			delete[] itemArray;
			i++;
		}
	}
	else
	{
		cout << "Error opening file...\n";
	}

}

/*
*	Pre:  Database is initialized and load function has been called
*	Post: association rules are written to file
*	Purpose: Execute Apriori algorithm logic
*/
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
	while (LK_1)
	{
		if (!LK_1->isEmpty())
		{
			timer.startClock();
			CK = aprioriGen(LK_1); //CK is a new list generated by LK_1
			if (CK->getCount() <= 0)
			{
				delete CK;
				break;
			}
			for (int i = 0; i < CK->getCount(); i++) //clear all candidates to 0 repeats
			{
				CK->getData(i)->mRepeatCount = 0;
			}
			LK_1->ultraKill();
			delete LK_1; //ok to delete LK_1
			for (int i = 0; i < mTransactionCount; i++) //for each transaction in database
			{
				CT = subset(CK, i); //extract set of candidates that are found in transaction
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

			LK_1 = prune(CK, minsup); //prune all lists from CK that don't have the required mRepeatCount. Returns CK and assigns to LK_1. (don't delete CK)
			time = timer.getTime();
			writeList(LK_1, time);
			compiledTime = compiledTime + time;
			//delete CK; don not dlete CK because you will be deleting LK_1
			k++;
			if (LK_1->getCount() <= 0) break;
		}
	}
	if (LK_1)
	{
		LK_1->ultraKill();
		delete LK_1;
	}
}

/*
*	Pre:  Database has been declared and is being initialized
*	Post: Initialize file for output
*	Purpose: Initialize file output
*/
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

/*
*	Pre: Database is initialized and load has been called
*	Post: extract all distinct items for L1 candidate set
*	Purpose: Get L1 candidate set
*/
//gets L1 which is just single sets of each item
template<typename T>
DDLinkedList<Candidate<T>*>* Database<T>::extract()
{
	DDLinkedList<Candidate<T>*>* L1 = new DDLinkedList<Candidate<T>*>();
	int itemCount = 0;
	T item;
	bool found;
	//fill L1 with Candidates, one for each item - N
	for (int i = 0; i < mTransactionCount; i++) //for each transaction
	{
		Transaction<T>* transaction = mDatabase[i];
		for (int j = 0; j < transaction->getCount(); j++) //for each item in transaction
		{
			item = transaction->getItem(j);
			Candidate<T>* candidate;
			if (L1->getCount() == 0) //test for a candidate item
			{
				candidate = new Candidate<T>(item); //add first item
				L1->insert(candidate);
			} 
			else //for all other items
			{
				found = false;
				for (int x = 0; x < L1->getCount(); x++) // test if item is in L1 candidates already
				{
					if (L1->getData(x)->getCount() > 0)
					{
						if (item == L1->getData(x)->getData(0)) //test if 0 index of candidate is equal to item.  If the item is not found in L1 found remains false
						{
							found = true;
							break;
						}
					}
				}
				if (found == false) //if the item was not found in L1, add to L1
				{
					candidate = new Candidate<T>(item);
					L1->insert(candidate);
				}
			}
		}
	}

	return L1;
}

template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::aprioriGen(DDLinkedList<Candidate<T>*>* LK_1)
{
	int k = LK_1->getData(0)->getCount() + 1;
	DDLinkedList<Candidate<T>*>* CK = new DDLinkedList<Candidate<T>*>();
	DDLinkedList<Candidate<T>*>* subsets;
	Candidate<T>* result;
	int count = 0;
	for (int i = 0; i < LK_1->getCount(); i++)
	{
		for (int c = 0; c < LK_1->getCount(); c++)
		{
			if (LK_1->getData(i) != LK_1->getData(c) && !LK_1->getData(i)->compare(LK_1->getData(c))) //if they are not equal to each other
			{
				result = LK_1->getData(i)->intersection(LK_1->getData(c)); //get the intersection
				if (result->getCount() == k - 2) //if intersection is correct get the union
				{
					delete result;  //don't need the intersection
					result = LK_1->getData(i)->unionize(LK_1->getData(c)); //get the union
					subsets = result->subsets(); //get all the subsets of result
					//test if all subsets are present in LK_1
					count = 0;
					for (int j = 0; j < subsets->getCount(); j++)
					{
						for (int l = 0; l < LK_1->getCount(); l++)
						{
							if (subsets->getData(j)->compare(LK_1->getData(l)))
							{
								count++; //count the subsets that are present
								break;
							}
						}
					}
					bool inCK = false;
					//test if the subset is already in CK
					for (int x = 0; x < CK->getCount(); x++)
					{
						if (result->compare(CK->getData(x)))
						{
							inCK = true;
							break;
						}
					}
					if(subsets->getCount() == count  && !inCK) CK->insert(result); //if all subsets are present, add to LK_1
					subsets->ultraKill(); //don't need this set of subsets anymore
					delete subsets; 
				}
			}
		}
	}
	return CK;
}

/*
*	Pre:  Apriori has been called.  While loop is initiated.  L[k-1] is passed
*	Post: returns C[k] by joining sets
*	Purpose: Joins by checking every Candidate vs every other Candidate
*   Prunes by counting subsets, < k subsets means it will be pruned
*/
/*
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

		//if (k > 2)
		//	cout << i << " ";

		//fill tmp with p x q
		for (int j = i + 1; j < Lkp->getCount(); j++)
		{
			
			Candidate<T>* toAdd = new Candidate<T>;
			Candidate<T>* toCopy2 = Lkp->getData(j);
			for (int g = 0; g < toCopy2->getCount(); g++)
			{//fill candidates 
				if (toCopy1->getData(g) != toCopy2->getData(g))
				{
					toAdd->insert(toCopy1->getData(g));
				}
				toAdd->insert(toCopy2->getData(g));
				
			}

			//only add if |tmp| = k and if nCp = k

			
			if (toAdd->getCount() == k)
			{				
				if (checkEquivalent(toAdd, tmp))
				{					
					tmp->insert(toAdd);
					
					if (k <= 2)
						Ck->insert(toAdd);

				}	
				//also add it to tracker
				copyTracker->insert(toAdd);
			}			
		}

		if (k > 2)
		{
			
			//prune while joining
			for (int j = 0; j < tmp->getCount(); j++)
			{//for each member of tmp
				int copyCount = 0;
				Candidate<T>* toCheck = tmp->getData(j);
				for (int g = 0; g < copyTracker->getCount(); g++)
				{//count how many of each set are in copyTracker					
					Candidate<T>* copyCheck = copyTracker->getData(g);
					if(copyCheck->operator==(toCheck)) //(copyCheck->compare(toCheck))
						copyCount++;
				}
				//add if there are (k) copies
				if (copyCount >= k)
					Ck->insert(tmp->getData(j));
			}
			
		}

		delete copyTracker;
		
	}
	return Ck;
}
*/
/*
*	Pre: Apriori is called
*	Post: returns pruned subsets from has tree algorithm
*	Purpose: Execute the subset function in Apriori Threshold is set to 1
*/
template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::subset(DDLinkedList<Candidate<T>*>* CK, int index)
{
	DDLinkedList<Candidate<T>*>* CT = new DDLinkedList<Candidate<T>*>();
	Transaction<T>* transaction = mDatabase[index];
	for (int i = 0; i < CK->getCount(); i++)
	{
		if (transaction->contains(CK->getData(i))) CT->insert(CK->getData(i));  //if the candidate is in the transaction, add to CT
	}
	return CT;
}

/*
*	Pre: Apriori is called
*	Post: prunes CK further and returns CK changed
*	Purpose: prune out items that don't have a repeat count above minsup
*/
template <typename T>
DDLinkedList<Candidate<T>*>* Database<T>::prune(DDLinkedList<Candidate<T>*>* CK, int minsup)
{
	DDLinkedList<Candidate<T>*>* LK_1 = new DDLinkedList<Candidate<T>*>();
	for (int i = 0; i < CK->getCount(); i++)
	{
		if (CK->getData(i)->mRepeatCount >= minsup)
		{
			LK_1->insert(CK->getData(i));
		}
		else
		{
			delete CK->getData(i);
		}
	}
	delete CK;
	return LK_1;
}

/*
*	Pre: 
*	Post:
*	Purpose: Experimental
*/
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

/*
*	Pre: apriori has run 
*	Post: written to file
*	Purpose: Writes a group of association rules to the file
*/
template<typename T>
void Database<T>::writeList(DDLinkedList<Candidate<T>*>* itemSet, double time)
{
	ofstream outFile;
	Candidate<T>* candidate;
	int cItemSet = 0;
	outFile.open(mOutFileName.c_str(), ios::out | ios::app);

	if (outFile.is_open())
	{
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
				if (j > 0)
					outFile << ",";
				outFile << candidate->getData(j);
			}
			outFile << "} ";
		}
		outFile << endl
			<< "Time for " << cItemSet << "-itemsets: " << time << endl;

		outFile.close();
	}
	else
	{
		cout << "Could not open file for write...";
	}
}
#endif