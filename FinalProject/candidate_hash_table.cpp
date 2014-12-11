#include "header.h"

CandidateHashTable::CandidateHashTable(int listSize)
{
	mSize = listSize;
	bucket = new Candidate<int>*[mSize];
	for (int i = 0; i < mSize; i++)
	{
		bucket[i] = NULL;
	}
}

CandidateHashTable::CandidateHashTable(int listSize, Candidate<int>* candidate)
{
	mSize = listSize;
	bucket = new Candidate<int>*[mSize];
	for (int i = 0; i < mSize; i++)
	{
		bucket[i] = NULL;
	}
	add(candidate);
}

CandidateHashTable::~CandidateHashTable()
{
	delete[] bucket;
}

Candidate<int>* CandidateHashTable::getCandidate(int index)
{
	if (bucket[0])
	{
		return bucket[0];
	}
	//cout << "getCandidate returned NULL candidate...";
	return NULL;
}

bool CandidateHashTable::isEmpty()
{
	for (int i = 0; i < mSize; i++)
	{
		if (bucket[i]) return false;
	}
	return true;
}

bool CandidateHashTable::add(Candidate<int>* candidate)
{
	int index = hash(candidate); //hash it
	int count = 0;
	while (bucket[index] != NULL && count < mSize) //find a free spot
	{
		count++;
		index++;
		if (index >= mSize) index = 0;
	}
	if (count < mSize) //if a free spot was found
	{
		bucket[index] = candidate;
		return true;
	} 
	return false; //if a free spot was not found return false
}

bool CandidateHashTable::contains(Candidate<int>* candidate)
{
	for (int i = 0; i < mSize; i++)
	{
		if (bucket[i])
		{
			if (candidate->compare(bucket[i])) return true;
		}
	}
	return false;
}

int CandidateHashTable::hash(Candidate<int>* candidate)
{
	int value = candidate->getData(0);
	return value % mSize;
}
int CandidateHashTable::getSize()
{
	return mSize;
}