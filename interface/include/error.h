#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include<stdbool.h>
#include<string.h>

typedef char* String;
typedef void (*err_func)(String);

#define test(cond, func)\
	_test(cond, #cond, func)

void _test(bool condition, String cond_str, err_func func);

#endif
