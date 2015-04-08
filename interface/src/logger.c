#include"logger.h"

#include<string.h>

static const char* _enumToStr[] = { "ERROR", "WARNING", "INFO"};

void init_logger(){
    for(unsigned int i=0; i<LOGGER_SIZE; ++i){
        _loggers[i].file = NULL;
        _loggers[i].name = NULL;
    }
}

Logger* get_logger(const char* name){
    unsigned int i=0;
    while(i<_nb_loggers && strcmp(name, _loggers[i].name)) ++i;
    if(i>=_nb_loggers){
        if( _nb_loggers>= LOGGER_SIZE ) return NULL;
        _nb_loggers++;
        _loggers[i].file = stderr;
        _loggers[i].lvl  = INFO;
        _loggers[i].name = name;
    }
    return &(_loggers[i]);
}

int set_level(const char* name, Level lvl){
    Logger* tmp = get_logger(name);
    if(!tmp) return 0;
    tmp->lvl = lvl;
    return 1;
}

int set_file(const char* name, const char* file){
    Logger* tmp = get_logger(name);
    if(!tmp) return 0;
    if(!file){
        tmp->file = stderr;
    } else {
        tmp->file = fopen(file, "r");
    }
    return 1;
}

int p_logging(const char* name, const char* file, const char* fctn, const int ligne, const char* message, Level lvl){
    Logger* tmp = get_logger(name);
    if(!tmp) return 0;
    if(lvl<=tmp->lvl) fprintf(tmp->file, "[%15s]:%15s(%4d ) %7s : %s",file, fctn, ligne, _enumToStr[lvl], message);
    return 1;
}

void free_logger(){
    for(unsigned int i=0; i< _nb_loggers; ++i){
        if(_loggers[i].file!=stderr) fclose(_loggers[i].file);
    }
}
