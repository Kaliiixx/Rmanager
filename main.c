#include <stdio.h>
#include <stdlib.h>
#include "frozen.h"

int main(int argc, char *argv[])
{
	struct json_token *arr, *tok;
	char *json = NULL;
	
	if (extractJson("files/model.json", &json))
	{

		// Tokenize json string, fill in tokens array
		arr = parse_json2(json, strlen(json));

		//Search for parameter "bar" and print it's value
		tok = find_json_token(arr, "type");
		printf("Value of bar is: %.*s\n", tok->len, tok->ptr);

		//Do not forget to free allocated tokens array
		free(arr);
	}
	
	return 0;
}

typedef struct Common Common
struct Common
{
	char *title = NULL;
	char *condition = NULL;
	char *licence = NULL;
	int  number = 0;
	char procurement_date[10] = {};
	char *place = NULL;
	char release_date[10] = {};
	char *format = NULL;
	char language[5] = NULL;
	char *description = NULL;
}


typedef struct Book Book
struct Book
{
	Common common;
	char *publisher = NULL;
	char *serie = NULL;
	int page = 0;
	char *author = NULL;
	char *genre = NULL;
	char *translator = NULL;
	char *version = NULL;
	char isbn[17] = {};
	
}


int extractBook (Book *book, json[])
{




}
