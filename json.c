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
		scanf("%c", NULL);
		printf("\nCondition : ");
		scanf("%c",&book.common.condition);
		scanf("%c", NULL);

		printf("\nLicence : ");
		scanf("%s",&book.common.licence);
				scanf("%c", NULL);

		printf("\nPlace : ");
		scanf("%s",&book.common.place);
		
		printf("\nFormat : ");
		scanf("%c",&book.common.format);
				scanf("%c", NULL);

		printf("\nTitle : ");
		scanf("%s",&book.common.title);
		
		printf("\nProcurement date : ");
		scanf("%s",&book.common.procurement_date);
				scanf("%c", NULL);

		printf("\nRelease date : ");
		scanf("%s",&book.common.release_date);
		scanf("%c", NULL);

		printf("\nLanguage: ");
		scanf("%s",&book.common.language);
		scanf("%c", NULL);

		printf("\nProcurement date : ");
		scanf("%s",&book.common.procurement_date);
		scanf("%c", NULL);

		printf("\nnumber : ");
		scanf("%d",&book.common.number);
		scanf("%c", NULL);

		printf("\nPublisher : ");
		scanf("%s",&book.publisher);
				scanf("%c", NULL);

		printf("\nSerie : ");
		scanf("%s",&book.serie);
				scanf("%c", NULL);

		printf("\nGenre : ");
		scanf("%s",&book.genre);
		scanf("%c", NULL);

		printf("\nNumber of translators : ");
		scanf("%d",&book.serie);
		scanf("%c", NULL);

		printf("\nTranslators : ");
		scanf("%s",&book.serie);
				scanf("%c", NULL);

		printf("\nVersion : ");
		scanf("%s",&book.version);
		scanf("%c", NULL);

		printf("\nNumber of authors");  
		scanf("%d",&book.nbAuthor);
		scanf("%c", NULL);

		printf("\nAuthors : ");
		scanf("%s",&book.author);
		scanf("%c", NULL);

		printf("\nISBN : ");
		scanf("%s",&book.isbn);
		scanf("%c", NULL);

		printf("\nPages : ");
		scanf("%d",&book.page);
		scanf("%c", NULL);

		fprintf(jsonFile,"{type: \"BOOK\",{\"publisher\": \"%s\",\"series\": \"%s\",\"pages\": \"%d\",\"authors\":[\"%s\"],\"genre\": \"%s\",\"translator\":\"%s\",\"version\": \"%s\",\"isbn\": \"%s\",},\"common\" :{\"title\": \"%s\",\"condition\" : \"%c\",\"licence\": \"%s\",\"number\": \"%d\",\"procurement_date\":\"%s\",\"place\": \"%s\",\"release_date\": \"%s\",\"format\": \"%c\",\"language\": \"%s\",\"decription\":%s}}",book.publisher, book.serie, book.page, book.author, book.genre,book.translator, book.version, book.isbn, book.common.title, book.common.condition,book.common.licence, book.common.number, book.common.procurement_date, book.common.place,book.common.release_date, book.common.format, book.common.language, book.common.description);
			
		fclose(jsonFile);
	}

	return 0;
}


