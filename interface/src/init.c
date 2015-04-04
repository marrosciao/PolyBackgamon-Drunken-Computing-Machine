#include"init.h"

#include<dlfcn.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

void init_func(void* handle, Functions* func, err_func err)
{
    //A cause de problème de conversion void* <-> pointeur de fonction,
    //les appels à dlsym causent des warnings (avec l'option -pedantic).
    //Ils sont dues à un défaut de conception de dlsym
    func->initLibrary = (pfInitLibrary)dlsym(handle, "InitLibrary");
    test(!dlerror() && func->initLibrary, err);
    func->startMatch  = (pfStartMatch)dlsym(handle, "StartMatch");
    test(!dlerror() && func->startMatch, err);
    func->startGame   = (pfStartGame)dlsym(handle, "StartGame");
    test(!dlerror() && func->startGame, err);
    func->endGame      = (pfEndGame)dlsym(handle, "EndGame");
    test(!dlerror() && func->endGame, err);
    func->endMatch       = (pfEndMatch)dlsym(handle, "EndMatch");
    test(!dlerror() && func->endMatch, err);
    func->doubleStack = (pfDoubleStack)dlsym(handle, "DoubleStack");
    test(!dlerror() && func->doubleStack, err);
    func->takeDouble  = (pfTakeDouble)dlsym(handle, "TakeDouble");
    test(!dlerror() && func->takeDouble, err);
    func->playTurn    = (pfPlayTurn)dlsym(handle, "PlayTurn");
    test(!dlerror() && func->playTurn, err);
}

void init_lib(const char* lib_path, void** handle, Functions* func, err_func err)
{
    printf("path : %s\n", lib_path);
    *handle = dlopen(lib_path, RTLD_NOW);
    test(*handle == NULL, err);
    dlerror();
    init_func(*handle, func, err);
    assert(func->initLibrary);
}

void init_state(SGameState* state)
{
    for(unsigned int i=0; i<24; ++i)
    {
        if(i==12 || i==13 || i==6 || i==19)
        {
            state->board[i].nbDames = 5;
            if(i==12 || 19)         state->board[i].owner = WHITE;
            else if(i==13 || i==6)     state->board[i].owner = BLACK;
        }
        else if(i==8 || i==17)
        {
            state->board[i].nbDames = 3;
            if(i==8) state->board[i].owner = BLACK;
            else      state->board[i].owner = WHITE;
        }
        else if(i==1 || i==24)
        {
            state->board[i].nbDames = 2;
            if(i==1) state->board[i].owner = WHITE;
            else      state->board[i].owner = BLACK;
        }
        else
        {
            state->board[i].owner = NOBODY;
            state->board[i].nbDames = 0;
        }
    }
    for(unsigned int i=0; i<2; ++i)
    {
        state->bar[i] = 0;
        state->out[i] = 0;
    }
    state->stake = 1;
    state->turn = 0;
    state->whiteScore = 0;
    state->blackScore = 0;
}

