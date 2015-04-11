typedef struct Book Book ;
typedef struct Common Common ;

struct Common
{
	char title[500]; //String
	char condition; // New, Fine, Very good, Good, Fair, Poor, Ex-librairy.   
	char licence[500];
	char place[100];
	char version;//Digital, Material
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

	char format; //Pocket, Normal
	
	int nbAuthor;
	char **author;

	char isbn[17];
	
	int page;
};

