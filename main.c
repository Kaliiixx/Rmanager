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
	
	if (extractJson("files/model.json", &json))
	{

		// Tokenize json string, fill in tokens array
		arr = parse_json2(json, strlen(json));

		//Search for parameter "bar" and print it's value
		tok = find_json_token(arr, "type");
		printf("Value of bar is: %.*s\n", tok->len, tok->ptr);

		//Do not forget to free allocated tokens array
		free(arr);
	}
	
	return 0;
}

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

typedef struct Common Common
struct Common
{
	char *title = NULL;
	char *condition = NULL;
	char *licence = NULL;
	int  number = 0;
	char procurement_date[10] = {};
	char *place = NULL;
	char release_date[10] = {};
	char *format = NULL;
	char language[5] = NULL;
	char *description = NULL;
}


typedef struct Book Book
struct Book
{
	Common common;
	char *publisher = NULL;
	char *serie = NULL;
	int page = 0;
	char *author = NULL;
	char *genre = NULL;
	char *translator = NULL;
	char *version = NULL;
	char isbn[17] = {};
	
}


int extractBook (Book *book, json[])
{




}
