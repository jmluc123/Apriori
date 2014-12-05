#include "header.h"


void main()
{
	Database<int>* database = new Database<int>(100, 4); //database with 100 transactions and 4 items per transaction
	database->load();
	//database->apriori();
	delete database;
}