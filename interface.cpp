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
	"0 - push",			 //INTERF_PUSH
	"1 - pop",			 //INTERF_POP
	"2 - clear",		 //INTERF_CLEAR
	"3 - find",			 //INTERF_FIND_LASTNAME
	"4 - load",
	"5 - save",
	"6 - finish"         //INTERF_STOP
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

void push()
{
	char lastname[64];
	int year;
	enum COURSES course;

	printf("Nazwisko: ");
	scanf_s("%s", lastname, sizeof(lastname));

	printf("Rok urodzenia: ");
	scanf_s("%d", &year);

	print_courses();
	printf("Kierunek studiow: ");
	scanf_s("%d", &course);

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
	MY_STACK_free();
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
	printf("Szukane nazwisko: \n");
	scanf_s("%s", str, sizeof(str));
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
		printf("Znaleziono : \n");
		MY_DATA_Print(pDat);
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchLastName, 0);
		if (pDat)
		{
			printf("Znaleziono : \n");
			MY_DATA_Print(pDat);
		}
	}
}

void find_year()
{
	int year;
	printf("Szukany rok urodzenia: \n");
	scanf_s("%d", &year);
	MY_STUDENT searchDat;
	memset(&searchDat, 0, sizeof(MY_STUDENT));
	searchDat.year = year;

	void *pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchYear, 1); //make a first search

	if (pDat)
	{
		printf("Znaleziono : \n");
		MY_DATA_Print(pDat);
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchYear, 0);
		if (pDat)
		{
			printf("Znaleziono : \n");
			MY_DATA_Print(pDat);
		}
	}
}

void find_course()
{
	print_courses();
	enum COURSES course;
	printf("Szukany kurs: \n");
	scanf_s("%d", &course);
	MY_STUDENT searchDat;
	memset(&searchDat, 0, sizeof(MY_STUDENT));
	searchDat.course = course;

	void* pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchCourse, 1); //make a first search

	if (pDat)
	{
		printf("Znaleziono : \n");
		MY_DATA_Print(pDat);
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_SearchCourse, 0);
		if (pDat)
		{
			printf("Znaleziono : \n");
			MY_DATA_Print(pDat);
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

void load(){}
void save(){}