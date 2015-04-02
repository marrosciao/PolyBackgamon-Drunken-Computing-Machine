#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>
#include<string.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"backgammon.h"
#include"config.h"
#include"referee.h"
#include"init.h"

//TODO : faire les test et merge la branche
//TODO : appliquer clang-format

void err(String str){
	fprintf(stderr, "%s -> %s\n",str, dlerror());
	exit(EXIT_FAILURE);
}

int main(){
	// --- Initialisation des bibliothèques {{{
	void* white_handle = NULL;
	Functions white_funcs;
	char* white_path = calloc(strlen(LIB_PATH)+strlen("/libstrategy.so")+1, sizeof(char));
	sprintf(white_path, "%s/libstrategy.so", LIB_PATH);
	init_lib(white_path, &white_handle, &white_funcs, err);

	void* black_handle = NULL;
	Functions black_funcs;
	char* black_path = calloc(strlen(LIB_PATH)+strlen("/libstrategy.so")+1, sizeof(char));
	sprintf(black_path, "%s/libstrategy.so", LIB_PATH);
	init_lib(black_path, &black_handle, &black_funcs, err);
	// }}}

	// --- Initialisation du jeux {{{
	SGameState state;
	init_state(&state);//TODO

	char black_name[50];
	char white_name[50];
	black_funcs.initLibrary(black_name);
	white_funcs.initLibrary(white_name);
	printf("Black I.A. : %s\n", black_name);
	printf("White I.A. : %s\n", white_name);

	cuint target_score = 1;
	black_funcs.startMatch(target_score);
	white_funcs.startMatch(target_score);
	bool finished = false;
	// }}}

	// --- Boucle principale
	while(!finished){
		black_funcs.startGame(BLACK);
		white_funcs.startGame(WHITE);
		bool end_of_round = false;
		state.stake = 1;//TODO : Voir avec stake dans SGameState
		Player winner = NOBODY;
		while(!end_of_round){
			//TODO : faire les copies de state
			if( white_funcs.doubleStack(&state) ){
				if( !black_funcs.takeDouble(&state) ){
					end_of_round = true;
					winner = WHITE;
				} else {
					state.stake*=2;
				}
			} else if( black_funcs.doubleStack(&state) ) {
				if( !white_funcs.takeDouble(&state) ){
					end_of_round = true;
					winner = BLACK;
				} else {
					state.stake *= 2;
				}
			}
			//TODO : reste
		}
		white_funcs.endGame();
		black_funcs.endGame();
	}

	black_funcs.endMatch();
	white_funcs.endMatch();


	// --- Fermeture des bibliothèques {{{
	dlclose(white_handle);
	dlclose(black_handle);
	free(white_path);
	free(black_path);
	// }}}
	return EXIT_SUCCESS;
}
