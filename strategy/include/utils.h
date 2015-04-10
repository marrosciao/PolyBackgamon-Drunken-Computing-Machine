#pragma once

#include "backgammon.h"
#include "arraylist.h"

typedef uint8_t uint;
typedef unsigned char uc;


#define max(x, y) _Generic((x),\
    size_t: max_size_t,\
    long: max_long,\
    uint: max_uint)(x,y)

size_t max_size_t(size_t, size_t);
long   max_long(long, long);
uint   max_uint(uint, uint);

#define min(x, y) _Generic((x),\
    size_t: min_size_t,\
    long: min_long,\
    uint: min_uint)(x,y)

size_t min_size_t(size_t, size_t);
long   min_long(long, long);
uint   min_uint(uint, uint);

/**
 * @brief Inverse l'orientation du plateau de jeu.
 *
 * Cette fonction est utilisée en interne pour simplifier le calcul des
 * possibilités.
 *
 * @param game Le plateau avant inversion.
 *
 * @return Le plateau après inversion.
 */
CompactGameState  reverse_game(CompactGameState);

/**
 * @brief Inverse l'orientation d'un mouvement.
 *
 * Un mouvement 1 -> 3 devient un mouvement 24 -> 22 et inversement.
 * Cette fonction est utilisée en interne pour simplifier le calcul des
 * possibilités.
 *
 * @param move Le mouvement à inverser.
 *
 * @return Le mouvement inversé.
 */
AIListMoves reverse_moves(AIListMoves);

/**
 * @brief Retourne l'adverse du joueur en paramètre.
 *
 * @param player Le joueur courant.
 *
 * @return BLACK si player est WHITE, WHITE sinon.
 */
CompactPlayer opposing_player(CompactPlayer player);

/**
 * @brief Applique un mouvement sur le plateau.
 *
 * @param game L'état du jeu concerné.
 * @param player Le joueur courant.
 * @param move Le mouvement à appliquer.
 *
 * @return L'état du jeu modifié.
 */
CompactGameState apply_move(CompactGameState, CompactPlayer, CompactMove);
