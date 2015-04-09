#ifndef _LOGGER_INCLUDED
#define _LOGGER_INCLUDED

#include<stdio.h>
#include<stdbool.h>

#define LOG_LVL INFO

#define LOGGER_SIZE 10
#define logging(name, message, lvl)\
    p_logging(name, __FILE__, __func__, __LINE__, message, lvl)

typedef enum{
    NONE    = 0,
    ERROR   = 1,
    WARNING = 2,
    INFO    = 3
} Level;

typedef struct{
    FILE* file;
    Level lvl;
    const char* name;
    bool simple_print;
} Logger;

//extern Logger _loggers[LOGGER_SIZE];
//extern unsigned int _nb_loggers;

void    init_logger();
Logger* get_logger(const char*);
int     set_level(const char*, Level);
int     set_file(const char*, const char*);
void    set_simple_print(const char*, bool);
int     p_logging(const char*, const char*, const char*, const int, const char*, Level);
void    free_logger();

#endif
