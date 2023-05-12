#ifndef MY_STUDENT_ADFGRETW__H
#define MY_STUDENT_ADFGRETW__H

struct MY_STUDENT
{
	char lastname[64];    // Nazwisko studenta
	int year;            // Rok urodzenia
	enum courses course; // Kierunek studiow
};

enum courses {
	informatyka,
	matematyka,
	architektura,
	budownictwo
};

void* MY_STUDENT_Init(char* llastname, int yyear, enum courses ccourse);
void MY_STUDENT_Free(void* ptr);
void* MY_STUDENT_Push(char* llastname, int yyear, enum courses ccourse);
void MY_STUDENT_Print(void* ptr);
#endif
