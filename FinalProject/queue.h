/* ***
*    co-Author:  Joshua Lucier
*  Last Update:  October 31, 2014
*        Class:  CSI-281
*     Filename:  queue.h
*
*  Description:
*      Queue Data structure
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "header.h"

template <typename T>
class Queue {
private:
	Node<T> *mHead, *mTail;
	int     mCount;

public:
	Queue();
	~Queue();

	int  getCount();

	void clear();
	T    dequeue();
	void display();
	void enqueue(T data);
	bool isEmpty();
	bool isExist(T searchKey);
};

/*        Pre: None
*     Post: A queue object is initialized
*  Purpose: to initialize an empty queue object
*********************************************/
template <typename T>
Queue<T>::Queue()
{
	//add your code
	mCount = 0;
	mHead = NULL;
	mTail = NULL;
}

/*        Pre: none
*     Post: returns number of nodes in the queue
*  Purpose: get nodes in the queue
*********************************************/
template <typename T>
int Queue<T>::getCount()
{
	return mCount;
}

/*        Pre: queue has been initialized and may have nodes
*     Post: queue nodes are all deleted
*  Purpose: delete the queue nodes
*********************************************/
template <typename T>
Queue<T>::~Queue()
{
	clear();
}

/*        Pre: queue is initialized and may have nodes
*     Post: queue nodes are deleted
*  Purpose: delete all queue nodes
*********************************************/
template <typename T>
void Queue<T>::clear()
{
	if (mCount == 0) return;
	Node<T> *node = mHead;
	delete mHead;
	mCount--;
	mHead = node;
	node = node->mNext;
	for (int i = 1; i < mCount; i++)
	{
		delete mHead;
		mCount--;
		mHead = node;
		node = node->mNext;
	}
}

/*        Pre: A queue may have 1 or more nodes
*     Post: deletes first node in queue and returns its value
*  Purpose: get the first in the queue
*********************************************/
template <typename T>
T  Queue<T>::dequeue()
{
	T data = mTail->mData;
	Node<T>* pre = mHead;
	for (int i = 0; i < mCount - 2; i++)
	{
		pre = pre->mNext;
	}
	delete mTail;
	mCount--;
	mTail = pre;
	return data;
}

/*        Pre: queue is initialized and a value is passed
*     Post: new node with value passed is added to the back of the queue
*  Purpose: add value to back of the queue
*********************************************/
template <typename T>
void Queue<T>::enqueue(T data)
{
	Node<T>* node = new Node<T>(data);
	node->mNext = mHead;
	mHead = node;
	mCount++;
	if (mCount == 1) mTail = mHead;
}

/*        Pre:  queue exists
*     Post: returns true if there are no nodes
*  Purpose: test to see if the queue is empty
*********************************************/
template <typename T>
bool Queue<T>::isEmpty()
{
	if (mCount > 0) return false;
	return true;
}

/*        Pre: queue is initialized and value is passed
*     Post: returns true if passed value is present in queue
*  Purpose: test to see if a value exists in the queue
*********************************************/
template <typename T>
bool Queue<T>::isExist(T data)
{
	Node<T>* node = mHead;
	for (int i = 1; i < mCount - 1; i++)
	{
		if (node->mData == data) return true;
		node = node->mNext;
	}
	return false;
}

//add other functions here

#endif