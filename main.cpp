#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "interface.h"
#include "data.h"
#include "stack.h"
int main()
{
	MY_STACK_Init(MY_STUDENT_Free);
	int opt = 0;

	size_t op = 0;
	while (op >= INTERF_PUSH && op <= INTERF_STOP)
	{
		menu();
		scanf("%d", &op);

		switch (op)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: //pop();
			break;
		case INTERF_CLEAR: //clear();
			break;
		case INTERF_FIND_LASTNAME: //find_lastname();
			break;
		case INTERF_STOP: //clear();
			return 0;
		default:
			printf("nieuznawany kod operacji\n");
		};
	}

	return 0;
}