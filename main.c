#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frozen.h"

int main(int argc, char *argv[])
{
	int fileLength = 0, i = 0;
	FILE* jsonFile = NULL;
	char *json = NULL;

	jsonFile = fopen("livre.json", "r");

	if ( jsonFile != NULL )
	{
		for (fileLength=0; fgetc(jsonFile) != EOF; i++);
		if(
		json = malloc(fileLength * sizeof(char));
		
		printf("%s\n",json);
	
		for(i=0; i<= fileLength; json[i]=fgetc(jsonFile) , i++)
		{
			if (json[i] == '\n' || json[i] == '\t')
			{
				json[i] = ' ';
			}
			printf("%c\n",json[i]);
		}


		// Tokenize json string, fill in tokens array

		//Search for parameter "bar" and print it's value
		// Do not forget to free allocated tokens array
		
	free(json);
	fclose(jsonFile);
	}
	else { printf("Error : Could not open the file"); }

	return 0;
}
