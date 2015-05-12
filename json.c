#include "main.h"

int extractJson(char file[], char **json)
{
	/* The aim of this function is to extract the Json file in 
	 * a characters string in order to read its tokens
	 */
	int fileLength = 0, i = 0, c = 0, quote = 1;
	FILE* jsonFile = NULL;

	jsonFile = fopen(file, "r");
	if ( jsonFile == NULL )
	{		
		return 1;
	}
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
	
	return 0;
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
		fprintf(jsonFile,"{\n");
		
			fprintf(jsonFile,"\t\"type\": \"BOOK\",\n");
			fprintf(jsonFile,"\t{\n");
				fprintf(jsonFile,"\t\t\"publisher\": \"%s\",\n", book.publisher);
				fprintf(jsonFile,"\t\t\"series\": \"%s\",\n", book.series);
				fprintf(jsonFile,"\t\t\"page\": %d,\n", book.page);
				fprintf(jsonFile,"\t\t\"authors\":\n\t\t\t[\n");
				
				for(i=0; i< book.nbAuthor; i++)
					
				{
					if( strcmp(book.author[i], "\0") )
					{	
						fprintf(jsonFile,"\t\t\t\t\"%s\",\n", book.author[i]);
					}

					if( i == (book.nbAuthor-1) )
					{
						fseek(jsonFile, -1, SEEK_CUR);
					}


				}
				fprintf(jsonFile,"\n");
				fseek(jsonFile, -1, SEEK_CUR);
				
				fprintf(jsonFile,"\n\t\t\t],\n");
				fprintf(jsonFile,"\t\t\"genre\": \"%s\",\n", book.genre);
				fprintf(jsonFile,"\t\t\"translators\":\n\t\t\t[\n");
				
				for(i=0; i< book.nbTranslator; i++)
				{
					if( strcmp(book.translator[i], "\0") )
					{
						fprintf(jsonFile,"\t\t\t\t\"%s\",\n", book.translator[i]);
					}
					
					if( i == (book.nbAuthor-1) )
					{
					        fseek(jsonFile, -1, SEEK_CUR);
					}

				}
				fprintf(jsonFile,"\n");
				fseek(jsonFile, -1, SEEK_CUR);
				
				fprintf(jsonFile,"\n\t\t\t],\n");
				fprintf(jsonFile,"\t\t\"format\": \"%c\",\n", book.format);
				fprintf(jsonFile,"\t\t\"isbn\": \"%s\",\n", book.isbn);
			fprintf(jsonFile,"\t},\n\n");
			
			fprintf(jsonFile,"\t\"common\" :\n");
			fprintf(jsonFile,"\t{\n");
				fprintf(jsonFile,"\t\t\"title\": \"%s\",\n", book.common.title);
				fprintf(jsonFile,"\t\t\"condition\" : \"%c\",\n", book.common.condition);
				fprintf(jsonFile,"\t\t\"license\": \"%s\",\n", book.common.license);
				fprintf(jsonFile,"\t\t\"number\": %d,\n", book.common.number);
				fprintf(jsonFile,"\t\t\"procurement_date\":\"%s\",\n", book.common.procurement_date);
				fprintf(jsonFile,"\t\t\"place\": \"%s\",\n", book.common.place);
				fprintf(jsonFile,"\t\t\"release_date\": \"%s\",\n", book.common.release_date);
				fprintf(jsonFile,"\t\t\"Version\": \"%c\",\n", book.common.version);
				fprintf(jsonFile,"\t\t\"language\": \"%s\",\n", book.common.language);
				fprintf(jsonFile,"\t\t\"description\":\"%s\"\n", book.common.description);
			fprintf(jsonFile,"\t}\n");
			
		fprintf(jsonFile,"}\n");
		
		fclose(jsonFile);
	}
	
	else
	{
			printf("Error");
			return 1;
	}
	
	return 0;
	
}

