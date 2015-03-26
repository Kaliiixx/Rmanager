#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int extractJson(char file[], char **json)
{
	/* The aim of this fonction is to extract the Json file in 
	 * a characters string in order to read its tokens
	 */
	int fileLength = 0, i = 0, c = 0, quote = 1;
	FILE* jsonFile = NULL;

	jsonFile = fopen(file, "r");
	if ( jsonFile != NULL )
	{		
		for (fileLength=0; (c = fgetc(jsonFile)) != EOF; )
		{
			//don’t count only letters, numbers, and punctuation exept in the quotes
			
			if ( c == '"')
			{
				quote ++ ;

			}

			
			if ( isalnum(c) || ispunct(c) ||  quote%2 == 0)
			{
				fileLength++ ;
			}
		}
		
		quote = 1 ;

		//get amount of characters to allocate a right size string
		*json = malloc(fileLength * sizeof(char));
		
		rewind(jsonFile);
		
		
		for(i=0; i< fileLength; i++)
		{
			//write only readable characters		
			c = fgetc(jsonFile);

			if ( c == '"')
			{
				quote++ ;			
			}
		
			if(isalnum(c) || ispunct(c) || quote%2 == 0)
	
			{
		
				(*json)[i] = (char)c;
			}
			
			else
			{
				i--;						
			}
		
		
			
		}
	
	fclose(jsonFile);
	return 1;
	}
	
	else { printf("Error : Could not open the file"); return 0;}
}

