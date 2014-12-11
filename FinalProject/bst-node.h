/* ***
*    co-Author:  Joshua Lucier
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  bst-node.h
*
*  Description:
*      A node for the BST tree for the hash table object.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef BST_NODE_H
#define BST_NODE_H

#include "header.h"

class BST_Node_Candidate
{
public:
	CandidateHashTable* bucket;
	//Candidate<int>* mCandidate;
	BST_Node_Candidate *mLeft, *mRight;

	BST_Node_Candidate(int tolerance);
	BST_Node_Candidate(int tolerance, Candidate<int>* candidate);
	BST_Node_Candidate(int tolerance, Candidate<int>* candidate, BST_Node_Candidate *left, BST_Node_Candidate *right);
	void add(Candidate<int>* candidate, BST_Node_Candidate* node);
	bool isExist(Candidate<int>* candidate, BST_Node_Candidate* node);
	~BST_Node_Candidate();
	void prune(Transaction<int>*, DDLinkedList<Candidate<int>*>*, BST_Node_Candidate*);
};
#endif