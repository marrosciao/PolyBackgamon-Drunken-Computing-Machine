#ifndef _GAME_INCLUDED
#define _GAME_INCLUDED

#include"init.h"
#include"backgammon.h"

typedef struct{
    char* lib_path;
    void* lib_handle;
    Functions* func;
    char name[50];
    int tries;
    unsigned int nb_moves;
    SMove moves[4];
}IA;

int gamePlayTurn(SGameState* state, IA players[2], Player current, Player* lastStaker, Player* winner);

void roll_dice(unsigned char dice[2]);

void copy_state(SGameState state, SGameState* copy);

#endif
