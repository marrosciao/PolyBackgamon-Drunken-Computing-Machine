#include"referee.h"

int check_move(const SMove move, Dice dices[], cuint nb_dices){
	uint err = 0;
	uint sum = 0;
	uint delta_move = move.dest_point - move.src_point;
	for(uint i=0; i<nb_dices; ++i){
		sum += dices[i];
		if( dices[i]!=delta_move && sum!=delta_move)
			err = 1;
	}
	return err;
}

