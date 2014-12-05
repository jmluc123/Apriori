#include "header.h"

void aDisplay(int *&structure, int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << structure[i] << ", ";
	}
}
/*      Pre:  array is initialized and information about the list size and data count is provided
*     Post:  returns the number of items in the list
*  Purpose:  Inserts the provided data at the provided index.
*************************************************************************/
int aInsert(int *&structure, int data, int index, int capacity, int count)
{
	if (count == capacity) return capacity;
	for (int i = count; i > index; i--)
	{
		structure[i] = structure[i - 1];
	}
	structure[index] = data;
	count++;
	return count;
}

/*      Pre:  array is initialized and information about the list size and data count is provided
*     Post:  returns a new array with the provided index removed
*  Purpose:  removes a avalue from the array
*************************************************************************/
int* aDelete(int *&structure, int index, int capacity, int count)
{
	int* newStructure = new int[capacity];
	int c = 0;
	for (int i = 0; i < count; i++)
	{
		if (i == index) continue;
		newStructure[c] = structure[i];
		c++;
	}
	delete structure;
	return newStructure;
}

/*      Pre:  array is initialized and information about the list size is provided
*     Post:  returns true if the data is found
*  Purpose:  Search for a data value to see if it exists.
*************************************************************************/
bool isExist(int *&structure, int data, int capacity)
{
	for (int i = 0; i < capacity; i++)
	{
		if (structure[i] == data) return true;
	}
	return false;
}


/*
Pre: An array is declared and passed by reference to the function
Post: The array is sorted for usage outside of the function.  Nothing returned.
Purpose:  Sort an array based on binary comparisons using the bubble sort method.
*/
void bubbleSort(int list[], int size)
{
	int temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

/*      Pre:  A sorted list is passed by reference to the function with its size.
*     Post:  Sorts the list in reverse order.
*  Purpose:  Reverses the order of a sorted list.
*************************************************************************/
void reverseSort(int list[], int n)
{
	int tmp;
	for (int i = 0; i < n / 2; i++)
	{
		tmp = list[0];
		list[0] = list[n - i - 1];
		list[n - i - 1] = tmp;
	}
}
