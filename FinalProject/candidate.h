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
	bool pruneCheck(DDLinkedList<Candidate<T>*>*); //see if list needs to be pruned out of CK
	bool isIn(Transaction* transaction); //see if candidate is contained in transaction
};

template <typename T>
bool Candidate<T>::compare(Candidate<T>* candidate)
{
	return false;
}

template <typename T>
bool isIn(Transaction<T>* transaction)
{
	bool isIn;
	bool allAreIn = true;
	for (int i = 0; i < mCount; i++)
	{
		isIn = false;
		for (int c = 0; c < transaction->getCount(); c++)
		{
			if (getData(i) == transaction->getItem(c))
			{
				isIn = true;
				break;
			}
		}
		if (!isIn)
		{
			allAreIn = false;
			break;
		}
	}
	return allAreIn;
}




#endif