#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"backgammon.h"
#include"config.h"
#include"referee.h"
#include"init.h"

//TODO : faire les test et merge la branche
//TODO : appliquer clang-format
//TODO : refactoring pour que ça soit plus propre
//TODO : gestion erreur

void err(String str){
	fprintf(stderr, "%s -> %s\n",str, dlerror());
	exit(EXIT_FAILURE);
}

void roll_dice(unsigned char dice[2]){
	srand(time(NULL));
	dice[1] = (unsigned char)( (rand()%5)+1 );
	dice[2] = (unsigned char)( (rand()%5)+1 );
}
void copy_state(SGameState state, SGameState* copy){
	copy = malloc(sizeof(SGameState));
	memcpy((void*)state.board, (void*)copy->board, 24);
	memcpy((void*)state.out,   (void*)copy->out,   2);
	memcpy((void*)state.bar,   (void*)copy->bar,   2);
	copy->whiteScore = state.whiteScore;
	copy->blackScore = state.blackScore;
	copy->turn = state.turn;
	copy->stake = state.stake;
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
	//TODO : faire la gestion des paramêtres en ligne de commande
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
	Player player = choose_start_player();
	SGameState state;
	init_state(&state);

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
			//TODO : faire les copies de state
			//TODO : roll dice
			roll_dice(dices);
			SGameState* state_copy = NULL;
			copy_state(state, state_copy);
			if( white_funcs.doubleStack(state_copy) )
			{
				if( !black_funcs.takeDouble(state_copy) )
				{
					end_of_round = true;
					winner = WHITE;
				}
				else
				{
					state.stake*=2;
				}
			}
			else if( black_funcs.doubleStack(state_copy) )
			{
				if( !white_funcs.takeDouble(state_copy) )
				{
					end_of_round = true;
					winner = BLACK;
				}
				else
				{
					state.stake *= 2;
				}
			}
			if(!end_of_round)
			{
				//TODO : reste
				if(player == WHITE)
				{
					white_funcs.playTurn(state_copy, dices, white_move, &white_nb_move, white_tries);
					white_tries -= move_all(&state, white_move, white_nb_move, dices, 2, WHITE);
				}
				else
				{
					black_funcs.playTurn(state_copy, dices, black_move, &black_nb_move, black_tries);
					black_tries -= move_all(&state, black_move, black_nb_move, dices, 2, BLACK);
				}
				if(black_tries<0)
				{
					winner = WHITE;
					end_of_round = true;
				}
				else if(white_tries<0)
				{
					winner = BLACK;
					end_of_round = true;
				}
				player = 1-player;
			}
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
	white_funcs.endMatch();


	// --- Fermeture des bibliothèques {{{
	dlclose(white_handle);
	dlclose(black_handle);
	free(white_path);
	free(black_path);
	// }}}
	return EXIT_SUCCESS;
}
