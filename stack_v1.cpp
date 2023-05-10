#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct StackItem
{
	int data;
	StackItem* next;
};

// interface.h
void menu();

// stack.h
static StackItem* firstItem = NULL;

StackItem* create(size_t size);
void push(int content);
int pop();
void clear();

int main()
{
	//StackItem* stack = create(1);
	int opt = -1;

	while(1)
	{
		
	}
}

//interface
void menu()
{
	const char* options[] =
	{
			"0	-	push",
			"1	-	pop",
			"2	-	clear",
			"3	-	exit"
	};

	for (int i = 0; i < 3; i++ )
	{
		printf("%s\n", options[i]);
	}
}

// stack
StackItem* create(size_t size)
{
	StackItem* stack = (StackItem*)malloc(size * sizeof(StackItem));
	if(stack)
	{
		memset(stack, 0, size * sizeof(StackItem));
	}
	return stack;
}

void push(int content)
{
	StackItem* newStackItem = (StackItem*)malloc(sizeof(StackItem));
	if(newStackItem)
	{
		newStackItem->next = firstItem;
		newStackItem->data = content;
		firstItem = newStackItem;
	}
	return;

}

int pop()
{
	StackItem* temp = firstItem->next;
	printf("ITEM POP(): %d \n", firstItem->data);
	free(firstItem);
	firstItem = temp;
	return 1;
}

void clear()
{
	StackItem* temp;
	while(firstItem != NULL)
	{
		temp = firstItem;
		firstItem = firstItem->next;
		free(temp);
	}
}
