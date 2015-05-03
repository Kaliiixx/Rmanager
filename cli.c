#include "main.h"

int readcli(char description[], int size, char type, void *pointer)
{
	/** This function print char[] description, i.e. which data the user have to enter, 
	 *  then it return them to the void *pointer, casted before
	 *  depending on char type 
	 **/

	int c = 0 ;

	char *initialPosition = NULL;
	char *string = NULL ;

	string = malloc(sizeof(char)*size);
	
	printf("\n%s: ", description);
	
	if ( fgets(string, size, stdin) != NULL )
	{
		initialPosition = strchr(string, '\n');
		if (initialPosition != NULL)
		{
			*initialPosition = '\0';
		}
		else
		{
			while ( c != '\n' && c != EOF ){c = getchar();}
		}
		
		switch(type)	
		{
			
			case  'c' :
				string[0] = toupper(string[0]); 
				sprintf(pointer, "%c", string[0]);
			break;

			case 's' :
				strcpy(pointer, string); 
			break;
		
			case 'i' :
				if ( strtol(string,NULL, 10) == 0 && string [0] != '0')
				{
					*((int *)pointer) =  -1;
				}	
				
				else
				{
					*((int *)pointer) = strtol(string,NULL, 10); 
				}
				break;
			 
			default :
				printf("Type error");
			break;
		}		
		
		free(string);
		return 1;
	}





	else
	{
		while ( c != '\n' && c != EOF ){c = getchar();}
		free(string);
		return 0;
	}
}
