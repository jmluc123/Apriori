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
	Candidate(T item, int id, string sId);
	Candidate(int id, string sId);
	int mRepeatCount; //c.count for each candidate
	bool compare(Candidate<T>*); //comparing a candidate in CK with candidates in CT to get c.count
	//bool pruneCheck(DDLinkedList<Candidate<T>*>*); //see if list needs to be pruned out of CK
	Candidate();
	//bool operator== (Candidate<T>*);
	Candidate(T item);
	Candidate<T>* Candidate<T>::intersection(Candidate<T>* candidate);
	Candidate<T>* Candidate<T>::unionize(Candidate<T>* candidate);
	DDLinkedList<Candidate<T>*>* Candidate<T>::subsets();

};

template <typename T>
Candidate<T>::Candidate(int id, string sId)
{
	string post = to_string(id);
	mId = "Candidate" + sId + " " + post;
	mLinkedList = NULL;
	mCount = 0;
	mRepeatCount = 0;
}

template <typename T>
Candidate<T>::Candidate()
{
	mRepeatCount = 0;
	mLinkedList = NULL;
	mCount = 0;
}

template <typename T>
Candidate<T>::Candidate(T item)
{
	mCount = 0;
	mLinkedList = NULL;
	insert(item);
	mRepeatCount = 0;
}


template <typename T>
Candidate<T>::Candidate(T item, int id, string sId)
{
	mCount = 0;
	mLinkedList = NULL;
	insert(item);
	mRepeatCount = 0;
	string post = to_string(id);
	mId = "Candidate" + sId + " " + post;
}
/*
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
*/



template <typename T>
bool Candidate<T>::compare(Candidate<T>* candidate)
{
	int forwardCompare = 0;
	bool compareAll = false;
	for (int i = 0; i < getCount(); i++) // for each in home candidate
	{
		for (int c = 0; c < candidate->getCount(); c++) //for each in guest candidate
		{
			if (getData(i) == candidate->getData(c)) //compare home candidate with guest candidate
			{
				forwardCompare++;//if home candidate is in guest candidate tally and test next home candidate
				break;
			}
		}
	}
	if (forwardCompare == getCount())  //All items in home candidate are in guest candidate but is guest candidate a subset of the home candidate as well?
	{
		int backwardCompare = 0;
		for (int c = 0; c < candidate->getCount(); c++) //for all in guest candidate
		{
			for (int k = 0; k < getCount(); k++) //for all in home candidate
			{
				if (getData(k) == candidate->getData(c)) //compare home candidate to guest candidate
				{
					backwardCompare++;
					break;
				}
			}
		}
		if (candidate->getCount() == backwardCompare) compareAll = true; //forward and backward compare have been successful.  
	}
	return compareAll;  //false if candidate was not found
}


template <typename T>
Candidate<T>* Candidate<T>::unionize(Candidate<T>* candidate)
{
	if (this == NULL) cout << "this == null on unionize";
	if (candidate == NULL) cout << "candidate == null on unionize";
	bool found;
	Candidate<T>* result = new Candidate<T>();
	for (int i = 0; i < getCount(); i++) //add the home candidate
	{
		result->insert(getData(i));
	}
	//add the guest candidate while comparing
	for (int i = 0; i < candidate->getCount(); i++)
	{
		found = false;
		for (int c = 0; c < result->getCount(); c++) //see if candidate i is already in result
		{
			if (result->getData(c) == candidate->getData(i))
			{
				found = true;
				break;
			}
		}
		if (!found) result->insert(candidate->getData(i)); //if it wasn't found
	}
	return result;
}

template <typename T>
Candidate<T>* Candidate<T>::intersection(Candidate<T>* candidate)
{
	if (this == NULL) cout << "this == null on intersection";
	if (candidate == NULL) cout << "candidate == null on intersection";
	Candidate<T>* result = new Candidate < T >();
	for (int i = 0; i < getCount(); i++) //for every item in the home candidate
	{
		for (int c = 0; c < candidate->getCount(); c++)//test if the item is also in guest candidate
		{
			if (candidate->getData(c) == getData(i))
			{
				result->insert(getData(i)); //if there is an intersection add to result and go to next item
				break;
			}
		}
	}
	return result;
}

template <typename T>
DDLinkedList<Candidate<T>*>* Candidate<T>::subsets()
{
	if (this == NULL) cout << "this == null on subsets function";
	typedef bitset<sizeof(int)> intBits;
	DDLinkedList<Candidate<T>*>* subsets = new DDLinkedList<Candidate<T>*>();
	Candidate<T>* subset;
	int k = getCount(); //how many items are in candidate
	int max = pow(2, k); //maximum value for all candidates present
	//create an array of values with a pow of 2 for each index (no empty set so no zero) 2^0 = 1
	T* sequence = new T[k];
	bool found = false;
	for (int i = 0; i < k; i++) sequence[i] = getData(i);
	//get all subsets
	for (int subsetBoolRep = 0; subsetBoolRep < max; subsetBoolRep++)
	{
		//new bitset
		intBits* binary = new intBits(subsetBoolRep);
		//new subset
		subset = new Candidate < T >();
		//load the subset
		for (size_t i = 0; i < k; i++) //test every position in subsetBoolRep
		{
			if (binary->size() > i)
			{
				if (binary->test(i)) subset->insert(sequence[i]);
			}
		}
		//test if subset is in subsets
		found = false;
		for (int i = 0; i < subsets->getCount(); i++)
		{
			if (subsets->getData(i)->compare(subset))
			{
				found = true;
				break;
			}
		}
		//if subset was not found add to subsets
		if (!found && subset->getCount() == k - 1) //if it isn't found and it has a length that is 1 less than current candidate
		{
			subsets->insert(subset);
		}
		else delete subset;
		delete binary;
	}
	delete[] sequence;
	return subsets;
}

#endif