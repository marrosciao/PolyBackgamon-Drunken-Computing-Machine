#include"referee.h"

#include<stdbool.h>

int check_move(const SMove move,
		Dice dices[],
		cuint nb_dices,
		const Player player,
		SGameState * const state){
	// TODO : check si il y a des pions "hors jeux" à jouer en priorité
	// TODO : check si le move va dans le bon sens
	uint err = 0;
	uint sum = 0;
	uint delta_move = (-1*(1-player)) * (move.dest_point - move.src_point);
	for(uint i=0; i<nb_dices; ++i){
		sum += dices[i];
		const bool has_out = state->out[player]>0;
		const bool authorized_move = dices[i]==delta_move;// || sum==delta_move;
		const bool can_take_from = state->board[move.src_point].nbDames>0 && state->board[move.src_point].owner==player;
		const bool can_put_to = state->board[move.dest_point].owner==player || state->board[move.dest_point].nbDames<2;
		if( !authorized_move ||
			!can_take_from ||
			!can_put_to || 
			(has_out && move.src_point!=0))
			err = 1;
	}
	return err;
}

int move_all(
		SGameState *const state,
		SMove const * const moves,
		cuint nb_moves,
		Dice dices[],
		cuint nb_dices,
		const Player player ){
	uint errors = 0;
	for(uint i=0; i<nb_moves; ++i){
		if(check_move(moves[i], dices, nb_dices, player, state)){
			++errors;
		} else {
			move(state, moves[i], player);
			//TODO : faire les moves à partir de la zone out et vers la fin
			//TODO : 0 -> zone out
			//TODO : 25 -> zone de fin
		}
	}
	return errors;
}

void move(SGameState * const state, SMove const movement, const Player player){
	if(movement.dest_point == 25)
		move_to_end(state, movement, player);
	else if(movement.src_point == 0)
		move_from_out(state, movement, player);
	else
		move_in_board(state, movement, player);
}

void move_from_out(SGameState * const state, SMove const movement, const Player player){
	state->out[player]--;
	if(
		state->board[movement.dest_point].owner != player &&
		state->board[movement.dest_point].nbDames<2
	  ){
		state->board[movement.dest_point].owner = player;
		state->board[movement.dest_point].nbDames = 0;
		state->out[1-player]++;
	}
	state->board[movement.dest_point].nbDames++;
}

void move_to_end(SGameState * const state, SMove const movement, const Player player){
	state->board[movement.src_point].nbDames--;
	state->bar[player]++;
}

void move_in_board(SGameState * const state, SMove const movement, const Player player){
	state->board[movement.src_point].nbDames--;
	if(
		state->board[movement.dest_point].owner != player &&
		state->board[movement.dest_point].nbDames<2
	  ){
		state->board[movement.dest_point].owner = player;
		state->board[movement.dest_point].nbDames = 0;
		state->out[1-player]++;
	}
	state->board[movement.dest_point].nbDames++;
}
