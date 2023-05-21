#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#pragma warning (disable : 4996)

int main()
{
	MY_STACK_Init(MY_DATA_Free);
	int op = 0;
	while (op >= INTERF_PUSH && op <= INTERF_STOP)
	{
		menu();
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
		case INTERF_LOAD: //load();
			break;
		case INTERF_SAVE: //save();
			return 0;
		default:
			printf("nieuznawany kod operacji\n");
		};
	}

	return 0;
}