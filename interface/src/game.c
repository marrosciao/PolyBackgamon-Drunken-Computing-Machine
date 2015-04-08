#include"game.h"

#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<assert.h>
#include<SDL/SDL.h>

#include"referee.h"
#include"graph.h"
#include"logger.h"

static Dice rand_dice(){
    return (Dice)(rand()%6)+1;
}
void roll_dice(unsigned char dice[2]){
    dice[0] = rand_dice();
    dice[1] = rand_dice();
}

SGameState* copy_state(SGameState state){
    SGameState *copy = (SGameState*)malloc(sizeof *copy);
    *copy = state;
    return copy;
}

int gamePlayTurn(SGameState* state, IA player[2], Player current, Player* lastStaker, Player* winner, SDL_Surface* screen)
{
    unsigned char dices[2];
    roll_dice(dices);
    char mess[50];
    sprintf(mess ,"résultat des dés : %d, %d\n", dices[0], dices[1]);
    logging("referee_logger", mess, INFO);
    animateDes(dices,screen);
    SGameState* state_copy = copy_state(*state);
    bool end_of_round = false;
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    if( *lastStaker!=current && player[current].func->doubleStack(state_copy) )
    {
        sprintf(mess, "\t%s double la mise : mise ainsi doublée : %d\n", enumToStr[current+1], (state->stake)*2 );
        logging("referee_logger", mess, INFO);
        if( !player[1-current].func->takeDouble(state_copy) )
        {
            sprintf(mess, "\t%s ne suit pas\n", enumToStr[(1-current)+1]);
            logging("referee_logger", mess, INFO);
            end_of_round = true;
            *winner      = current;
        }
        else
        {
            sprintf(mess, "\t%s suit\n", enumToStr[(1-current)+1]);
            logging("referee_logger", mess, INFO);
            state->stake *= 2;
            *lastStaker   = current;
        }
    }
    if( !end_of_round )
    {

        unsigned int errors = 1;
        while(errors>0 && player[current].tries>0)
        {
            player[current].nb_moves = 0;
            player[current].func->playTurn(
                state_copy,
                dices,
                player[current].moves,
                &(player[current].nb_moves),
                player[current].tries
            );
            errors = move_all(
                    state,
                    player[current].moves,
                    player[current].nb_moves,
                    dices,
                    2,
                    current
            );
            player[current].tries -= errors;
            if(errors>0)
            {
                roll_dice(dices);
                sprintf(mess ,"\trésultat des dés : %d, %d\n", dices[0], dices[1]);
                logging("referee_logger", mess, INFO);
            }
        }
    }
    if(player[current].tries<=0)
    {
        sprintf(mess, "%s a fait trop d'erreur et à perdu\n", enumToStr[current+1]);
        logging("referee_logger", mess, ERROR);
        *winner = (Player)(1-current);
        end_of_round = true;
    }
    if(state->out[current]==15)
    {
        *winner = current;
        end_of_round = true;
    }
    free(state_copy);
    return end_of_round;
}
