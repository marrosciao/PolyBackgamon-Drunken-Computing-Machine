#include<stdbool.h>
#include<assert.h>

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

int main(){
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
	return 0;
}
