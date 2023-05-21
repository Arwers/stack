#pragma once

#ifndef ERRORS___H
#define ERRORS___H

enum ERROR_TYPES {
	ALLOC_ERROR,
	STACK_UNDERFLOW,
	FATAL_ERROR,
	TOTAL_ERROR
};

void print_error(enum ERROR_TYPES error);

#endif