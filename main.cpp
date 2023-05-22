#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#pragma warning (disable : 4996)

int main()
{
	MY_STACK_Init(MY_DATA_Free, MY_DATA_Save, MY_DATA_Load);
	int op = 0;
	while (op >= INTERF_PUSH && op <= INTERF_STOP)
	{
		menu();
		printf("Operacja: ");
		scanf_s("%d", &op);

		switch (op)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTERF_CLEAR: clear();
			break;
		case INTERF_FIND: find();
			break;
		case INTERF_STOP: clear();
			return 0;
		case INTERF_LOAD: load();
			break;
		case INTERF_SAVE: save();
			break;
		default:
			printf("nieuznawany kod operacji\n");
		};
		printf("\n");
	}

	return 0;
}