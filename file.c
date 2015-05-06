#include "main.h"

int delBook()
{
	/* This function is aimed on deleting books
	 * from the database, using their ID
	 */

	char fileName[128];

	FILE* jsonFile = NULL;

	READ("File ID", 129, 's', &fileName)
	
	jsonFile = fopen (fileName,"r"); 

	if ( jsonFile == NULL) //This ID does not exit : do not remove. 
	{
		fclose(jsonFile);
		return 1;
	}

	fclose(jsonFile);
	
	remove(fileName); // https://www.gnu.org/software/libc/manual/html_node/Deleting-Files.html	
	
	return 0;


}

int listBook()
{
	/* This fuction is aimed on listing
	 * books of the database. Their ID
	 * is stored in a file ; then in Book
	 *  variable and endly displayed.
	 */

	char **fileName, *json; // A list of names, and an array wich contents
				// json to parse it.
	int nbFile = 0, i, j, c, d;
	
	FILE* fileList = NULL;      //These variables
	DIR* dir = NULL;            //are used to list 
	struct dirent* file = NULL; // a directory.
	
	Book* bookList;

	fileList = fopen("fileList","w+");

	if(fileList == NULL)
	{
		return 1;
	}

	dir = opendir("."); // Open a directory set in the config file.

	if (dir == NULL)
	{
		return 1;
	}
	
	while ((file = readdir(dir)) != NULL) //list all files of the directory
	{
			fprintf(fileList,"%s\n", file->d_name);
	}			

	closedir(dir);
	
	if( fseek(fileList, 0, SEEK_SET) != 0) //reset the cursor a the top of the file
	{
		return 1;	
	}
	
	d = 0 ;

	do
	{
		// This loop count all file of the directory (Books)
		// except hidden files (configs and attachments)
		
		c = fgetc(fileList);
		
		if(c == '.' && d == 1)
		{
			nbFile--;
			d = 0;
		}

		if(c == '\n')
		{
			d = 1;
			nbFile++;
		}
	}while(c!=EOF);

	
	bookList = malloc(sizeof(Book) * nbFile);

	if(bookList == NULL)
	{
		return 1;
	}
	
	/* This part of the file allocate a 2 dimension array
	 * on this form fileName[NumberOfFiles][256] to stock 
	 * their ID.
	 *  {{BEGIN}} */
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
	/*{{END}}*/ 
	
	if ( fseek(fileList, 0, SEEK_SET) != 0 ) // Return to top
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
	}while(c!=EOF)d
	
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

