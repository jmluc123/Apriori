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
	//database with 1000 transactions, an average of 4 items per transaction with 1000 distinct items at a confidence of .05
	Database<int>* database = new Database<int>(1000, 4, 1000, 0.05); 
	database->load();
	database->apriori(13);
	delete database;
	
}
