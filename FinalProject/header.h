#include <iostream>

using namespace std;

#include "DDLinkedList.h"



int aInsert(int *&structure, int data, int index, int capacity, int count);
int* aDelete(int *&structure, int index, int capacity, int count);
bool isExist(int *&structure, int data, int capacity);
void aDisplay(int *&structure, int count);
void bubbleSort(int list[], int size);
void reverseSort(int list[], int n);