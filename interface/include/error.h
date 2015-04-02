#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include<stdbool.h>
//TODO : commenter

typedef const char* String;
typedef void (*err_func)(String);

#define test(cond, func)\
	_test(cond, #cond, __FILE__, __func__, __LINE__, func)

void _test(bool condition, String cond_str, String file, String func, int line, err_func erfunc);

#endif
