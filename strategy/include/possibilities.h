#pragma once

/**
 * @file possibilities.h
 * @brief Permet de calculer les états possibles à la fin du tour.
 */

#include <stddef.h>

#include "backgammon.h"
#include "arraylist.h"

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
ArrayList *retrieveEveryPossibility(CompactGameState game, Player player, const unsigned char dices[2]);
