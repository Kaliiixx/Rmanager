typedef struct Book Book ;
typedef struct Common Common ;

struct Common
{
	char *title;
	char *condition;
	char *licence;
	char *place;
	char *format;
	char *description;
	
	char procurement_date[10];
	char release_date[10];
	char language[5];
	
	int  number;
};

struct Book
{
	Common common;
	
	char *publisher;
	char *serie;
	char *author;
	char *genre;
	char *translator;
	char *version;
	
	char isbn[17];
	
	int page;
};

