#include "main.h"

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if( strcmp(argv[1], "add") == 0 )
		{
			addBook();
		}
		
		else if( strcmp(argv[1], "del") == 0 )
		{
			delBook();
		}
		
		else if( strcmp(argv[1], "list") == 0 )
		{
			listBook();
		}

		else if( strcmp(argv[1], "help") == 0 )
		{
		printf("rmanager help [COMMAND] -- display help\nrmanager add CATEGORIE-- add an element to the database\nrmanager del FILENUMBER -- delete the element associated to FILENUMBER from the database\nrmanager import FILE CATEGORIE -- import an element to one categorie of the database\nrmanager config -- open the configuration prompt\nrmanager create MODEL -- create a new categorie.\n");
		}

		else
		{
			printf("%s is not a valid command. Type rmanager help for further informations.\n", argv[1]);
		}

	}
	
	return 0;
}

