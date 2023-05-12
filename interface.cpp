#include <stdio.h>
#include "data.h"
#include "stack.h"
#include "interface.h"

const char* strtab[] =
{
	"0 - push",			 //INTERF_PUSH
	"1 - pop",			 //INTERF_POP
	"2 - clear",		 //INTERF_CLEAR
	"3 - find lastname", //INTERF_FIND_LASTNAME
	"4 - finish"         //INTERF_STOP
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
	enum courses course;
	printf("nazwisko, rok urodzenia, kierunek\n");
	scanf("%s", lastname);
	scanf("%d", &year);
	scanf("%s", &course);

	void* pdat = MY_STUDENT_Push(lastname, year, course);
	if (!MY_STACK_Push(pdat))
		printf("push error\n");
}