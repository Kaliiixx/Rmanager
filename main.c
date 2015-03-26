#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frozen.h"
#include "json.h"
#include "struct.h"

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

