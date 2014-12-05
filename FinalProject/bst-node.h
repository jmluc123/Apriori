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

class BST_Node_Candidate
{
public:
	Candidate<int>* mCandidate;
	BST_Node_Candidate *mLeft, *mRight;

	BST_Node_Candidate();
	BST_Node_Candidate(Candidate<int>* candidate);
	BST_Node_Candidate(Candidate<int>* candidate, BST_Node_Candidate *left, BST_Node_Candidate *right);
	void add(Candidate<int>* candidate, BST_Node_Candidate* node);
	bool isExist(Candidate<int>* candidate, BST_Node_Candidate* node);
	~BST_Node_Candidate();
	void prune(Transaction<int>*, DDLinkedList<Candidate<int>*>*, BST_Node_Candidate*);
};
#endif