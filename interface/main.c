#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>
#include<string.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"backgammon.h"
#include"config.h"


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

void init_func(void* handle, Functions* func){
	// TODO : faire le test si les fonctions ont bien été chargé
	func->initLibrary = (pfInitLibrary)dlsym(handle, "InitLibrary");
	func->startMatch  = (pfStartMatch)dlsym(handle, "StartMatch");
	func->startGame   = (pfStartGame)dlsym(handle, "StartGame");
	func->endGame	  = (pfEndGame)dlsym(handle, "EndGame");
	func->endMatch 	  = (pfEndMatch)dlsym(handle, "EndMatch");
	func->doubleStack = (pfDoubleStack)dlsym(handle, "DoubleStack");
	func->takeDouble  = (pfTakeDouble)dlsym(handle, "TakeDouble");
	func->playTurn    = (pfPlayTurn)dlsym(handle, "PlayTurn");
}

void init_lib(const char* lib_path, void** handle, Functions* func){
	*handle = dlopen(lib_path, RTLD_NOW);
	if(handle==NULL){
		perror("Unable to open the library");
		exit(EXIT_FAILURE);
	}
	dlerror();
	init_func(*handle, func);
}

int main(){
	// --- Initialisation des bibliothèques
	void* white_handle = NULL;
	Functions white_funcs;
	char* white_path = calloc(strlen(LIB_PATH)+strlen("/libstrategy.so")+1, sizeof(char));
	sprintf(white_path, "%s/libstrategy.so", LIB_PATH);
	init_lib(white_path, &white_handle, &white_funcs);
	char white_name[50];
	white_funcs.initLibrary(white_name);
	printf("White I.A. : %s\n", white_name);

	void* black_handle = NULL;
	Functions black_funcs;
	char* black_path = calloc(strlen(LIB_PATH)+strlen("/libstrategy.so")+1, sizeof(char));
	sprintf(black_path, "%s/libstrategy.so", LIB_PATH);
	init_lib(black_path, &black_handle, &black_funcs);
	char black_name[50];
	black_funcs.initLibrary(black_name);
	printf("Black I.A. : %s\n", black_name);

	// --- Fermeture des bibliothèques
	dlclose(white_handle);
	dlclose(black_handle);
	return EXIT_SUCCESS;
}
