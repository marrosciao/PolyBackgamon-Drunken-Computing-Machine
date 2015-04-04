#pragma once

#include <stddef.h>

#include "backgammon.h"

typedef unsigned int uint;

/**
 * @brief Calcule les états possibles à la fin du tour.
 *
 * Après appel de la fonction, `states[i]` contient l'état du jeu après
 * application des `nb_dices_used` mouvements de `moves[i]` sur game. Tous les
 * éléments de `moves` sont garantis d'utiliser `nb_dices_used`.
 *
 * @param game L'état du plateau du début du tour.
 * @param dices Les dés à utiliser.
 * @param player Le joueur courant.
 * @param max_nb_moves Nombre maximum de mouvements à calculer.
 * @param moves Tableau d'au moins max_nb_moves contenant les mouvements
 *              calculés.
 * @param states Tableau d'au moins max_nb_moves contenant les états de jeu
 *               calculés.
 * @param nb_dices_used Nombre de dés utilisés.
 *
 * @return Le nombre d'états effectivement calculés.
 */
size_t get_all_possible_moves(const SGameState * game,
                              const uint dices[2],
                              Player player,
                              size_t max_nb_moves,
                              SMove moves[max_nb_moves][4],
                              SGameState states[max_nb_moves],
                              size_t *nb_dices_used);
