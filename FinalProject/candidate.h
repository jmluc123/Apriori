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
};

template <typename T>
Candidate<T>::Candidate()
{
	mRepeatCount = 0;
}

template <typename T>
Candidate<T>::~Candidate()
{

}

//check if sets are equal to eachother - rather than their addresses 
template <typename T>
bool Candidate<T>::operator== (Candidate<T>* other)
{
	if (this == NULL && other == NULL) return true;
	else if (this == NULL || other == NULL) return false;
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
	bool forwardCompareAll = false;
	bool compareAll = true;
	for (int i = 0; i < getCount(); i++)
	{
		forwardCompare = false;
		for (int c = 0; c < candidate->getCount(); c++)
		{
			if (getData(i) == candidate->getData(c))
			{
				forwardCompare = true;
				break;
			}
		}
		if (!forwardCompare)
		{
			forwardCompareAll = false;
			break;
		}
	}
	if (forwardCompareAll)
	{
		bool backwardCompare;
		for (int i = 0; i < candidate->getCount(); i++)
		{
			backwardCompare = false;
			for (int c = 0; c < getCount(); c++)
			{
				if (getData(c) == candidate->getData(i))
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
	return compareAll;
}

#endif