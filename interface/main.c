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
	init_lib("../strategy/libstrategy.so", &white_handle, &white_funcs);
	char white_name[50];
	white_funcs.initLibrary(white_name);//TODO : erreur lors de la recopie du nom
	printf("White I.A. : %s\n", white_name);

	void* black_handle = NULL;
	Functions black_funcs;
	init_lib("../strategy/libstrategy.so", &black_handle, &black_funcs);
	char black_name[50];
	black_funcs.initLibrary(black_name);//TODO : erreur lors de la recopie du nom
	printf("Black I.A. : %s\n", black_name);

	// --- Fermeture des bibliothèques
	dlclose(white_handle);
	dlclose(black_handle);
	return EXIT_SUCCESS;
}
