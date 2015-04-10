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

// Renvoie un nombre aléatoire entre 1 et 6
static Dice rand_dice(){
    return (Dice)(rand()%6)+1;
}
// Renvoie nombre aléatoire entre 1 et 6 (par les paramêtres)
void roll_dice(unsigned char dice[2]){
    dice[0] = rand_dice();
    dice[1] = rand_dice();
}

// Copie l'état du jeu
SGameState* copy_state(SGameState state){
    SGameState *copy = (SGameState*)malloc(sizeof *copy);
    *copy = state;
    return copy;
}

int gamePlayTurn(SGameState* state, IA player[2], Player current, Player* lastStaker, Player* winner, SDL_Surface* screen)
{
    set_level("referee_logger", LOG_LVL);
    
    // On lance les dés
    unsigned char dices[2];
    roll_dice(dices);
    char mess[50];

    sprintf(mess ,"résultat des dés : %d, %d\n", dices[0], dices[1]);
    logging("referee_logger", mess, INFO);

    // On dessine l'animation des dés
    animateDes(dices,screen);
    // On copie l'état du jeu
    SGameState* state_copy = copy_state(*state);

    bool end_of_round = false;
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};

    // On demande au joueur courant s'il veut augmenter la mise, si il n'est pas le dernier
    // à avoir augmenté la mise
    if( *lastStaker!=current && player[current].func->doubleStack(state_copy) )
    {
        sprintf(mess, "%s double la mise : mise ainsi doublée : %d\n", enumToStr[current+1], (state->stake)*2 );
        logging("referee_logger", mess, INFO);

        // On demande a l'autre joueur s'il veut suivre
        if( !player[1-current].func->takeDouble(state_copy) )
        {
            sprintf(mess, "%s ne suit pas\n", enumToStr[(1-current)+1]);
            logging("referee_logger", mess, INFO);

            // Si il ne suit pas, le joueur courant gagne et c'est la fin de la manche
            end_of_round = true;
            *winner      = current;
        }
        else
        {
            sprintf(mess, "%s suit\n", enumToStr[(1-current)+1]);
            logging("referee_logger", mess, INFO);

            // Sinon on double la mise et on sauvegarde le fait que ce soit le joueur
            // courant le dernier à avoir augmenté la mise
            state->stake *= 2;
            *lastStaker   = current;
        }
    }

    // Si la manche n'est pas fini
    if( !end_of_round )
    {
        unsigned int errors = 1;
        player[current].nb_moves = 0;
        // On demande au joueur de faire des mouvements
        player[current].func->playTurn(
            state_copy,
            dices,
            player[current].moves,
            &(player[current].nb_moves),
            player[current].tries
        );

        // On teste les mouvements et on les effectue si ils sont valide
        errors = move_all(
                state,
                player[current].moves,
                player[current].nb_moves,
                dices,
                2,
                current
        );
        // Si le joueur à fait des erreurs, on lui enlève un nombre
        // d'essai égal au nombre d'erreur. Le nombre d'erreur que peut faire
        // un joueur dans un tour est au maximum de 1 : dès qu'il fait un erreur,
        // on arrète son tour et on annule ses mouvement;
        player[current].tries -= errors;

        if(errors>0)
        {
            sprintf(mess ,"résultat des dés : %d, %d\n", dices[0], dices[1]);
            logging("referee_logger", mess, INFO);
        }
    }

    // Si le joueur courant à fait trop d'erreurs, le joueur adverse gagne et c'est la 
    // fin de la manche
    if(player[current].tries<=0)
    {
        sprintf(mess, "%s a fait trop d'erreur et à perdu\n", enumToStr[current+1]);
        logging("referee_logger", mess, ERROR);

        *winner = (Player)(1-current);
        end_of_round = true;
    }

    // Si le joueur courant à mis ses 15 pions dans la zone de fin,
    // il gagne
    if(state->out[current]==15)
    {
        *winner = current;
        end_of_round = true;
    }

    free(state_copy);
    return end_of_round;
}
