/* ***
*       Author:  Li Jun ZHANG
*      Changed:  Joshua Lucier
*  Last Update:  Sept 12, 2014
*        Class:  CSI-281
*     Filename:  linkedList.h
*
*  Description:
*      This is the template linked list definition.
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/
/* Josh Double Check DDLinkedList of Candidates*/
#ifndef DDLINKEDLIST_H
#define DDLINKEDLIST_H

#include "header.h"

template <typename T>
class DDLinkedList
{
	template <typename T>
	struct Node
	{
		T       mData;
		Node<T> *mNext;
		Node<T> *mPrev;

		/*      Pre:  None
		*     Post:  This object is initialized using default values
		*  Purpose:  To initialize date object
		*************************************************************************/
		Node()
		{
			mData = T();
			mNext = NULL;
			mPrev = NULL;
		}


		/*      Pre:  None
		*     Post:  This object is initialized using specified data
		*  Purpose:  To intialize date object
		*************************************************************************/
		Node(T data)
		{
			mData = data;
			mNext = NULL;
			mPrev = NULL;
		}
	};


private:
	Node<T> *mHead, *mTail;
	int     mCount;

public:
	static int seed[3];
	DDLinkedList();
	~DDLinkedList();
	DDLinkedList(DDLinkedList<T>&);
	int  getCount();
	T getData(int index);
	bool setData(int index, T data);

	void clear();
	void display();
	bool insert(T data);
	bool insert(T data, int index);
	bool isEmpty();
	bool isExist(T searchKey);
	bool remove(T searchKey);
	T    removeAt(int index);

	T operator[](int index);
};

/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list using [] operator
*****************************************************************************/
template <class T>
T DDLinkedList<T>::operator[](int index)
{
	return getData(index);
}

/*      Pre:  None
*     Post:  This object is initialized using the default
*  Purpose:  To initialize date object
*****************************************************************************/
template <class T>
DDLinkedList<T>::DDLinkedList()
{
	mHead = NULL;
	mTail = NULL;
	mCount = 0;
}

/*      Pre:  List is instantiated during a copy
*     Post:  This object is initialized with data from the original list
*  Purpose:  Copy Constructor
*****************************************************************************/
template <class T>
DDLinkedList<T>::DDLinkedList(DDLinkedList<T>& list)
{
	mCount = 0;
	if (list.mCount == 0)
	{
		mHead = NULL;
		mTail = NULL;
		mCount = 0;
	}
	//test for head and tail
	if (list.mCount == 1)
	{
		insert(list[0]);
	}
	else
	{
		for (int i = 0; i < list.mCount; i++)
		{
			insert(list[i]);
		}
	}
}

/*      Pre:  None
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <class T>
DDLinkedList<T>::~DDLinkedList()
{
	clear();
}


/*      Pre:  The object is instantiated
*     Post:  The number of nodes in the linked list is returned to the caller
*  Purpose:  To retrieve the number of nodes in the list
*****************************************************************************/
template <class T>
int DDLinkedList<T>::getCount()
{
	return mCount;
}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list
*****************************************************************************/
template <class T>
T DDLinkedList<T>::getData(int index)
{
	if (index >= mCount){
		cout << "Index out of range...\n";
		system("pause");
	}
	Node<T>* p;
	p = mHead;
	for (int i = 0; i < index; i++)
	{
		p = p->mNext;
	}
	return p->mData;
}

/*      Pre:  The list is instantiated, the index is valid and the data is
*            available
*     Post:  The data in the specified index is updated with the specified
*            data
*  Purpose:  To update the specified nodes in the list
*****************************************************************************/
template <class T>
bool DDLinkedList<T>::setData(int index, T data)
{
	if (index >= mCount || index < 0){
		cout << "Index out of range...\n";
		system("pause");
		system("cls");
		return false;
	}
	Node<T>* p;
	p = mHead;
	for (int i = 0; i < index; i++)
	{
		p = p->mNext;
	}
	p->mData = data;
	return true;
}

/*      Pre:  The list is initiated
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <class T>
void DDLinkedList<T>::clear()
{
	Node<T>* p; //position
	Node<T>* d; //node to delete
	if (mHead == NULL) return;
	p = mHead;
	mHead = NULL;
	mTail = NULL;
	for (int i = 0; i < mCount - 2; i++)
	{
		d = p;
		p = p->mNext;
		delete d;
	}
	delete p;
	mCount = 0;
}



/*      Pre:  The list is instantiated
*     Post:  The entire list is displayed on the screen
*  Purpose:  To show the content of the list
*****************************************************************************/
template <class T>
void DDLinkedList<T>::display()
{
	if (mCount == 0)
	{
		cout << "No items in set..." << "\n";
		return;
	}
	Node<T>* p; //position to display
	p = mHead;
	ostringstream mStream;
	cout << "{ ";
	mStream << p->mData;
	cout << mStream.str();
	if (mCount > 1)
	{
		mStream.str("");
		p = p->mNext;
		for (int i = 1; i < mCount - 1; i++)
		{
			mStream << p->mData;
			cout << ", " << mStream.str();
			mStream.str("");
			p = p->mNext;
		}
		mStream << p->mData;
		cout << ", " << mStream.str();
		mStream.str("");
	}
	cout << " }" << "\n";
}

/*      Pre:  The list is instantiated and the searchKey is available
*     Post:  The function returns true if the search key exists in the list;
*            otherwise false
*  Purpose:  To determine if a specific value exists in the list or not
*****************************************************************************/
template <class T>
bool DDLinkedList<T>::isExist(T searchKey)
{
	Node<T>* p; //position
	p = mHead;
	bool found = false;
	if (mCount == 0) return found;
	if (p->mData == searchKey) found = true;
	for (int i = 1; i < mCount && found == false; i++)
	{
		p = p->mNext;
		if (p->mData == searchKey) found = true;
	}
	return found;
}

/*      Pre:  The list is instantiated and the data is available
*     Post:  The data is inserted in ascending order
*  Purpose:  To insert a data into the list in ascending order.  However, if
*            the data already existed in the list, it will not be added again
*****************************************************************************/
template <class T>
bool DDLinkedList<T>::insert(T data)
{
	if (isExist(data)) return false;
	Node<T>* node = new Node<T>(data);
	if (mCount == 0)
	{
		mHead = node;
		mTail = node;
		node->mNext = NULL;
		node->mPrev = NULL;
		mCount++;
		return true;
	}
	else
	{
		mTail->mNext = node;
		node->mPrev = mTail;
		mTail = node;
		mCount++; //increment
	}
	return true;
}


/*      Pre:  The list is instantiated
*     Post:  The function returns true is the list is empty; false otherwise
*  Purpose:  To determine if the list is empty
*****************************************************************************/
template <class T>
bool DDLinkedList<T>::isEmpty()
{
	if (mCount == 0) return true;
	return false;
}


/*      Pre:  The list is instantiated and the searchKey is available
*     Post:  If the searchKey exists, removes it from the list and the
*            function returns true; otherwise the function does nothing
*            and returns false
*  Purpose:  To remove a specific value from the list
*****************************************************************************/
template <class T>
bool DDLinkedList<T>::remove(T searchKey)
{
	if (!isExist(searchKey)) return false;
	Node<T>* dNode; //node for deleting
	Node<T>* prev; //node previous to node to be deleted
	dNode = mHead;
	if (mCount == 1)
	{
		mHead = NULL;
		mTail = NULL;
		delete dNode;
		dNode = NULL;
		mCount--;
		return true;
	}
	else
	{
		//test for head
		if (dNode->mData == searchKey)
		{
			mHead = dNode->mNext;
			mHead->mPrev = NULL;
			delete dNode;
			dNode = NULL;
			mCount--;
			return true;
		}
		//test for tail
		if (mTail->mData == searchKey)
		{
			dNode = mTail->mPrev;
			delete mTail;
			dNode->mNext = NULL;
			mCount--;
			return true;
		}
		//iterate to find
		int found = false;
		for (int i = 0; i < mCount; i++)
		{
			dNode = dNode->mNext;
			if (dNode->mData == searchKey)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			dNode->mPrev->mNext = dNode->mNext;
			dNode->mNext->mPrev = dNode->mPrev;
			mCount--;
			delete dNode;
		}
		return found;
	}

}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  Remove the element in the specified index location and returns
*            its content to the caller.  If the index location is invalid, the
*            function returns the default value
*  Purpose:  To remove an item in the specified index location
*****************************************************************************/
template <class T>
T DDLinkedList<T>::removeAt(int index)
{
	T value;
	if (index >= mCount || index < 0)
	{
		cout << "Index out of range..." << "\n";
		system("pause");
		return false;
	}
	Node<T>* mNode;
	//test for one node
	if (mCount == 1 && index == 0)
	{
		value = mHead->mData;
		delete mHead;
		mHead = NULL;
		mTail = NULL;
		mCount--;
		return value;
	}
	else if (index == 0)
	{
		value = mHead->mData;
		mNode = mHead;
		mHead = mHead->mNext;
		mHead->mPrev = NULL;
		delete mNode;
		mCount--;
		return value;
	}
	if (index == mCount - 1)
	{
		value = mTail->mData;
		mNode = mTail;
		mTail = mTail->mPrev;
		mTail->mNext = NULL;
		delete mNode;
		mCount--;
		return value;
	}
	mNode = mHead;
	for (int i = 0; i < index; i++)
	{
		mNode = mNode->mNext;
	}
	value = mNode->mData;
	mNode->mPrev->mNext = mNode->mNext;
	mNode->mNext->mPrev = mNode->mPrev;
	delete mNode;
	mCount--;
	return value;
}

template <class T>
bool DDLinkedList<T>::insert(T data, int index)
{

	Node<T>* node = new Node<T>(data);
	Node<T>* prev = mHead;
	if (index > mCount) return false;
	if (index == mCount)
	{
		insert(data);
		return true;
	}
	if (index == 0)
	{
		node->mNext = mHead;
		mHead->mPrev = node;
		mHead = node;
		mCount++;
		return true;
	}
	if (index == 1)
	{
		mHead->mNext->mPrev = node;
		node->mNext = mHead->mNext;
		mHead->mNext = node;
		node->mPrev = mHead;
		mCount++;
		return true;
	}
	if (index == mCount - 1)
	{
		mTail->mPrev->mNext = node;
		node->mPrev = mTail->mPrev;
		mTail->mPrev = node;
		node->mNext = mTail;
		mCount++;
		return true;
	}
	for (int i = 0; i < index - 1; i++)
	{
		prev = prev->mNext;
	}
	node->mNext = prev->mNext;
	node->mPrev = prev;
	node->mNext->mPrev = node;
	prev->mNext = node;
	mCount++;
	return true;
}




#endif