#include"error.h"

#include<string.h>
#include"stdio.h"
#include"stdlib.h"

void _test(bool condition, String cond_str, String file, String func, int line, err_func erfunc){
    if(!condition){
        //TODO : verifier que calloc ne plante pas
        char* str = calloc(
                strlen(cond_str)+
                strlen(file)+
                strlen(func)+
                (int)(line%10)+1+
                strlen("[] (line ) : ")+5,
                sizeof(char));
        sprintf(str, "[%s]%s (line %i) : %s", file, func, line, cond_str);
        erfunc(str);
        free(str);
    }
}

