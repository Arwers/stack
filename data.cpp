#include <stdio.h>
#include <iostream>
#include "data.h"
#pragma warning (disable : 4996)

void* MY_STUDENT_Init(char* llastname, int yyear, enum courses ccourse)
/*==========================================================
Alokujemy pamiec dla obiektu MY_STUDENT i wypelniamy dane
===========================================================*/
{
	MY_STUDENT* pdat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (pdat)
	{
		strcpy(pdat->lastname, llastname);
		pdat->course = ccourse;
		pdat->year = yyear;
	}
	return (void*)(pdat);
}

void MY_STUDENT_Free(void* ptr)
/*==========================================================
Zwalniamy pamiec
===========================================================*/
{
	MY_STUDENT* pDat = (MY_STUDENT*)ptr;
	if (pDat)
		free(pDat);
}

void* MY_STUDENT_Push(char* llastname, int yyear, enum courses ccourse)
{
	return MY_STUDENT_Init(llastname, yyear, ccourse);
}

void MY_STUDENT_Print(void* ptr)
{
	MY_STUDENT* p = (MY_STUDENT*)ptr;
	
	if (p)
	{
		printf("nazwisko    : %s\n", p->lastname);
		printf("rok urodzenia : %d\n", p->year);
		printf("kierunek studiów    : %d\n", p->course); // TO DO: get_course_name 
	}
}