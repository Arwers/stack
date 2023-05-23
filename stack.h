#ifndef STACK___H
#define STACK___H

struct MY_STACK
{
	void* pData;    // wskaznik do danych typu void *
	MY_STACK* next; // wskaznik do poprzedniego elementu stosu	
};

typedef void (*FreeData)(void* pdat);                      //Definicja typu: wskaznik do funkcji z prototypem void NazwaFunkcji(void *);
typedef int (CompData)(void* pcurData, void* pSearchData); //Definicja typu: wskaznik do funkcji z prototypem int  NazwaFunkcji(void *, void *);
typedef int (*SaveData)(void* pcurData, FILE* file);
typedef void* (*LoadData)(FILE* file);
typedef void (*PrintData)(void* pdat);

void MY_STACK_Print();
void MY_STACK_Init(FreeData pFreeDat, SaveData pSaveDat, LoadData pLoadDat, PrintData pPrintDat);
MY_STACK* MY_STACK_Push(void* pdat);
MY_STACK MY_STACK_Pop();
void MY_STACK_Free();
void* MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry);
void MY_STACK_Save();
void MY_STACK_Load();
#endif