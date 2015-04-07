#include"init.h"

#include<dlfcn.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include <string.h>

void init_func(void* handle, Functions* func, err_func err)
{
    //A cause de problème de conversion void* <-> pointeur de fonction,
    //les appels à dlsym causent des warnings (avec l'option -pedantic).
    //Ils sont dues à un défaut de conception de dlsym
    func->initLibrary = (pfInitLibrary)dlsym(handle, "InitLibrary");
    test(!dlerror()   && func->initLibrary, err);
    func->startMatch  = (pfStartMatch)dlsym(handle, "StartMatch");
    test(!dlerror()   && func->startMatch, err);
    func->startGame   = (pfStartGame)dlsym(handle, "StartGame");
    test(!dlerror()   && func->startGame, err);
    func->endGame     = (pfEndGame)dlsym(handle, "EndGame");
    test(!dlerror()   && func->endGame, err);
    func->endMatch    = (pfEndMatch)dlsym(handle, "EndMatch");
    test(!dlerror()   && func->endMatch, err);
    func->doubleStack = (pfDoubleStack)dlsym(handle, "DoubleStack");
    test(!dlerror()   && func->doubleStack, err);
    func->takeDouble  = (pfTakeDouble)dlsym(handle, "TakeDouble");
    test(!dlerror()   && func->takeDouble, err);
    func->playTurn    = (pfPlayTurn)dlsym(handle, "PlayTurn");
    test(!dlerror()   && func->playTurn, err);
}

void init_lib(const char* lib_path, void** handle, Functions* func, err_func err)
{
    *handle = dlopen(lib_path, RTLD_NOW);
    test(*handle != NULL, err);
    dlerror();
    init_func(*handle, func, err);
}

void init_board(SGameState* state)
{
    Square board[24] = {
        {.owner = WHITE, .nbDames = 2},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = BLACK, .nbDames = 5},
        {.owner = NOBODY},
        {.owner = BLACK, .nbDames = 3},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = WHITE, .nbDames = 5},
        {.owner = BLACK, .nbDames = 5},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = WHITE, .nbDames = 3},
        {.owner = NOBODY},
        {.owner = WHITE, .nbDames = 5},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = NOBODY},
        {.owner = BLACK, .nbDames = 2},
    };
    int tmp[2] = {0,0};
    memcpy(state->board, board, sizeof board);
    memcpy(state->out, tmp, sizeof tmp);
    memcpy(state->bar, tmp, sizeof tmp);

}

void init_state(SGameState* state)
{
    *state = (SGameState) {
        .stake = 1,
    };
    init_board(state);
}
