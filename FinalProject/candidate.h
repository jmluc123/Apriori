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
};

template <typename T>
bool Candidate<T>::compare(Candidate<T>* candidate)
{
	return new Candidate<T>();
}




#endif