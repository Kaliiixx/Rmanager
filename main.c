#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "frozen.h"

int extractJson(char file[], char **json);


int main(int argc, char *argv[])
{
	struct json_token *arr, *tok;
	char *json = NULL;
	
	if (extractJson("model.json", &json))
	{

		// Tokenize json string, fill in tokens array
		arr = parse_json2(json, strlen(json));

		//Search for parameter "bar" and print it's value
		tok = find_json_token(arr, "key_1");
		printf("Value of bar is: [%.*s]\n", tok->len, tok->ptr);

		//Do not forget to free allocated tokens array
		free(arr);
		free(json);
	}
	
	return 0;
}

int extractJson(char file[], char **json)
{
	/* The aim of this fonction is to extract the Json file in 
	 * a characters string in order to read its tokens
	 */
	int fileLength = 0, i = 0, c=0;
	FILE* jsonFile = NULL;

	jsonFile = fopen(file, "r");
	if ( jsonFile != NULL )
	{		
		for (fileLength=0; fgetc(jsonFile) != EOF; fileLength++);
		//get amount of characters to allocate a right size string
		*json = malloc(fileLength * sizeof(char));
		
		rewind(jsonFile);
		
		
		for(i=0; i< fileLength; i++)
		{
			//write only readable characters		
			c = fgetc(jsonFile);
		
			if( isalnum(c) || ispunct(c))
	
			{
		
				(*json)[i] = (char)c;
		
			}
			else
			{
				(*json)[i]= ' ';						
			}
		
		
			
		}
	
	fclose(jsonFile);
	return 1;
	}
	
	else { printf("Error : Could not open the file"); return 0;}
}

