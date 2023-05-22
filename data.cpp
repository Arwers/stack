#include <stdio.h>
#include <iostream>
#include "data.h"
#include "errors.h"
#include "interface.h"
#pragma warning (disable : 4996)

void* MY_DATA_Init(char* llastname, int yyear, enum COURSES ccourse)
/*==========================================================
Alokujemy pamiec dla obiektu MY_STUDENT i wypelniamy dane
===========================================================*/
{
	MY_STUDENT* pdat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (!pdat)
	{
		print_error(ALLOC_ERROR);
		return NULL;
	}

	if (pdat)
	{
		size_t size = strlen(llastname) + 1;
		pdat->lastname = (char*)malloc(size * sizeof(char));
		if (!pdat->lastname)
		{
			print_error(ALLOC_ERROR);
			return NULL;
		}

		strcpy_s(pdat->lastname, size, llastname);
		pdat->course = ccourse;
		pdat->year = yyear;
	}

	return (void*)(pdat);
}

void MY_DATA_Free(void* ptr)
/*==========================================================
Zwalniamy pamiec
===========================================================*/
{
	MY_STUDENT* pDat = (MY_STUDENT*)ptr;
	if (pDat) {
		free(pDat->lastname);
		pDat->lastname = NULL;

		free(pDat);
		pDat = NULL;
	}
}

void* MY_DATA_Push(char* llastname, int yyear, enum COURSES ccourse)
{
	return MY_DATA_Init(llastname, yyear, ccourse);
}

void MY_DATA_Print(void* ptr)
{
	MY_STUDENT* p = (MY_STUDENT*)ptr;
	
	if (p)
	{
		printf("Nazwisko: %s\n", p->lastname);
		printf("Rok urodzenia: %d\n", p->year);
		MY_DATA_PrintCourse(p->course);
	}
}

int MY_DATA_SearchLastName(void* pCurData, void* pSearchData)
{
	MY_STUDENT* pcur = (MY_STUDENT*)pCurData;
	MY_STUDENT* psearch = (MY_STUDENT*)pSearchData;

	if (strcmp(pcur->lastname, psearch->lastname) == 0)
		return 1;

	return 0;
}

int MY_DATA_SearchYear(void* pCurData, void* pSearchData)
{
	MY_STUDENT* pcur = (MY_STUDENT*)pCurData;
	MY_STUDENT* psearch = (MY_STUDENT*)pSearchData;

	if (pcur->year == psearch->year)
		return 1;

	return 0;
}

int MY_DATA_SearchCourse(void* pCurData, void* pSearchData)
{
	MY_STUDENT* pcur = (MY_STUDENT*)pCurData;
	MY_STUDENT* psearch = (MY_STUDENT*)pSearchData;

	if(pcur->course == psearch->course)
		return 1;

	return 0;
}

void MY_DATA_PrintCourse(enum COURSES course)
{
	printf("Kierunek studiow: ");
	switch (course) 
	{
	case INFORMATYKA: printf("informatyka\n");
		break;
	case MATEMATYKA: printf("matematyka\n");
		break;
	case ARCHITEKTURA: printf("architektura\n");
		break;
	case BUDOWNICTWO: printf("budownictwo\n");
		break;
	case TRANSPORT: printf("transport\n");
		break;
	case ENERGETYKA: printf("energetyka\n");
		break;
	case BIOTECHNOLOGIA: printf("biotechnologia\n");
		break;
	default: printf("nieznany kierunek\n");
		break;
	}
}