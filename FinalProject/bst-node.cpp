/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  header.h
*
*  Description:
*      bst_node_candidate functions
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/

#include "header.h"

/*        Pre:  A BST is most likely initialized
*     Post: a new node is initialized
*  Purpose: create a new node for a BST
***************************************************************/
BST_Node_Candidate::BST_Node_Candidate(int tolerance)
{
	//add your code
	bucket = new CandidateHashTable(tolerance);
	mLeft = NULL;
	mRight = NULL;
}



BST_Node_Candidate::~BST_Node_Candidate()
{
	if (mLeft) delete mLeft;
	if (mRight) delete mRight;
	delete bucket;
}


void BST_Node_Candidate::add(Candidate<int>* candidate, BST_Node_Candidate* node)
{
	bool added;
	if (node == NULL) return;
	if (node->bucket->contains(candidate)) //test if candidate is in the bucket
	{
		return;
	}
	if (node->bucket->isEmpty()) //root node with nothing in it.
	{
		added = node->bucket->add(candidate);
		return;
	}
	added = node->bucket->add(candidate); //Now try to add
	if (!added) //if the bucket is full
	{
		if (candidate->getData(0) < node->bucket->getCandidate(0)->getData(0)) //check left node
		{
			if (node->mLeft)
				add(candidate, node->mLeft);
			else
				node->mLeft = new BST_Node_Candidate(bucket->getSize(), candidate);
		}
		else if (candidate->getData(0) >= node->bucket->getCandidate(0)->getData(0)) //check right node
		{
			if (node->mRight)
				add(candidate, node->mRight);
			else
				node->mRight = new BST_Node_Candidate(bucket->getSize(), candidate);
		}
	}
	return;
}


bool BST_Node_Candidate::isExist(Candidate<int>* candidate, BST_Node_Candidate* node)
{
	bool exists = false;
	if (node == NULL) return false;
	if (bucket->contains(candidate)) return true;
	if (mLeft) exists = isExist(candidate, node->mLeft);
	if (exists) return true;
	if (mRight) exists = isExist(candidate, node->mRight);
	if (exists) return true;
	return false;

}

/*        Pre: a BST is most likely initialized
*     Post: a new node is initialized with a given value
*  Purpose: create a new node with a chosen value for a BST
***************************************************************/
BST_Node_Candidate::BST_Node_Candidate(int tolerance, Candidate<int>* candidate)
{
	//add your code
	bucket = new CandidateHashTable(tolerance, candidate);
	mLeft = NULL;
	mRight = NULL;
}

/*        Pre: a BST is most likely initialized or being initialized and up to 2 BST nodes may be provided
*     Post: a new node is initialized for addition to a BST
*  Purpose: initialize a new node with pre-attached nodes to a BST
*****************************************************************/
BST_Node_Candidate::BST_Node_Candidate(int tolerance, Candidate<int>* candidate, BST_Node_Candidate *left, BST_Node_Candidate *right)
{
	bucket = new CandidateHashTable(tolerance, candidate);
	mLeft = left;
	mRight = right;
}

void BST_Node_Candidate::prune(Transaction<int>* transaction, DDLinkedList<Candidate<int>*>* CT, BST_Node_Candidate* node)
{
	if (node == NULL) return;
	for (int i = 0; i < bucket->getSize(); i++)
	{
		if (bucket->getCandidate(i))
		{
			if (transaction->contains(bucket->getCandidate(i))) CT->insert(bucket->getCandidate(i));
		}
	}
	prune(transaction, CT, node->mLeft);
	prune(transaction, CT, node->mRight);
}

