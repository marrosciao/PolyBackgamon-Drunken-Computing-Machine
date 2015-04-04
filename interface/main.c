#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>
#include<string.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"backgammon.h"
#include"config.h"
#include"init.h"
#include"game.h"

#define enum_to_string(val) #val

//TODO : faire les test et merge la branche
//TODO : appliquer clang-format
//TODO : refactoring pour que ça soit plus propre
//TODO : gestion erreur

void err(String str){
	fprintf(stderr, "%s -> %s\n",str, dlerror());
	exit(EXIT_FAILURE);
}

Player choose_start_player()
{
	unsigned char dice[2];
	roll_dice(dice);
	if( dice[BLACK] > dice[WHITE])
		return BLACK;
	else if( dice[WHITE] > dice[BLACK] )
		return WHITE;
	else
		return choose_start_player();
}

int main(){
    IA players[2];
    /*void* handle = dlopen("strategy/libstrategy.so", RTLD_NOW);*/
    /*printf("%s\n", dlerror());*/
    /*fflush(stdout);*/
    /*pfInitLibrary fn = (pfInitLibrary)dlsym(handle, "InitLibrary");*/
    /*printf("%s\n", dlerror());*/
    /*fflush(stdout);*/
    /*char name[50];*/
    /*fn(name);*/
    /*printf("%s\n", name);*/
	//TODO : faire la gestion des paramêtres en ligne de commande
	// --- Initialisation des bibliothèques {{{
    for(unsigned int i=0; i<2; ++i)
    {
        players[i].lib_handle = NULL;
        players[i].lib_path = calloc(strlen("../strategy/libstrategy.so")+1, sizeof(char));
        sprintf( (players[i].lib_path) , "../strategy/libstrategy.so");
        players[i].func = malloc( sizeof(Functions) );
        init_lib( (players[i].lib_path) , &(players[i].lib_handle), players[i].func, err);
        //players[i].func.initLibrary( (players[i].name) );
        printf("%p\n", players[i].func->endMatch);
        players[i].func->endMatch();
        printf("%s I.A. : %s\n", enum_to_string(i),players[i].name );
    }
	// }}}
    /*
	// --- Initialisation du jeux {{{
	Player current = choose_start_player();
	SGameState state;
	init_state(&state);


	cuint target_score = 1;
	black_funcs.startMatch(target_score);
	white_funcs.startMatch(target_score);
	bool finished = false;
	const unsigned int maxScore = 3;
	// }}}

	// --- Boucle principale
	while(!finished)
	{
		//TODO :séparer en fonction
		black_funcs.startGame(BLACK);
		white_funcs.startGame(WHITE);
		bool end_of_round = false;
		state.stake = 1;
		Player winner = NOBODY;
		unsigned char dices[2];
		SMove white_move[4];
		unsigned int white_nb_move = 0;
		int white_tries = 3;
		SMove black_move[4];
		unsigned int black_nb_move = 0;
		int black_tries = 3;
		while(!end_of_round)
		{
            end_of_round = gamePlayTurn(&state, players, current, &lastStaker, &winner);
            current = 1-current;
		}
		white_funcs.endGame();
		black_funcs.endGame();
		if(winner==WHITE)
		{
			state.whiteScore+=state.stake;
			finished = state.whiteScore==maxScore;
		}
		else
		{
			state.blackScore+=state.stake;
			finished = state.blackScore==maxScore;
		}
	}

	black_funcs.endMatch();
	white_funcs.endMatch();*/


	// --- Fermeture des bibliothèques {{{
    /*for(unsigned int i=0; i<2; ++i)*/
    /*{*/
        /*dlclose(players[i].lib_handle);*/
        /*free(players[i].lib_path);*/
    /*}*/
	// }}}
	return EXIT_SUCCESS;
}
