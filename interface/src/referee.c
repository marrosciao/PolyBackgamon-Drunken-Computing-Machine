#include"referee.h"

int check_move(const SMove move,
		Dice dices[],
		cuint nb_dices,
		const Player player,
		SGameState * const state){
	// TODO : check si il y a des pions "hors jeux" à jouer en priorité
	// TODO : check si le move va dans le bon sens
	uint err = 0;
	uint sum = 0;
	uint delta_move = move.dest_point - move.src_point;
	for(uint i=0; i<nb_dices; ++i){
		sum += dices[i];
		if( (
				dices[i]!=delta_move &&
				sum!=delta_move
			) || (
				state->board[move.src_point].nbDames<=0 ||
				state->board[move.src_point].owner!=player
			) || (
				state->board[move.dest_point].owner!=player &&
				state->board[move.dest_point].nbDames<2
			) )
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
		const Player player
		){
	uint errors = 0;
	for(int i=0; i<nb_moves; ++i){
		if(check_move(moves[i], dices, nb_dices)){
			++errors;
		} else {
			move(state, moves[i], player);
		}
	}
	return errors;
}

void move(SGameState * const state, SMove const movement, const Player player){
	state->board[movement.src_point]->nbDames--;
	if(
		state->board[movement.dest_point]->owner != player &&
		state->board[movement.dest_point]->nbDames<2
	  ){
		state->board[movement.dest_point]->owner = player;
		state->board[movement.dest_point]->nbDames = 0;
		state->out[1-player]++;
	}
	state->board[movement.dest_point]->nbDames++;
}
