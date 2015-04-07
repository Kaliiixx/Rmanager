#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "frozen.h"
#include "struct.h"
#include "macros.h"
#include "cli.h"

int extractJson(char file[], char **json)
{
	/* The aim of this function is to extract the Json file in 
	 * a characters string in order to read its tokens
	 */
	int fileLength = 0, i = 0, c = 0, quote = 1;
	FILE* jsonFile = NULL;

	jsonFile = fopen(file, "r");
	if ( jsonFile != NULL )
	{		
		for (fileLength=0; (c = fgetc(jsonFile)) != EOF; )
		{
			//do not count only letters, numbers, and punctuation except in the quotes
			
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
	int i = 0;

	Book book;
	
	FILE* jsonFile = NULL;
	
	char fileName[128], tmpString[100];
	
	snprintf(fileName,sizeof(fileName), "%ld", time(NULL));
	
	while( fopen(fileName,"r") != NULL )
	{
		strcat(fileName,"0");

	}
	
	jsonFile = fopen(fileName,"w");

	if( jsonFile != NULL )
	{
		printf("\nTitle : ");
		READ(501,'s',&book.common.title)
		
		printf("\nCondition : ");
		READ(2,'c',&book.common.condition)
		
			printf("\nLicence : ");
		READ(501,'s',&book.common.licence)

		printf("\nPlace : ");
		READ(101,'s',&book.common.place)
		
		printf("\nFormat : ");
		READ(2,'c',&book.common.format)

		printf("\nDescription : ");
		READ(1001,'s',&book.common.description)
		
		printf("\nProcurement date : ");
		READ(11,'s',&book.common.procurement_date)

		printf("\nRelease date : ");
		READ(11,'s',&book.common.release_date)

		printf("\nLanguage: ");
		READ(6,'s',&book.common.language)

		printf("\nnumber : ");
		READ(100,'i',&book.common.number)
		
		printf("\nPublisher : ");
		READ(101,'s',&book.publisher)

		printf("\nSerie : ");
		READ(101,'s',&book.serie)

		printf("\nGenre : ");
		READ(11,'s',&book.genre)

		printf("\nNumber of translators : ");
		READ(2,'i',&book.nbTranslator)
		
		if( book.nbTranslator >= 1)
		{
			*book.translator = malloc(book.nbTranslator * sizeof(char));
			for(i=0; i<book.nbTranslator; i++)
			{
				book.translator[i] = malloc(100 * sizeof(char));		
			}

			for(i=0; i<book.nbTranslator;  i++)
			{
				printf("\nTranslator n. %d : ", i+1);
				READ(101,'s',&tmpString)
				strcpy(book.translator[i], tmpString);
			}

		}

		printf("\nVersion : ");
		READ(2,'c',&book.version)

		printf("\nNumber of authors : ");  
		READ(2,'i',&book.nbAuthor)

		if( book.nbAuthor >= 1)
		{
			*book.author = malloc(book.nbAuthor * sizeof(char));
			for(i=0; i<book.nbAuthor; i++)
			{
				book.author[i] = malloc(100 * sizeof(char));		
			}

			for(i=0; i<book.nbAuthor;  i++)
			{
				printf("\nAuthor n. %d : ", i+1);
				READ(101,'s',&tmpString)
				strcpy(book.author[i], tmpString);
			}

		}
		printf("\nISBN : ");
		READ(18,'s',&book.isbn)

		printf("\nPages : ");
		READ(2,'i',&book.page)

		printf("%s", book.common.title);

		fprintf(jsonFile,"{type: \"BOOK\",{\"publisher\": \"%s\",\"series\": \"%s\",\"pages\": \"%d\",\"authors\":[\"%d\"],\"genre\": \"%s\",\"translator\":\"%d\",\"version\": \"%c\",\"isbn\": \"%s\",},\"common\" :{\"title\": \"%s\",\"condition\" : \"%c\",\"licence\": \"%s\",\"number\": \"%d\",\"procurement_date\":\"%s\",\"place\": \"%s\",\"release_date\": \"%s\",\"format\": \"%c\",\"language\": \"%s\",\"description\":%s}}",book.publisher, book.serie, book.page, book.nbAuthor, book.genre, book.nbTranslator, book.version, book.isbn, book.common.title, book.common.condition,book.common.licence, book.common.number, book.common.procurement_date, book.common.place,book.common.release_date, book.common.format, book.common.language, book.common.description);
			
		fclose(jsonFile);
	}

	return 0;
}


