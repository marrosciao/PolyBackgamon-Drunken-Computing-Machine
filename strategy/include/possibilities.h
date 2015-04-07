#pragma once

#include <stddef.h>

#include "backgammon.h"
#include "arraylist.h"

/** uint est plus court que unsigned int ^^ */
typedef unsigned int uint;

/**
 * @brief Retourne tous les états possibles du jeu à la fin d'un tour.
 *
 * Toutes les combinaisons de mouvement retournées sont garanties d'être
 * valides, ce qui inclut d'utiliser un maximum de dés. Il peut y avoir des
 * doublons ou des équivalences dans les mouvements retournés.
 *
 * @param game L'état du jeu au début du tour.
 * @param player Le joueur courant.
 * @param dices Les dés à utiliser.
 *
 * @return Une ArrayList des mouvements possibles.
 */
ArrayList *retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2]);

/**
 * @brief Applique un mouvement sur le plateau.
 *
 * @param game L'état du jeu concerné.
 * @param player Le joueur courant.
 * @param move Le mouvement à appliquer.
 *
 * @return L'état du jeu modifié.
 */
SGameState apply_move(SGameState, Player, SMove);
