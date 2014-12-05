#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

#include "TimerSystem.h"
#include "node.h"
#include "queue.h"
#include "ddlinkedlist.h"
#include "transaction.h"
#include "candidate.h"
#include "bst-node.h"
#include "hash_table.h"
#include "database.h"



int aInsert(int *&structure, int data, int index, int capacity, int count);
int* aDelete(int *&structure, int index, int capacity, int count);
bool isExist(int *&structure, int data, int capacity);
void aDisplay(int *&structure, int count);
void bubbleSort(int list[], int size);
void reverseSort(int list[], int n);

void presentMain();

#endif