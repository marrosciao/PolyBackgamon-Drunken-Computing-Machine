#include"error.h"

#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void _test(bool condition, String cond_str, String file, String func, int line, err_func erfunc){
    if(!condition){
        char* str = (char*)calloc(
                strlen(cond_str)+
                strlen(file)+
                strlen(func)+
                (int)(line%10)+1+
                strlen("[] (line ) : ")+5,
                sizeof(char));
        if(!str) exit(-1);
        sprintf(str, "[%s]%s (line %i) : %s", file, func, line, cond_str);
        erfunc(str);
        free(str);
    }
}

