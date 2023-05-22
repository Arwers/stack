#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "errors.h"
#pragma warning (disable : 4996)
static MY_STACK* first = NULL;   // Wskaznik do elementu na szczycie stosu
FreeData ptr_free_dat;           // Deklaracja wskaznika do funkcji typu FreeData
SaveData ptr_save_dat;
LoadData ptr_load_dat;

void MY_STACK_Init(FreeData pFreeDat, SaveData pSaveDat, LoadData pLoadDat)
{
	first = NULL;
	ptr_free_dat = pFreeDat;
	ptr_save_dat = pSaveDat;
	ptr_load_dat = pLoadDat;
}

MY_STACK* MY_STACK_Push(void* pdat)
{
	// alokujemy pamiec dla nowego elementu kolejki
	MY_STACK* current = (MY_STACK*)malloc(sizeof(MY_STACK));
	if (!current)
	{
		print_error(ALLOC_ERROR);
		return NULL;
	}
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
		print_error(STACK_UNDERFLOW);
		rv.pData = NULL;
		rv.next = NULL;
	}
	else
	{
		MY_STACK* next = first->next;
		rv.pData = first->pData;
		free(first);
		first = next;
		printf("Pobrano element\n");
	}
	return rv;
}

void MY_STACK_Free()
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

void MY_STACK_Save()
{
	size_t it;
	// robimy kopie wskaznika, na ktorej bedziemy iterowac
	MY_STACK* temp = first;
	if(!temp)
	{
		print_error(STACK_UNDERFLOW);
		return;
	}
	
	size_t no_items = 0; // ilosc elementow
	while(temp)
	{
		no_items++;
		temp = temp->next;
	}
	temp = first;

	unsigned int no_it = (unsigned int)no_items;
	__int64* file_desc = (__int64*)malloc((no_items + 1) * sizeof(__int64));
	if (!file_desc)
		MyExit(NULL, file_desc);

	FILE* pf = fopen("dane.bin", "wb");
	if (!pf)
		MyExit(pf, file_desc);

	if (fwrite(&no_it, sizeof(unsigned int), 1, pf) != 1)
		MyExit(pf, file_desc);

	//rezerwujemy miejsce w pliku dla file_descr
	_fseeki64(pf, (no_items + 1) * sizeof(__int64), SEEK_CUR);

	for (it = 0; it < no_items; ++it)
	{
		file_desc[it] = ftell(pf);
		if (ptr_save_dat(temp->pData, pf) != 1)
			MyExit(pf, file_desc);
		temp = temp->next;
	}

	file_desc[it] = _ftelli64(pf);
	//zapisujemy wskazniki pozycji dla kazdego recordu
	_fseeki64(pf, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), no_items + 1, pf) != no_items + 1)
		MyExit(pf, file_desc);
	
	if (pf)
		fclose(pf);
	pf = NULL;

	if (file_desc)
		free(file_desc);
	file_desc = NULL;
}

void MY_STACK_Load()
{
	if (first) MY_STACK_Free();
	unsigned int no_items = 0, it, rec;
	__int64* file_desc = NULL;

	FILE* pf = fopen("dane.bin", "rb");
	if (!pf) 
		MyExit(pf, file_desc);

	if (fread(&no_items, sizeof(unsigned int), 1, pf) != 1)
		MyExit(pf, file_desc);

	file_desc = (__int64*)malloc((no_items + 1) * sizeof(__int64));

	if (!file_desc)
		MyExit(pf, file_desc);

	if (fread(file_desc, sizeof(file_desc[0]), no_items + 1, pf) != no_items + 1)
		MyExit(pf, file_desc);

	for (it = 0; it < no_items; ++it)
	{
		rec = no_items - it - 1;  //odczytujemy rekordy w odwrotnej kolejnosci: no_items-1, ... , 0 

		//Odczyt dowolnego recordu rec:
		_fseeki64(pf, file_desc[rec], SEEK_SET);
		void* ptr_data = ptr_load_dat(pf);
		if(!MY_STACK_Push(ptr_data))
			MyExit(pf, file_desc);
	}

	if (file_desc)
		free(file_desc);
	file_desc = NULL;

	if (pf)
		fclose(pf);
	pf = NULL;
}