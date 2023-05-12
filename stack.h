#ifndef MY_STACK___H
#define MY_STACK___H

struct MY_STACK
{
	void* pData;    // wskaznik do danych typu void *
	MY_STACK* next; // wskaznik do poprzedniego elementu stosu	
};

typedef void (*FreeData)(void* pdat);                      //Definicja typu: wskaznik do funkcji z prototypem void NazwaFunkcji(void *);
typedef int (CompData)(void* pcurData, void* pSearchData); //Definicja typu: wskaznik do funkcji z prototypem int  NazwaFunkcji(void *, void *);

void MY_STACK_Init(FreeData pFreeDat);
MY_STACK* MY_STACK_Push(void* pdat);
#endif