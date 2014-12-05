/* ***
*    co-Author:  Joshua Lucier
*  Last Update:  October 31, 2014
*        Class:  CSI-281
*     Filename:  bst-node.h
*
*  Description:
*      A node for the BST object.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef BST_NODE_H
#define BST_NODE_H

#include "header.h"

struct BST_Node_Candidate
{
	Candidate<int>* mCandidate;
	BST_Node_Candidate *mLeft, *mRight;

	BST_Node_Candidate();
	BST_Node_Candidate(Candidate<int>* candidate);
	BST_Node_Candidate(Candidate<int>* candidate, BST_Node_Candidate *left, BST_Node_Candidate *right);
	void add(Candidate<int>* candidate);
	bool isExist(Candidate<int>* candidate);
	~BST_Node_Candidate();
	void prune(Transaction<int>*, DDLinkedList<Candidate<int>*>*, BST_Node_Candidate*);
};


BST_Node_Candidate::~BST_Node_Candidate()
{

}

void BST_Node_Candidate::add(Candidate<int>* candidate)
{
	if (candidate->getData(0) < mCandidate->getData(0))
	{
		if (mLeft)
			mLeft->add(candidate);
		else
			mLeft = new BST_Node_Candidate(candidate);
	}
	else if (candidate->getData(0) >= mCandidate->getData(0))
	{
		if (candidate->compare(mCandidate))
		{
			return;
		}
		if (mRight)
			mRight->add(candidate);
		else
			mRight = new BST_Node_Candidate(candidate);
	}
}


bool BST_Node_Candidate::isExist(Candidate<int>* candidate)
{
	bool exists = false;
	exists = mLeft->isExist(candidate);
	if (exists) return true;
	exists = mRight->isExist(candidate);
	if (exists) return true;
	return false;

}
/*        Pre:  A BST is most likely initialized
*     Post: a new node is initialized
*  Purpose: create a new node for a BST
***************************************************************/
BST_Node_Candidate::BST_Node_Candidate()
{
	//add your code
	mCandidate* = new Candidate<int>();
	mLeft = NULL;
	mRight = NULL;
}


/*        Pre: a BST is most likely initialized
*     Post: a new node is initialized with a given value
*  Purpose: create a new node with a chosen value for a BST
***************************************************************/
BST_Node_Candidate::BST_Node_Candidate(Candidate<int>* candidate)
{
	//add your code
	mCandidate = candidate;
	mLeft = NULL;
	mRight = NULL;
}

/*        Pre: a BST is most likely initialized or being initialized and up to 2 BST nodes may be provided
*     Post: a new node is initialized for addition to a BST
*  Purpose: initialize a new node with pre-attached nodes to a BST
*****************************************************************/
template <typename T>
BST_Node_Candidate::BST_Node_Candidate(Candidate<int>* candidate, BST_Node_Candidate *left, BST_Node_Candidate *right)
{
	//add your code
	mCandidate = candidate;
	mLeft = left;
	mRight = right;
}

void prune(Transaction<int>* transaction, DDLinkedList<Candidate<int>*>* CT, BST_Node_Candidate* node)
{
	if (node->mCandidate->isIn(transaction)) CT->insert(node->mCandidate);
	prune(transaction, CT, node->mLeft);
	prune(transaction, CT, node->mRight);
}

#endif