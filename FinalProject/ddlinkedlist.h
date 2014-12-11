/* ***
*      Changed:  Joshua Lucier
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  ddlinkedList.h
*
*  Description:
*      This is the template doubly linked list definition.
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
protected:
	T* mLinkedList;
	int mCount;
	string mId;

public:
	DDLinkedList(int, string);
	DDLinkedList();
	~DDLinkedList();
	int getCount();
	int getCapactity();
	T getData(int index);
	bool setData(int index, T data);
	void setID(string id);
	void clear();
	void display();
	bool insert(T);
	bool insert(T, int);
	bool isEmpty();
	bool isExist(T searchKey);
	bool remove(T searchKey);
	bool removeAt(int);
	bool ultraKill();
	int insert(int *&structure, int data, int index, int capacity, int count);
};

/*      Pre:  None
*     Post:  This object is initialized using default values
*  Purpose:  To initialize static linked list
*************************************************************************/
template <class T>
DDLinkedList<T>::DDLinkedList()
{
	mLinkedList = NULL;
	mCount = 0;
}

template <class T>
DDLinkedList<T>::DDLinkedList(int id, string sId)
{
	string post = to_string(id);
	mId = "Linked List" + sId + " " + post;
	mLinkedList = NULL;
	mCount = 0;
}

template <class T>
void DDLinkedList<T>::setID(string id)
{
	mId = id;
}
/*      Pre:  Static linked list is initialized
*     Post:  deletes static linked list array
*  Purpose:  clean up before static linked list is deleted
*************************************************************************/
template <class T>
DDLinkedList<T>::~DDLinkedList()
{
	if (mLinkedList) delete[] mLinkedList;
	mLinkedList = NULL;
}

/*      Pre:  Static linked list is initialized
*     Post:  Returns the count of indexes in the data portion of the array
*  Purpose:  get the amount of data values in the array.
*************************************************************************/
template <class T>
int DDLinkedList<T>::getCount()
{
	return mCount;
}

/*      Pre:  linked list is initialized
*     Post:  Gets the value of a specific virtual index in the linked list
*  Purpose:  Get a value from the linked list
*************************************************************************/
template <class T>
T DDLinkedList<T>::getData(int index)
{
	if (index < 0 || index >= mCount)
	{
		cout << "Index out of range";
		return NULL;
	}
	return mLinkedList[index];
}

/*      Pre:  static linked list is initialized
*     Post:  Sets a value in the linked list
*  Purpose:  Sets a value in the linked list based on its virtual index
*************************************************************************
template <class T>
bool DDLinkedList<T>::setData(int index, T data)
{
	if (index > mCapacity - 1)
	{
		cout << "Index out of range";
		return false;
	}
	int trueindex;
	if (mFront + index >= mCapacity) trueindex = mfront + index - mCapacity;
	else trueindex = mfront + index;
	mLinkedList[trueindex] = data;
	return true;
}
*/

/*      Pre:  Static linked list
*     Post:  Destroys the linked list values and gets ready for more
*  Purpose:  Make a new linked list
*************************************************************************/
template <class T>
void DDLinkedList<T>::clear()
{
	delete[] mLinkedList;
	mLinkedList = NULL;
	mCount = 0;
}

/*      Pre:  static linked list is initialized
*     Post:  display values of linked list
*  Purpose:  display the contents of linked list
*************************************************************************/
template <class T>
void DDLinkedList<T>::display()
{
	for (int i = 0; i < mCount; i++)
	{
		cout << mLinkedList[i] << " ";
	}
	cout << endl;
}

/*      Pre:  static linked list is initialized
*     Post:  insert data to the end of a static linked list
*  Purpose:  add data to a linked list
*************************************************************************/
template <class T>
bool DDLinkedList<T>::insert(T data)
{
	if (mCount == 0)
	{
		mLinkedList = new T[1];
		mLinkedList[0] = data;
		mCount++;
		return true;
	}
	else
	{
		T* mLinkedListTmp = new T[mCount + 1];
		for (int i = 0; i < mCount; i++)
		{
			mLinkedListTmp[i] = mLinkedList[i];
		}
		mLinkedListTmp[mCount] = data;
		delete mLinkedList;
		mLinkedList = mLinkedListTmp;
		mCount++;
		return true;
	}
	return false;
}

/*      Pre:  Static linked list is initialized
*     Post:  adds a specific piece of data at a specific virtual index.
*  Purpose:  add data to a static linked list
*************************************************************************
template <class T>
bool DDLinkedList<T>::insert(T data, int index)
{
	if (mCount == 0)
	{
		mLinkedList[mFront] = data;
		mRear = mFront;
		mCount++;
		return true;
	}
	if (index >= mCount)
	{
		cout << "Index out of range";
		return false;
	}
	int trueIndex = mFront + index;
	if (mFront + index >= mCapacity) trueIndex = trueIndex - mCapacity;
	if (mCount == mCapacity)
	{
		return false;
	}
	int i = mRear;
	int stillIndex = trueIndex - 1;
	if (stillIndex == -1) stillIndex = mCapacity - 1;
	while (i != stillIndex)
	{
		mLinkedList[i + 1] = mLinkedList[i];
		i--;
		if (i == -1) i = mCapacity - 1;
	}
	mLinkedList[trueIndex] = data;
	mRear = mRear + 1;
	if (mRear == mCapacity) mRear = 0;
	mCount++;
	return true;
}
*/

/*      Pre:  static linked list is initialized
*     Post:  returns true if the linked list is empty
*  Purpose:  find out if a linked list is empty
*************************************************************************/
template <class T>
bool DDLinkedList<T>::isEmpty()
{
	if (mCount == 0) return true;
	else return false;
}

/*      Pre:  static linked list is initialized
*     Post:  returns true if the data value is found in the linked list
*  Purpose:  test if a value exists
*************************************************************************/
template <class T>
bool DDLinkedList<T>::isExist(T searchKey)
{
	for (int i = 0; i < mCount; i++)
	{
		if (mLinkedList[i] == searchKey) return true;
	}
	return false;
}

/*      Pre:  static linked list is initialized
*     Post:  returns true if a removal of value is successful
*  Purpose:  removes value from linked list
*************************************************************************
template <class T>
bool DDLinkedList<T>::remove(T searchKey)
{
	int index = 0;
	while (index < mCount)
	{
		if (mLinkedList[index] == searchKey) break;
		index++;
	}
	if (index == mCount) return false;
	for (int i = 0; i < mCount; i++)
	{
		mLinkedList[index] = mLinkedList[index + 1];
		index++;
		if (index == mCount) index = 0;
	}
	mCount--;
	mRear--;
	if (mRear == -1) mRear = mCapacity - 1;
	return true;
}
*/
/*      Pre:  static linked list is initialized
*     Post:  returns true if removal was successful
*  Purpose:  removes a value at the provided virtual index
*************************************************************************/
template <class T>
bool DDLinkedList<T>::removeAt(int index)
{
	if (index > mCount || index < 0){
		cout << "index out of range...";
		return false;
	}
	if (mCount == 1)
	{
		mCount--;
		delete mLinkedList;
		mLinkedList = NULL;
		return true;
	}
	T* mLinkedListTmp = new T[mCount - 1];
	for (int i = 0; i < mCount; i++)
	{
		if (i < index)
		{
			mLinkedListTmp[i] = mLinkedList[i];
		}
		else if (i > index)
		{
			mLinkedListTmp[i - 1] = mLinkedList[i];
		}
	}
	delete[] mLinkedList;
	mLinkedList = mLinkedListTmp;
	mCount--;
	return true;
}

template <typename T>
bool DDLinkedList<T>::ultraKill()
{
	for (int i = 0; i < mCount; i++)
	{
		if (mLinkedList[i]) delete mLinkedList[i];
	}
	return true;
}




#endif