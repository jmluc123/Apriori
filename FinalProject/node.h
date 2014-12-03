/* ***
*    co-Author:  Joshua Lucier
*  Last Update:  October 31, 2014
*        Class:  CSI-281
*     Filename:  node.h
*
*  Description:
*      Typical Linked List node for queue or stack objects.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef NODE_H
#define NODE_H

#include "header.h"

/*        Pre: A queue is most likely initialized or being initialized
*     Post: a new node is created for enqueuing
*  Purpose: initialize a new node for enqueuing
*********************************************/
template <typename T>
struct Node
{
	T       mData;
	Node<T> *mNext;

	Node();
	Node(T data);
};

/*        Pre: A queue is most likely initialized or being initialized
*     Post: a new node is created for enqueuing
*  Purpose: initialize a new node for enqueuing
*********************************************/
template <typename T>
Node<T>::Node()
{
	mData = T();
	mNext = NULL;
	//add your code
}

/*        Pre: A queue is most likely initialized or being initialized
*     Post: a new node is created for enqueuing
*  Purpose: initialize a new node for enqueuing
*********************************************/
template <typename T>
Node<T>::Node(T data)
{
	//add your code
	mData = data;
	mNext = NULL;
}

#endif