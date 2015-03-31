#ifndef _REFEREE_INCLUDED
#define _REFEREE_INCLUDED

#include"backgammon.h"

typedef const unsigned char Dice;
typedef const unsigned int cuint;
typedef unsigned int uint;

//! return 0 if the movement are correct, 1 else
int check_move(const SMove, Dice[], cuint, const Player, SGameState * const);

//! return the number of bad moves
int move_all(SGameState * const state, SMove const * const moves,
		cuint nb_moves, Dice dices[], cuint nb_dices, const Player player);

void move(SGameState * const, SMove const, const Player);
void move_from_out(SGameState * const, SMove const, const Player);
void move_to_end(SGameState * const, SMove const, const Player);
void move_in_board(SGameState * const, SMove const, const Player);

#endif
