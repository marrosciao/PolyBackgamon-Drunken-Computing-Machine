#include"game.h"

#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>

#include"referee.h"

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

int gamePlayTurn(SGameState* state, IA player[2], Player current, Player* lastStaker, Player* winner)
{
    unsigned char dices[2];
    roll_dice(dices);
    SGameState* state_copy = NULL;
    copy_state(*state, state_copy);
    bool end_of_round = false;
    *winner = NOBODY;
    if( *lastStaker!=current && player[current].func->doubleStack(state_copy) )
    {
        if( !player[1-current].func->takeDouble(state_copy) )
        {
            end_of_round = true;
            *winner = current;
        }
        else
        {
            state->stake *= 2;
        }
    }
    if( !end_of_round )
    {
        player[current].func->playTurn(
                state_copy,
                dices,
                player[current].moves,
                &(player[current].nb_moves),
                player[current].tries
        );
        player[current].tries -= move_all(
                state,
                player[current].moves,
                player[current].nb_moves,
                dices,
                2,
                current
        );
    }
    if(player[current].tries<0)
    {
        *winner = 1-current;
        end_of_round = true;
    }
    return end_of_round;
}



