#include "main.h"

int delBook()
{
	char fileName[128];
	
	READ("File ID", 129, 's', &fileName)

	if ( fopen (fileName,"r") != NULL )
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
