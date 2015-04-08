#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int readcli(int size, char type, void *pointer)
{
	int c = 0, number=0;

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
		
		switch(type)	
		{
			
			case  'c' :
				sprintf(pointer, "%c", string[0]);
			break;

			case 's' :
				strcpy(pointer, string); 
			break;
		
			case 'i' :
				number = strtol(string,NULL, 10);
				*((int *)pointer) = number;	
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
