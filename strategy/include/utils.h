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

CompactGameState  reverse_game(CompactGameState);
AIListMoves reverse_moves(AIListMoves);
Player opposing_player(Player player);

/**
 * @brief Applique un mouvement sur le plateau.
 *
 * @param game L'état du jeu concerné.
 * @param player Le joueur courant.
 * @param move Le mouvement à appliquer.
 *
 * @return L'état du jeu modifié.
 */
CompactGameState apply_move(CompactGameState, Player, CompactMove);
