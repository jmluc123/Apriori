
#include "header.h"


void main()
{
	Database<int>* database = new Database<int>(1000, 4, 25, 0.05); //database with 1000 transactions and 4 items per transaction
	database->load();
	database->apriori(13);
	delete database;
	
}
