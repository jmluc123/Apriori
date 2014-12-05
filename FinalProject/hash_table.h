/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  hash_table.h
*
*  Description:
*	This is the hash table to be used in the subset function
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "header.h"

class BSTHashTable
{
private:
	int mSize; //size of hash array
	BST_Node_Candidate** bucket;
public:
	BSTHashTable(int listSize);
	~BSTHashTable();
	void add(Candidate<int>* candidate);
	void prune(Transaction<int>* transaction, DDLinkedList<Candidate<int>*>* CT);
	bool contains(Candidate<int>* candidate);
	int hash(Candidate<int>* candidate);
	int getSize();
};



#endif