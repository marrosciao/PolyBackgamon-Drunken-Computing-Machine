#include"referee.h"

#include<stdbool.h>

//TODO : changer les paramêtres pour enlever les trucs inutiles
//TODO : refactoring ?
int check_move(const SMove move,
		Dice dices[],
		cuint nb_dices,
		const Player player,
		SGameState * const state)
{
	uint err = 0;
	// Si player==BLACK 1-player == WHITE, de même si player==WHITE.
	// Si player==BLACK==0, 1-player==1, -1*(1-player)==-1, inversement pour player==WHITE.
	// Le joueur noir se déplace de la case
	// 24 vers la case 0, donc dans le sens négatif.
	// Pour vérifier si le déplacement est valide, on prend la valeur absolue 
	// de la différence dest - src en multipliant par -1 si le joueur est 
	// le joueur noir et par 1 si il est blanc.
	uint delta_move = (-1*(1-player)) * (move.dest_point - move.src_point);

	for(uint i=0; i<nb_dices; ++i)
	{
		//TODO : 0 -> zone out
		//TODO : 25 -> zone de fin
		const bool has_out         = state->bar[player]>0;
		const bool authorized_move = dices[i]==delta_move;
		const bool can_take_from   = state->board[move.src_point-1].nbDames>0 && state->board[move.src_point].owner==player;
		const bool can_put_to      = state->board[move.dest_point-1].owner==player || state->board[move.dest_point].nbDames<2;

		if( !authorized_move ||
			!can_take_from ||
			!can_put_to || 
			(has_out && move.src_point!=0))
		{
			err = 1;
		}
	}
	return err;
}

//TODO : changer les paramêtres pour enlever les trucs inutiles
int move_all(
		SGameState *const state,
		SMove const * const moves,
		cuint nb_moves,
		Dice dices[],
		cuint nb_dices,
		const Player player )
{
	uint errors = 0;
	for(uint i=0; i<nb_moves; ++i)
	{
		if(check_move(moves[i], dices, nb_dices, player, state))
		{
			++errors;
		}
		else
		{
			//TODO : 0 -> zone out
			//TODO : 25 -> zone de fin
			move(state, moves[i], player);
		}
	}
	return errors;
}

void move(SGameState * const state, SMove const movement, const Player player)
{
	if(movement.dest_point == 25)
		move_to_end(state, movement, player);
	else if(movement.src_point == 0)
		move_from_out(state, movement, player);
	else
		move_in_board(state, movement, player);
}

void move_from_out(SGameState * const state, SMove const movement, const Player player)
{
	state->bar[player]--;
	put_on(state->board, state->bar, movement.dest_point, player);
}

void move_to_end(SGameState * const state, SMove const movement, const Player player)
{
	take_from(state->board, movement.src_point);
	state->out[player]++;
}

void move_in_board(SGameState * const state, SMove const movement, const Player player)
{
	take_from(state->board, movement.src_point);
	put_on(state->board, state->bar, movement.dest_point, player);
}

void put_on(Square board[24], uint bar[2], cuint dest, const Player p)
{

	if(
		board[dest-1].owner != p &&
		board[dest-1].nbDames<2
	  ){
		board[dest-1].owner = p;
		board[dest-1].nbDames = 0;
		bar[1-p]++;
	}
	board[dest-1].nbDames++;
}

void take_from(Square board[24], cuint src)
{
	board[src-1].nbDames--;
}
