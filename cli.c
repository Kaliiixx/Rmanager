#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int readcli(int size, char type, void *pointer)
{
	int c = 0, i = 0;

	char *initialPosition = NULL;
	char *string = NULL ;

	string = malloc(sizeof(char)*size);
	
	
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
		
		switch(size)
		{
			case  'c' :
				*pointer = (char)(((int)'0')+string[0]);
			break;

			case 's' :
				for(i=0; i<size; i++)
				{
					pointer[i] = string[i];
				}
			break;

			case 'i' :
				*pointer = string[0];
			break;
			 
			default :
				printf("Type error");
			break;
		}		
		
		return 1;
	}





	else
	{
		while ( c != '\n' && c != EOF ){c = getchar();}
		return 0;
	}
}
