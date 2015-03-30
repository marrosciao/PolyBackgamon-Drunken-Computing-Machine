#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"include/backgammon.h"


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

void init_lib(void* handle, Functions* func){
	func->initLibrary = (pfInitLibrary)dlsym(handle, "InitLibrary");
	func->startMatch  = (pfStartMatch)dlsym(handle, "StartMatch");
	func->startGame   = (pfStartGame)dlsym(handle, "StartGame");
	func->endGame	  = (pfEndGame)dlsym(handle, "EndGame");
	func->endMatch 	  = (pfEndMatch)dlsym(handle, "EndMatch");
	func->doubleStack = (pfDoubleStack)dlsym(handle, "DoubleStack");
	func->takeDouble  = (pfTakeDouble)dlsym(handle, "TakeDouble");
	func->playTurn    = (pfPlayTurn)dlsym(handle, "PlayTurn");
}

int main(){
	void *white_handle = dlopen("../strategy/libstrategy.so", RTLD_NOW);
	if(white_handle==NULL){
		perror("Unable to open the library");
		exit(EXIT_FAILURE);
	}
	dlerror();
	Functions white_funcs;
	init_lib(white_handle, &white_funcs);
	char white_name[50];
	white_funcs.initLibrary(white_name);//TODO : erreur lors de la recopie du nom
	printf("%s\n", white_name);
	dlclose(white_handle);
	return 0;
}
