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
BST_Node_Candidate::BST_Node_Candidate()
{
	//add your code
	mCandidate = NULL;
	mLeft = NULL;
	mRight = NULL;
}



BST_Node_Candidate::~BST_Node_Candidate()
{

}


void BST_Node_Candidate::add(Candidate<int>* candidate, BST_Node_Candidate* node)
{
	if (node == NULL) return;
	if (node->mCandidate == NULL) //root node with nothing in it.
	{
		node->mCandidate = candidate;
		return;
	}
	if (candidate->getData(0) < node->mCandidate->getData(0))
	{
		if (node->mLeft)
			add(candidate, node->mLeft);
		else
			node->mLeft = new BST_Node_Candidate(candidate);
	}
	else if (candidate->getData(0) >= node->mCandidate->getData(0))
	{
		if (candidate->compare(node->mCandidate)) //test if candidate is same as 
		{
			return;
		}
		if (node->mRight)
			add(candidate,node->mRight);
		else
			node->mRight = new BST_Node_Candidate(candidate);
	}
	return;
}


bool BST_Node_Candidate::isExist(Candidate<int>* candidate, BST_Node_Candidate* node)
{
	bool exists = false;
	if (node == NULL) return false;
	if (candidate->compare(mCandidate)) return true;
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
BST_Node_Candidate::BST_Node_Candidate(Candidate<int>* candidate, BST_Node_Candidate *left, BST_Node_Candidate *right)
{
	mCandidate = candidate;
	mLeft = left;
	mRight = right;
}

void BST_Node_Candidate::prune(Transaction<int>* transaction, DDLinkedList<Candidate<int>*>* CT, BST_Node_Candidate* node)
{
	if (node == NULL) return;
	if (transaction->contains(node->mCandidate)) CT->insert(node->mCandidate);
	prune(transaction, CT, node->mLeft);
	prune(transaction, CT, node->mRight);
}

