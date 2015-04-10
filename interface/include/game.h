#ifndef _GAME_INCLUDED
#define _GAME_INCLUDED

#include<SDL/SDL.h>
#include"init.h"
#include"backgammon.h"

//! struct rassemblant les infos d'une IA
typedef struct{
    //! nombre de match gagné
    unsigned int match_won;
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

/**
 * @fn int gamePlayTurn(SGameState* state,
 * IA players[2],
 * Player current,
 * Player* lastStaker,
 * Player* winner,
 * SDL_Surface* screen)
 * @brief Joue un tour
 * @param state      état du jeu
 * @param player     structure rassemblant les informations sur les joueurs
 * @param current    joueur dont c'est le tour
 * @param lastStaker Dernier joueur a avoir augmenté la mise, change si le joueur augmente la mise
 * @param winner     paramètre de retour, permet de savoir qui à gagné si la manche se termine
 * @param screen     l'écran sur lequel afficher le plateau de jeu
 * @return true si la manche est fini, faux si il faut continuer la manche
 */
int gamePlayTurn(SGameState* state, IA players[2], Player current, Player* lastStaker, Player* winner, SDL_Surface* screen);

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
