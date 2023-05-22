#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "stack.h"

const char* errormess[] =
{
	"E MEMORY ALLOCATION ERROR",
	"W STACK UNDERFLOW",
	"E FATAL ERROR",
	"W INVALID INPUT ERROR"
};

void print_error(enum ERROR_TYPES error)
{
	puts(errormess[error] + 2);
	if(errormess[error] == "E")
	{
		MY_STACK_Free();
		system("pause");
	}
	return;
}

void MyExit(FILE* pft, __int64* fdesc)
{
	if (pft)
		fclose(pft);

	if (fdesc)
		free(fdesc);

	print_error(FATAL_ERROR);
}