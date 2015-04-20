#include "main.h"

int delBook()
{
	FILE* jsonFile = NULL;
	char fileName[128];
	
	READ("File ID", 129, 's', &fileName)
	
	jsonFile = fopen (fileName,"r"); 

	if ( jsonFile != NULL)
	{
		fclose(jsonFile);
		
		remove(fileName);///https://www.gnu.org/software/libc/manual/html_node/Deleting-Files.html 	
		
		return 0;
	}

	else
	{
		return 1;
	}


}
