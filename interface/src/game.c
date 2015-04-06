#include"game.h"

#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<stdio.h>

#include"referee.h"

static Dice rand_dice(){
    return (Dice)(rand()%6)+1;
}
void roll_dice(unsigned char dice[2]){
    dice[0] = rand_dice();
    dice[1] = rand_dice();
}

SGameState* copy_state(SGameState state){
    SGameState *copy = malloc(sizeof *copy);
    *copy = state;
    return copy;
}

int gamePlayTurn(SGameState* state, IA player[2], Player current, Player* lastStaker, Player* winner)
{
    unsigned char dices[2];
    roll_dice(dices);
    printf("\t\trésultat des dés : %d, %d\n", dices[0], dices[1]);
    SGameState* state_copy = copy_state(*state);
    bool end_of_round = false;
    *winner = NOBODY;
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    if( *lastStaker!=current && player[current].func->doubleStack(state_copy) )
    {
        printf("\t\t %s double la mise\n", enumToStr[current+1]);
        if( !player[1-current].func->takeDouble(state_copy) )
        {
            printf("\t\t %s ne suit pas\n", enumToStr[(1-current)+1]);
            end_of_round = true;
            *winner = current;
        }
        else
        {
            printf("\t\t %s suit\n", enumToStr[(1-current)+1]);
            state->stake *= 2;
            *lastStaker = current;
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
        for(unsigned int i=0; i<player[current].nb_moves; ++i){
            printf("%s : %d -> %d\n", enumToStr[current+1], player[current].moves[i].src_point, player[current].moves[i].dest_point);
        }
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
        printf("\t\t%s a fait trop d'erreurs\n", enumToStr[current+1]);
        *winner = (Player)(1-current);
        end_of_round = true;
    }
    return end_of_round;
}
