#include"error.h"

void _test(bool condition, String cond_str, err_func func){
	if(!condition)
		func(cond_str);
}

