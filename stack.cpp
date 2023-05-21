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
		printf("Stos jest pusty\n");
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

void MY_STACK_free()
{
	//Zwalniamy cala kolejke
	//Ustaliamy wskaznik p do first
	MY_STACK* p = first, * ptmp = NULL;

	//pobieramy po kolejce obiekty
	while (p)
	{
		//Zwalniamy dane dla biezacego elementu kolejki, do ktorego wskazuje wskaznik p
		(*ptr_free_dat)(p->pData);

		//Przypisujemy adres biezacego elementu do pomocniczej zmiennej ptmp
		ptmp = p;

		//przestawiamy wskaznik p do nastepnego elementu kolejki
		p = p->next;

		//zwalniamy biezacy element kolejki
		free(ptmp);
	}

	first = NULL;
}

void * MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry)
{
	static MY_STACK* p;
	MY_STACK* ptmp = NULL;

	if (FirstEntry)
		p = first;

	//pobieramy po kolejce obiekty
	while (p)
	{
		if (!(*ptr_comp_fun)(p->pData, pSearchDat))
		{
			//nie odnaleziono
			//przestawiamy wskaznik p do nastepnego elementu kolejki
			p = p->next;
		}
		else
		{
			//sukcess
			ptmp = p;
			p = p->next;  //reset to the next element of queue
			return ptmp->pData;  //return the data of found element
		}
	}

	return NULL;
}