#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "frozen.h"
#include "struct.h"

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

int addBook()
{
	Book book;
	FILE* jsonFile = NULL;
	char fileName[128], buf[1000];
	
	snprintf(fileName,sizeof(fileName), "%ld", time(NULL));
	
	while( fopen(fileName,"r") != NULL )
	{
		strcat(fileName,"0");

	}
	
	jsonFile = fopen(fileName,"w");

	if( jsonFile != NULL )
	{
		printf("\nTitle : ");
		scanf("%s",&book.common.title);
		
		printf("\nCondition : ");
		scanf("%c",&book.common.condition);

		printf("\nLicence : ");
		scanf("%s",&book.common.licence);
		
		printf("\nPlace : ");
		scanf("%s",&book.common.place);
		
		printf("\nFormat : ");
		scanf("%c",&book.common.format);
		
		printf("\nTitle : ");
		scanf("%s",&book.common.title);
		
		printf("\nProcurement date : ");
		scanf("%s",&book.common.procurement_date);
		
		printf("\nRelease date : ");
		scanf("%s",&book.common.release_date);

		printf("\nLanguage: ");
		scanf("%s",&book.common.language);

		printf("\nProcurement date : ");
		scanf("%s",&book.common.procurement_date);

		printf("\nnumber : ");
		scanf("%d",&book.common.number);

		printf("\nPublisher : ");
		scanf("%s",&book.publisher);
		
		printf("\nSerie : ");
		scanf("%s",&book.serie);
		
		printf("\nGenre : ");
		scanf("%s",&book.genre);

		printf("\nNumber of translators : ");
		scanf("%d",&book.serie);

		printf("\nTranslators : ");
		scanf("%s",&book.serie);
		
		printf("\nVersion : ");
		scanf("%s",&book.version);

		printf("\nNumber of authors");  
		scanf("%d",&book.nbAuthor);

		printf("\nAuthors : ");
		scanf("%s",&book.author);

		printf("\nISBN : ");
		scanf("%s",&book.isbn);

		printf("\nPages : ");
		scanf("%d",&book.page);

		json_emit(buf, sizeof(buf),    }")

		fclose(jsonFile);
	}

	return 0;
}
