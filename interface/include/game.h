#ifndef _GAME_INCLUDED
#define _GAME_INCLUDED

#include"init.h"
#include"backgammon.h"

//! struct rassemblant les infos d'une IA
typedef struct{
    //! chemin de la bibliothèque dynamique
    char* lib_path;
    //! handler de la bibliothèque dynamique
    void* lib_handle;
    //! fonctions chargé par une bibliothèque dynamique
    Functions* func;
    //! nom de l'IA
    char name[50];
    //! nombre d'essai restant au joueur
    int tries;
    //! nombre de mouvement fait par l'IA
    unsigned int nb_moves;
    //! mouvement fait par l'IA
    SMove moves[4];
}IA;

int gamePlayTurn(SGameState* state, IA players[2], Player current, Player* lastStaker, Player* winner);

void roll_dice(unsigned char dice[2]);

void copy_state(SGameState state, SGameState* copy);

#endif
