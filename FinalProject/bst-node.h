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
using namespace std;

template <typename T>
struct BST_Node
{
	T           mData;
	BST_Node<T> *mLeft, *mRight;

	BST_Node();
	BST_Node(T data);
	BST_Node(T data, BST_Node<T> *left, BST_Node<T> *right);
};

/*        Pre:  A BST is most likely initialized
*     Post: a new node is initialized
*  Purpose: create a new node for a BST
***************************************************************/
template <typename T>
BST_Node<T>::BST_Node()
{
	//add your code
	mData = T();
	mLeft = NULL;
	mRight = NULL;
}


/*        Pre: a BST is most likely initialized
*     Post: a new node is initialized with a given value
*  Purpose: create a new node with a chosen value for a BST
***************************************************************/
template <typename T>
BST_Node<T>::BST_Node(T data)
{
	//add your code
	mData = data;
	mLeft = NULL;
	mRight = NULL;
}

/*        Pre: a BST is most likely initialized or being initialized and up to 2 BST nodes may be provided
*     Post: a new node is initialized for addition to a BST
*  Purpose: initialize a new node with pre-attached nodes to a BST
*****************************************************************/
template <typename T>
BST_Node<T>::BST_Node(T data, BST_Node<T> *left, BST_Node<T> *right)
{
	//add your code
	mData = data;
	mLeft = left;
	mRight = right;
}

#endif