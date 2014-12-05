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