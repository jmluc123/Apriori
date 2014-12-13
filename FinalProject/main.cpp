/* ***
*      Changed:  Joshua Lucier & Ryan Moss
*  Last Update:  December 5, 2014
*        Class:  CSI-281
*     Filename:  main.cpp
*
*  Description:
*      main logic of program
*
*  Certification of Authenticity:
*     I certify that changes to this assignment are entirely my own work.
**********************************************************************/

#include "header.h"


void main()
{
	/*
	DDLinkedList<int>* ddlinkedlist = new DDLinkedList<int>;
	for (int i = 0; i < 10; i++)
	{
		ddlinkedlist->insert(i);
	}
	ddlinkedlist->display();
	ddlinkedlist->removeAt(5);
	ddlinkedlist->display();
	system("pause");
	delete ddlinkedlist;
	*/
	//database with 1000 transactions, an average of 4 items per transaction with 1000 distinct items at a confidence of .05
	Database<int>* database = new Database<int>(10000, 10, 1000, 5); 
	database->load();
	database->apriori(5);
	system("pause");
	delete database;
}
