#pragma once
#ifndef MY_INTERFACE___H
#define MY_INTERFACE___H

enum MY_INTERF_EN
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_FIND,
	INTERF_STOP,
	INTERF_TOT
};

enum DATA_VAR
{
	DATA_VAR_LASTNAME,
	DATA_VAR_YEAR,
	DATA_VAR_COURSE,
	DATA_VAR_TOT
};
void menu();
void push();
void pop();
void clear();
void find();
void find_lastname();
void find_year();
void find_course();
#endif
