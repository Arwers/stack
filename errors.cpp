#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "stack.h"

const char* errormess[] =
{
	"E MEMORY ALLOCATION ERROR",
	"W STACK UNDERFLOW",
	"E FATAL ERROR"
};

void print_error(enum ERROR_TYPES error)
{
	puts(errormess[error] + 2);
	if(errormess[error] == "E")
	{
		MY_STACK_free();
		system("pause");
	}
	return;
}