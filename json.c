#include "main.h"

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
		
			if(isalnum(c) ||  ispunct(c) || quote%2 == 0)
	
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
	char tmpString[100];

	READ("Title",501,'s',&book.common.title)
	
	do
	{
		READ("Condition [New - Fine - Very good- Good - fAir - Poor - Ex-library]",2,'c',&book.common.condition)
	}while(book.common.condition != 'N' && book.common.condition != 'F' && book.common.condition != 'V' && book.common.condition != 'G' && book.common.condition != 'A' && book.common.condition != 'P' && book.common.condition != 'E');
	
	READ("License",501,'s',&book.common.license)
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
	READ("Series",101,'s',&book.series)
	READ("Genre",11,'s',&book.genre)
	do {
		READ("Number of translators (≥0)",100,'i',&book.nbTranslator)
	}while(!isdigit(book.nbTranslator) && book.nbTranslator<0 );	
	if( book.nbTranslator >= 1)
	{
		book.translator = malloc(book.nbTranslator * sizeof(char *));
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
			
			printf("\nTranslator n. %d ", i+1);
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
		book.author = malloc(book.nbAuthor * sizeof(char *));
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
			printf("\nAuthor n. %d ", i+1);
			READ("",101,'s',&tmpString)
			strcpy(book.author[i], tmpString);
		}
	}
	READ("ISBN",18,'s',&book.isbn)
	do {
		READ("Pages",100,'i',&book.page)
	}while(!isdigit(book.page) && book.page<0);
	writeJson(book);
	
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

	return 0;
}

int writeJson (Book book)
{
	int i = 0;
	FILE* jsonFile = NULL;
	
	char fileName[128];
	
	snprintf(fileName,sizeof(fileName), "%ld", time(NULL));
	
	while( fopen(fileName,"r") != NULL )
	{
		strcat(fileName,"0");

	}
	
	jsonFile = fopen(fileName,"w");

	if( jsonFile != NULL )
	{
		fprintf(jsonFile,"{");
		
			fprintf(jsonFile,"type: \"BOOK\",");
			fprintf(jsonFile,"{");
				fprintf(jsonFile,"\"publisher\": \"%s\",", book.publisher);
				fprintf(jsonFile,"\"series\": \"%s\",", book.series);
				fprintf(jsonFile,"\"page\": \"%d\",", book.page);
				fprintf(jsonFile,"\"authors\":[");
				
				for(i=0; i< book.nbAuthor; i++)
					
				{
					if(book.author[i] != "\0")
					{	
						fprintf(jsonFile,"\"%s\",", book.author[i]);
				
					}
				}
				
				fprintf(jsonFile,"],");
				fprintf(jsonFile,"\"genre\": \"%s\",", book.genre);
				fprintf(jsonFile,"\"translators\":[");
				
				for(i=0; i< book.nbTranslator; i++)
				{
					if(book.translator[i] != "\0")
					{
						fprintf(jsonFile,"\"%s\",", book.translator[i]);
					}
				}
				
				fprintf(jsonFile,"],");
				fprintf(jsonFile,"\"format\": \"%c\",", book.format);
				fprintf(jsonFile,"\"isbn\": \"%s\",", book.isbn);
			fprintf(jsonFile,"},");
			
			fprintf(jsonFile,"\"common\" :");
			fprintf(jsonFile,"{");
				fprintf(jsonFile,"\"title\": \"%s\",", book.common.title);
				fprintf(jsonFile,"\"condition\" : \"%c\",", book.common.condition);
				fprintf(jsonFile,"\"license\": \"%s\",", book.common.license);
				fprintf(jsonFile,"\"number\": \"%d\",", book.common.number);
				fprintf(jsonFile,"\"procurement_date\":\"%s\",", book.common.procurement_date);
				fprintf(jsonFile,"\"place\": \"%s\",", book.common.place);
				fprintf(jsonFile,"\"release_date\": \"%s\",", book.common.release_date);
				fprintf(jsonFile,"\"Version\": \"%c\",", book.common.version);
				fprintf(jsonFile,"\"language\": \"%s\",", book.common.language);
				fprintf(jsonFile,"\"description\":\"%s\"", book.common.description);
			fprintf(jsonFile,"}");
			
		fprintf(jsonFile,"}");
		
		fclose(jsonFile);
	}
	
	else
	{
			printf("Error");
			return 1;
	}
	
	return 0;
	
}

