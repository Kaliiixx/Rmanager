typedef struct Book Book ;
typedef struct Common Common ;

struct Common
{
	char title[500];
	char condition;
	char licence[500];
	char place[100];
	char format;
	char description[1000];
	
	char procurement_date[10];
	char release_date[10];
	char language[5];
	
	int number;
};

struct Book
{
	Common common;
	
	char publisher[100];
	char serie[100];

	char genre[10];
	
	int nbTranslator;
	char **translator;

	char version;
	
	int nbAuthor;
	char **author;

	char isbn[17];
	
	int page;
};

