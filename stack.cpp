#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


static MY_STACK* first = NULL;   // Wskaznik do elementu na szczycie stosu
FreeData ptr_free_dat;           // Deklaracja wskaznika do funkcji typu FreeData

void MY_STACK_Init(FreeData pFreeDat)
{
	first = NULL;
	ptr_free_dat = pFreeDat;
}

MY_STACK* MY_STACK_Push(void* pdat)
{
	// alokujemy pamiec dla nowego elementu kolejki
	MY_STACK* current = (MY_STACK*)malloc(sizeof(MY_STACK));
	if (!current)
		return NULL;

	// jeøeli jest "najnizszym" elementem stosu to do next przypisujemy NULL
	if (!first)
	{
		current->next = NULL;
	}
	else current->next = first;

	//Ustawiamy pData
	current->pData = pdat;
	
	// zamieniamy wskaünik first tak, aby wskazywa≥ "najwyzszy" element stosu
	first = current;

	return current;
}