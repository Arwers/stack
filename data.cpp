#include <stdio.h>
#include <iostream>
#include "data.h"

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