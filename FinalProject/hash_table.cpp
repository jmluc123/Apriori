/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  header.h
*
*  Description:
*      hash_table functions
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/

#include "header.h"


/*
*	Pre: hash table is declared
*	Post: initializes hash table
*	Purpose: constructor
*/
BSTHashTable::BSTHashTable(int listSize)
{
	mSize = listSize;
	bucket = new BST_Node_Candidate*[mSize];
	for (int i = 0; i < mSize; i++)
	{
		bucket[i] = new BST_Node_Candidate(mSize);
	}
}

/*
*	Pre: hash table is initialized
*	Post: deletes bucket
*	Purpose: deconstructor
*/
BSTHashTable::~BSTHashTable()
{
	delete[] bucket;
}

/*
*	Pre:  At least one node is initialized in hash table.
*	Post: adds a candidate to the node tree
*	Purpose: add a candidate to the hash tree
*/
void BSTHashTable::add(Candidate<int>* candidate)
{
	int index = hash(candidate);
	bucket[index]->add(candidate, bucket[index]);
}

/*
*	Pre:  bsthashtable is initialized
*	Post: returns true if a candidate is found in a node tree
*	Purpose: find out if a candidate exists in a node tree
*/
bool BSTHashTable::contains(Candidate<int>* candidate)
{
	int index = hash(candidate);
	if (bucket[index] == NULL)
	{
		return false;
	}
	else
	{
		return bucket[index]->isExist(candidate, bucket[index]);
	}
}

/*
*	Pre:  BSTHashTable is initialized and a transaction has been passed with an empty C[t] set. 
*	Post:  Load CT with candidates from the hash table that are in the transaction
*	Purpose: tests if candidates in node tree are in transaction.  Adds to CT if they are.
*/
void BSTHashTable::prune(Transaction<int>* transaction, DDLinkedList<Candidate<int>*>* CT)
{
	for (int i = 0; i < mSize; i++)
	{
		bucket[i]->prune(transaction, CT, bucket[i]);
	}
}

/*
*	Pre:  BST table is initialized.  An add has been called.  
*	Post:  returns index of appropriate index in hash table
*	Purpose: hash the hash table of trees
*/
int BSTHashTable::hash(Candidate<int>* candidate)
{
	return candidate->getData(0) % mSize;
}
