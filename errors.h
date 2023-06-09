#pragma once

#ifndef ERRORS___H
#define ERRORS___H

enum ERROR_TYPES {
	ALLOC_ERROR,
	STACK_UNDERFLOW,
	FATAL_ERROR,
	INVALID_INPUT_ERROR,
	TOTAL_ERROR
};

void print_error(enum ERROR_TYPES error);
void MyExit(FILE* pft, __int64* fdesc);
#endif