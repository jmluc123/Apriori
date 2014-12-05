#include "header.h"


void main()
{
	Database<int>* database = new Database<int>(100, 4, 25, 0.05); //database with 100 transactions and 4 items per transaction
	database->load();
	database->extract();
	//database->apriori();
	delete database;
	
}