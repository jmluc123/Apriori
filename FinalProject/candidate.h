#include "header.h"


#ifndef CANDIDATE_H
#define CANDIDATE_H

template <typename T>
class Candidate : public DDLinkedList<T>
{
public:
	int mRepeatCount;
	bool compare(Candidate<T>);
	bool pruneCheck(DDLinkedList<Candidate<T>>);
};






#endif