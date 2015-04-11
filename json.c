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
		READ("Title",501,'s',&book.common.title)
		
		do
		{
			READ("Condition [New - Fine - Very good- Good - fAir - Poor - Ex-librairy]",2,'c',&book.common.condition)
		}while(book.common.condition != 'N' && book.common.condition != 'F' && book.common.condition != 'V' && book.common.condition != 'G' && book.common.condition != 'A' && book.common.condition != 'P' && book.common.condition != 'E');
		
		READ("Licence",501,'s',&book.common.licence)

		READ("Place",101,'s',&book.common.place)
		
		do
		{
			READ("Format [Pocket - Normal]",2,'c',&book.format)
		}while(book.format != 'P' && book.format !='N');
		
		READ("Description",1001,'s',&book.common.description)
		
		READ("Procurement date",11,'s',&book.common.procurement_date)

		READ("Release date",11,'s',&book.common.release_date)

		READ("Language",6,'s',&book.common.language)

		do {
			READ("Number (≥0)",100,'i',&book.common.number)
		}while(!isdigit(book.common.number) && book.common.number<0 );
	
		READ("Publisher",101,'s',&book.publisher)

		READ("Serie",101,'s',&book.serie)

		READ("Genre",11,'s',&book.genre)

		do {
			READ("Number of translators (≥0)",100,'i',&book.nbTranslator)
		}while(!isdigit(book.nbTranslator) && book.nbTranslator<0 );	
		if( book.nbTranslator >= 1)
		{
			*book.translator = malloc(book.nbTranslator * sizeof(char));
			for(i=0; i<book.nbTranslator; i++)
			{
				book.translator[i] = malloc(100 * sizeof(char));		
			}

			for(i=0; i<book.nbTranslator;  i++)
			{
				/** See this case 
				 * to make it compatible
				 * with readgui
				 **/
				
				printf("\nTranslator n. %d : ", i+1);
				READ("",101,'s',&tmpString)
				strcpy(book.translator[i], tmpString);
			}
			
			for(i=0; i<100; i++)
			{
				tmpString[i] = 0;
			}
		}
		
		do {
			READ("Version [Digital - Material]",2,'c',&book.common.version)
		}while(book.common.version != 'D' && book.common.version != 'M');

		do {
			READ("Number of authors (≥0):",100,'i',&book.nbAuthor)
		}while(!isdigit(book.nbAuthor) && book.nbAuthor<0 );

		if( book.nbAuthor >= 1)
		{
			*book.author = malloc(book.nbAuthor * sizeof(char));
			for(i=0; i<book.nbAuthor; i++)
			{
				book.author[i] = malloc(100 * sizeof(char));		
			}

			for(i=0; i<book.nbAuthor;  i++)
			{
				/** See this case 
				 * to make it compatible
				 * with readgui
				 **/
				printf("\nAuthor n. %d : ", i+1);
				READ("",101,'s',&tmpString)
				strcpy(book.author[i], tmpString);
			}

		}
		READ("ISBN",18,'s',&book.isbn)

		do {
			READ("Pages",100,'i',&book.page)
		}while(!isdigit(book.page) && book.page<=0);

		fprintf(jsonFile,"{type: \"BOOK\",{\"publisher\": \"%s\",\"series\": \"%s\",\"pages\": \"%d\",\"authors\":[\"%d\"],\"genre\": \"%s\",\"translator\":\"%d\",\"version\": \"%c\",\"isbn\": \"%s\",},\"common\" :{\"title\": \"%s\",\"condition\" : \"%c\",\"licence\": \"%s\",\"number\": \"%d\",\"procurement_date\":\"%s\",\"place\": \"%s\",\"release_date\": \"%s\",\"format\": \"%c\",\"language\": \"%s\",\"description\":%s}}",book.publisher, book.serie, book.page, book.nbAuthor, book.genre, book.nbTranslator, book.common.version, book.isbn, book.common.title, book.common.condition,book.common.licence, book.common.number, book.common.procurement_date, book.common.place,book.common.release_date, book.format, book.common.language, book.common.description);
		
		if( book.nbTranslator >= 1)
		{
			for(i=0; i<book.nbTranslator; i++)
			{
				free(book.translator[i]);		
			}
			free(book.translator);
		}			
		
		if( book.nbAuthor >= 1)
		{
			for(i=0; i<book.nbAuthor; i++)
			{
				free(book.author[i]);		
			}
			free(book.author);
		}

		fclose(jsonFile);
	}

	return 0;
}


