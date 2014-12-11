/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  hash_table.h
*
*  Description:
*	This is a hash table to be used in the subset function for BST nodes
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/
#ifndef CANDIDATE_HASH_TABLE_H
#define CANDIDATE_HASH_TABLE_H

#include "header.h"

class CandidateHashTable
{
private:
	int mSize; //size of hash array
	Candidate<int>** bucket;
public:
	CandidateHashTable(int listSize);
	CandidateHashTable(int listSize, Candidate<int>* candidate);
	~CandidateHashTable();
	bool add(Candidate<int>* candidate);
	bool contains(Candidate<int>* candidate);
	int hash(Candidate<int>* candidate);
	int getSize();
	bool isEmpty();
	Candidate<int>* getCandidate(int index);
};


#endif