#include "main.h"

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (argv[1] == "add\0" )
		{
			addBook();
		}
	}
	else
	{
		printf("\nrmanager help [COMMAND] -- display help\nrmanager add CATEGORIE-- add an element to the database\nrmanager del FILENUMBER -- delete the element associated to FILENUMBER from the database\nrmanager import FILE CATEGORIE -- import an element to one categorie of the database\nrmanager config -- open the configuration prompt\nrmanager create MODEL -- create a new categorie.\n");

	
	}
	
	return 0;
}

