#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"include/backgammon.h"

typedef SDL_Surface Surface;
typedef SDL_Window Window;

bool init(SDL_Window* win, SDL_Surface** surf, int width, int height, const char * const name){
	bool success = true;
	if( SDL_Init(SDL_INIT_VIDEO) <0){
		success = false;
	} else {
		win = SDL_CreateWindow(name,
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				SDL_WINDOW_SHOWN);
		if(!win){
			success=false;
		} else {
			*surf = SDL_GetWindowSurface(win);
			//Fill the surface white 
			SDL_FillRect( *surf, NULL, SDL_MapRGB( (*surf)->format, 0xFF, 0xFF, 0xFF ) );
		}
	}
	return success;
}

void close_(SDL_Surface *surf, SDL_Window* win){
	SDL_FreeSurface(surf);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

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
	white_funcs.initLibrary(white_name);
	printf("%s\n", white_name);

	const int SCREEN_WIDTH = 640; 
	const int SCREEN_HEIGHT = 480;
	SDL_Window* win = NULL;
	SDL_Surface* surface = NULL;
	bool isInit = init(win, &surface, SCREEN_WIDTH, SCREEN_HEIGHT, "Backgammon");
	assert(isInit);
	SDL_Surface* gHelloWorld = SDL_LoadBMP( "rc/board.bmp" );//TODO : trouver comment load un jpg
	//TODO : pourquoi pas d'affichage de l'image
	if( gHelloWorld == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
	} else {
		SDL_BlitSurface( gHelloWorld, NULL, surface, NULL);
		SDL_UpdateWindowSurface(win);
		SDL_Delay(2000);
	}
	if(isInit) close_(gHelloWorld, win);
	dlclose(white_handle);
	return 0;
}
