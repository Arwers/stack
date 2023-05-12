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

	// je¿eli jest "najnizszym" elementem stosu to do next przypisujemy NULL
	if (!first)
	{
		current->next = NULL;
	}
	else current->next = first;

	//Ustawiamy pData
	current->pData = pdat;
	
	// zamieniamy wskaŸnik first tak, aby wskazywa³ "najwyzszy" element stosu
	first = current;

	return current;
}

MY_STACK MY_STACK_Pop() 
{
	MY_STACK rv;
	if(!first)
	{
		printf("Stos jest pusty");
		rv.pData = NULL;
		rv.next = NULL;
	}
	else
	{
		MY_STACK* next = first->next;
		rv.pData = first->pData;
		free(first);
		first = next;
	}
	return rv;
}