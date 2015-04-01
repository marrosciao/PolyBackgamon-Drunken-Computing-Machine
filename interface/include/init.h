#ifndef _INIT_INCLUDED
#define _INIT_INCLUDED

#include"error.h"
#include"backgammon.h"

typedef struct{
	pfInitLibrary	initLibrary;
	pfStartMatch	startMatch;
	pfStartGame		startGame;
	pfEndGame		endGame;
	pfEndMatch		endMatch;
	pfDoubleStack	doubleStack;
	pfTakeDouble	takeDouble;
	pfPlayTurn		playTurn;
} Functions;


void init_func(void*, Functions*, err_func);
void init_lib(const char*, void**, Functions*, err_func);
void init_state(SGameState*);
#endif
