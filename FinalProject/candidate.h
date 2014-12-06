/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  candidate.h
*
*  Description:
*      This is the Candidate item which is a basic association rule.  
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/

#ifndef CANDIDATE_H
#define CANDIDATE_H
/* Ryan */
#include "header.h"

template <typename T>
class Candidate : public DDLinkedList<T>
{
public:
	int mRepeatCount; //c.count for each candidate
	bool compare(Candidate<T>*); //comparing a candidate in CK with candidates in CT to get c.count
	//bool pruneCheck(DDLinkedList<Candidate<T>*>*); //see if list needs to be pruned out of CK
	Candidate();
	~Candidate();
	bool operator== (Candidate<T>*);
	Candidate(T item);
};

template <typename T>
Candidate<T>::Candidate()
{
	mRepeatCount = 0;
}

template <typename T>
Candidate<T>::Candidate(T item)
{
	insert(item);
	mRepeatCount = 0;
}

//check if sets are equal to eachother - rather than their addresses 
template <typename T>
bool Candidate<T>::operator== (Candidate<T>* other)
{
	for (int i = 0; i < other->getCount(); i++)
	{
		if (other->getData(i) != getData(i))
			return false;
	}

	return true;
}



template <typename T>
bool Candidate<T>::compare(Candidate<T>* candidate)
{
	bool forwardCompare;
	bool forwardCompareAll = true;
	bool compareAll = false;
	for (int i = 0; i < getCount(); i++) // for each in home candidate
	{
		forwardCompare = false;
		for (int c = 0; c < candidate->getCount(); c++) //for each in guest candidate
		{
			if (getData(i) == candidate->getData(c)) //compare home candidate with guest candidate
			{
				forwardCompare = true;//if home candidate is in guest candidate set true and search next home candidate
				break;
			}
		}
		if (!forwardCompare)
		{
			forwardCompareAll = false;
			break;
		}
	}
	if (forwardCompareAll)  //All items in home candidate are in guest candidate but is guest candidate a subset of the home candidate as well?
	{
		compareAll = true;
		bool backwardCompare;
		for (int c = 0; c < candidate->getCount(); c++) //for all in guest candidate
		{
			backwardCompare = false;
			for (int k = 0; k < getCount(); k++) //for all in home candidate
			{
				if (getData(k) == candidate->getData(c)) //compare home candidate to guest candidate
				{
					backwardCompare = true;
					break;
				}
			}
			if (!backwardCompare)
			{
				compareAll = false;
				break;
			}
		}
	}
	return compareAll;  //false if candidate was not found
}

#endif