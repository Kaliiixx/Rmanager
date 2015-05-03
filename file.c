#include "main.h"

int delBook()
{
	char fileName[128];

	FILE* jsonFile = NULL;

	READ("File ID", 129, 's', &fileName)
	
	jsonFile = fopen (fileName,"r"); 

	if ( jsonFile != NULL)
	{
		fclose(jsonFile);
		
		remove(fileName); // https://www.gnu.org/software/libc/manual/html_node/Deleting-Files.html	
		
		return 0;
	}

	else
	{
		return 1;
	}


}

int listBook()
{
	char **fileName, *json;
	int nbFile = 0, i, j, c;
	
	FILE* fileList = NULL;
	DIR* dir = NULL;
	struct dirent* file = NULL;
	
	Book* bookList;

	fileList = fopen("fileList","w+");

	if(fileList == NULL)
	{
		return 1;
	}

	dir = opendir(".");

	if (dir == NULL)
	{
		return 1;
	}
	
	while ((file = readdir(dir)) != NULL)
	{
			fprintf(fileList,"%s\n", file->d_name);
	}			

	closedir(dir);
	
	if( fseek(fileList, 0, SEEK_SET) != 0)
	{
		return 1;	
	}
	
	do
	{
		c = fgetc(fileList);
		if(c == '\n')
		{
			nbFile++;
		}
	}while(c!=EOF);
	
	bookList = malloc(sizeof(Book) * nbFile);

	if(bookList == NULL)
	{
		return 1;
	}
	
	fileName = malloc(sizeof(char) * nbFile);

	if(fileName == NULL)
	{
		return 1;
	}
	
	for(i=0; i<nbFile; i++)
	{
		fileName[i] = malloc(sizeof(char) * 256);

		if(fileName[i] == NULL)
		{ 
			return 1;	
		}
	}
	
	if ( fseek(fileList, 0, SEEK_SET) != 0 )
	{
		return 1;
	}
	
	i = j = 0;
		
	do
	{
		c = fgetc(fileList);
		if(c == '\n')
		{
			printf("\n%s\n", fileName[i]);
			i++;
			j=0;
		}
		else
		{
			fileName[i][j] = (char)c;
		}
	}while(c!=EOF);
	
	fclose(fileList);


	for(i=0; i<nbFile; i++)
	{
		if(extractJson(fileName[i],&json) != 0)
		{
			return 1;
		}

				
			
	
	}
		
	return 0;
}

