#ifndef DATA___H
#define DATA___H

struct MY_STUDENT
{
	char* lastname;      // Nazwisko studenta
	int year;            // Rok urodzenia
	enum COURSES course; // Kierunek studiow
	size_t size;		 // Wielkosc nazwiska
};

enum COURSES {
	INFORMATYKA,
	MATEMATYKA,
	ARCHITEKTURA,
	BUDOWNICTWO,
	TRANSPORT,
	ENERGETYKA,
	BIOTECHNOLOGIA,
	COURSES_TOT
};


void * MY_DATA_Init(char *llastname, int yyear, enum COURSES ccourse);
void MY_DATA_Free(void *ptr);
void * MY_DATA_Push(char *llastname, int yyear, enum COURSES ccourse);
void MY_DATA_Print(void *ptr);
int MY_DATA_SearchLastName(void *pCurData, void *pSearchData);
int MY_DATA_SearchYear(void *pCurData, void *pSearchData);
int MY_DATA_SearchCourse(void *pCurData, void *pSearchData);
void MY_DATA_PrintCourse(enum COURSES course);
int MY_DATA_Save(void* ptr, FILE* file);
void * MY_DATA_Load(FILE* file);
#endif
