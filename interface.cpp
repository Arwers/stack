#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "stack.h"
#include "interface.h"
#include "errors.h"
#pragma warning (disable : 4996)

const char* strtab[] =
{
	"0 - print",		// INTERF_PRINT
	"1 - push",			// INTERF_PUSH
	"2 - pop",			// INTERF_POP
	"3 - clear",		// INTERF_CLEAR
	"4 - find",			// INTERF_FIND_LASTNAME
	"5 - load",			// INTERF_LOAD
	"6 - save",			// INTERF_SAVE
	"7 - finish"        // INTERF_STOP
};

const char* vartab[] =
{
	"0 - nazwisko",
	"1 - rok urodzenia",
	"2 - kierunek studiow"
};

const char* crstab[] =
{
	"0 - informatyka",
	"1 - matematyka",
	"2 - architektura",
	"3 - budownictwo",
	"4 - transport",
	"5 - energetyka",
	"6 - biotechnologia",
};

void menu()
{
	size_t it;
	for (it = 0; it < INTERF_TOT; ++it)
	{
		printf("%s\n", strtab[it]);
	}
}

void print_stack()
{
	MY_STACK_Print();
}

void push()
{
	char lastname[64];
	int year;
	enum COURSES course;

	printf("Nazwisko: ");
	scanf_s("%s", lastname, sizeof(lastname));

	printf("Rok urodzenia: ");
	if (!scanf_s("%d", &year) || getchar() != '\n' )
	{
		print_error(INVALID_INPUT_ERROR);
		while (getchar() != '\n') {} // czysczenie stdin po blednym wprowadzeniu danych
		return;
	}

	print_courses();
	printf("Kierunek studiow: ");
	if(!scanf_s("%d", &course) || getchar() != '\n')
	{
		print_error(INVALID_INPUT_ERROR);
		while (getchar() != '\n') {}
		return;
	}

	void* pdat = MY_DATA_Push(lastname, year, course);
	if (!MY_STACK_Push(pdat))
		printf("push error\n");
}

void pop()
{
	MY_STACK tmp = MY_STACK_Pop();
	MY_DATA_Print(tmp.pData);
	MY_DATA_Free(tmp.pData);
}

void clear()
{
	MY_STACK_Free();
}

void find()
{
	int op;
	printf("Wybierz kryterium\n");
	for (size_t i = 0; i < DATA_VAR_TOT; ++i) printf("%s\n", vartab[i]);
	printf("Operacja: ");
	scanf_s("%d", &op);
	switch (op) 
	{
	case DATA_VAR_LASTNAME: find_lastname();
		break;
	case DATA_VAR_YEAR: find_year();
		break;
	case DATA_VAR_COURSE: find_course();
		break;
	default: printf("Takie kryterium nie istnieje\n");
	}

	return;
}

void find_lastname()
{
	char str[256];
	printf("Szukane nazwisko: ");
	scanf_s("%s", str, sizeof(str));
	printf("\n");
	MY_STUDENT* searchDat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if(!searchDat)
	{
		print_error(ALLOC_ERROR);
		return;
	}
	memset(searchDat, 0, sizeof(MY_STUDENT));

	size_t size = strlen(str) + 1;
	searchDat->lastname = (char*)malloc(size * sizeof(char));
	if (!searchDat->lastname)
	{
		print_error(ALLOC_ERROR);
	}

	strcpy(searchDat->lastname, str);

	void *pDat = MY_STACK_Search(searchDat, MY_DATA_SearchLastName, 1); //make a first search
	if (pDat)
	{
		printf("Znaleziono: \n");
		MY_DATA_Print(pDat);
		printf("\n");
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchLastName, 0);
		if (pDat)
		{
			printf("Znaleziono: \n");
			MY_DATA_Print(pDat);
			printf("\n");
		}
	}
}

void find_year()
{
	int year;
	printf("Szukany rok urodzenia: ");
	scanf_s("%d", &year);
	printf("\n");
	MY_STUDENT searchDat;
	memset(&searchDat, 0, sizeof(MY_STUDENT));
	searchDat.year = year;

	void *pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchYear, 1); //make a first search

	if (pDat)
	{
		printf("Znaleziono: \n");
		MY_DATA_Print(pDat);
		printf("\n");
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchYear, 0);
		if (pDat)
		{
			printf("Znaleziono: \n");
			MY_DATA_Print(pDat);
			printf("\n");
		}
	}
}

void find_course()
{
	print_courses();
	enum COURSES course;
	printf("Szukany kurs: ");
	scanf_s("%d", &course);
	printf("\n");
	MY_STUDENT searchDat;
	memset(&searchDat, 0, sizeof(MY_STUDENT));
	searchDat.course = course;

	void* pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchCourse, 1); //make a first search

	if (pDat)
	{
		printf("Znaleziono: \n");
		MY_DATA_Print(pDat);
		printf("\n");
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchCourse, 0);
		if (pDat)
		{
			printf("Znaleziono: \n");
			MY_DATA_Print(pDat);
			printf("\n");
		}
	}
}

void print_courses()
{
	printf("Dostepne kierunki studiow: \n");
	for (size_t i = 0; i < COURSES_TOT;++i)
	{
		printf("%s\n", crstab[i]);
	}
}

void load()
{
	MY_STACK_Load();
}
void save()
{
	MY_STACK_Save();
}