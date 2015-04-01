#include"init.h"

#include<dlfcn.h>
#include<stdlib.h>

void init_func(void* handle, Functions* func, err_func err)
{
	// TODO : faire le test si les fonctions ont bien été chargé
	func->initLibrary = (pfInitLibrary)dlsym(handle, "InitLibrary");
	test(!dlerror(), err);
	func->startMatch  = (pfStartMatch)dlsym(handle, "StartMatch");
	test(!dlerror(), err);
	func->startGame   = (pfStartGame)dlsym(handle, "StartGame");
	test(!dlerror(), err);
	func->endGame	  = (pfEndGame)dlsym(handle, "EndGame");
	test(!dlerror(), err);
	func->endMatch 	  = (pfEndMatch)dlsym(handle, "EndMatch");
	test(!dlerror(), err);
	func->doubleStack = (pfDoubleStack)dlsym(handle, "DoubleStack");
	test(!dlerror(), err);
	func->takeDouble  = (pfTakeDouble)dlsym(handle, "TakeDouble");
	test(!dlerror(), err);
	func->playTurn    = (pfPlayTurn)dlsym(handle, "PlayTurn");
	test(!dlerror(), err);
}

void init_lib(const char* lib_path, void** handle, Functions* func, err_func err)
{
	*handle = dlopen(lib_path, RTLD_NOW);
	test(*handle == NULL, err);
	dlerror();
	init_func(*handle, func, err);
}

void init_state(SGameState* state)
{
	for(unsigned int i=0; i<24; ++i)
	{
		if(i==12 || i==13 || i==6 || i==19)
		{
			state->board[i].nbDames = 5;
			if(i==12 || 19) 		state->board[i].owner = WHITE;
			else if(i==13 || i==6) 	state->board[i].owner = BLACK;
		}
		else if(i==8 || i==17)
		{
			state->board[i].nbDames = 3;
			if(i==8) state->board[i].owner = BLACK;
			else 	 state->board[i].owner = WHITE;
		}
		else if(i==1 || i==24)
		{
			//TODO : finie
			state->board[i].nbDames = 2;
			if(i==1) state->board[i].owner = WHITE;
			else 	 state->board[i].owner = BLACK;
		}
		state->board[i].owner = NOBODY;
		state->board[i].nbDames = 0;
	}
}
