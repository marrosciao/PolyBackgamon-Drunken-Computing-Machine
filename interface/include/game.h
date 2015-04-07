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

/**
 * @fn void roll_dice(unsigned char dice[2])
 * @brief Éffectue un lancé de dés
 * @param dice tableau des dés dont il faut généré les valeurs²
 */
void roll_dice(unsigned char dice[2]);

/**
 * @fn SGameState* copy_state(SGameState state)
 * @brief Copie un SGameState
 * @param state état à copier
 * @return pointeurs vers la copie de l'état
 */
SGameState* copy_state(SGameState state);

#endif
