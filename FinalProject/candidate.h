#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "header.h"

template <typename T>
class Candidate : public DDLinkedList<T>
{
public:
	int mRepeatCount; //c.count for each candidate
	bool compare(Candidate<T>*); //not sure
	bool pruneCheck(DDLinkedList<Candidate<T>*>*); //see if list needs to be pruned out of C[4]
};






#endif