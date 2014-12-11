/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  header.h
*
*  Description:
*      header file for all includes
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <cstddef>
#include <bitset>

using namespace std;

//Various useful functions
int aInsert(int *&structure, int data, int index, int capacity, int count);
int* aDelete(int *&structure, int index, int capacity, int count);
bool isExist(int *&structure, int data, int capacity);
void aDisplay(int *&structure, int count);
void bubbleSort(int list[], int size);
void reverseSort(int list[], int n);
int push(int* myArray, int data, int count);

#include "TimerSystem.h"
#include "node.h"
#include "queue.h"
#include "ddlinkedlist.h"
#include "candidate.h"
#include "candidate_hash_table.h"
#include "transaction.h"
#include "bst-node.h"
#include "hash_table.h"
#include "database.h"

void presentMain();

template <typename T>
string toString(T value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

#endif