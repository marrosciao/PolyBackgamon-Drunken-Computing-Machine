#include <stdbool.h>

#include "possibilities.h"

/** Pour toutes les fonctions ici, SGameState est normalisé. */

bool        is_move_possible(SGameState *game, Player player, uint location);
bool        is_valide_move(SGameState *game, Player player, uint from, uint len);
SGameState  reverse_game(SGameState);
AIListMoves reverse_moves(AIListMoves);

bool is_valide_move(SGameState *game, Player player, uint from, uint len) {
    if (from > 25 || (from + len) >= 25) {
        return false;
    }

    if (from && game->bar[player]) {
        return false;
    }

    if (from == 0) {
        return is_move_possible(game, player, from + len);
    } else if (from + len == 25) {

    } else {
    }
}

bool is_move_possible(SGameState *game, Player player, uint location) {
    if (game->board[location].owner == player ||
        game->board[location].owner == NOBODY) {
        return true;
    } else {
        return game->board[location].nbDames < 2;
    }
}

ArrayList *retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2]) {
    if (player == BLACK) {
        game = reverse_game(game);
    }

    ArrayList *list = list_new();

    // TODO: implémenter !

    if (player == BLACK) {
        list_foreach(list, reverse_moves);
    }
    return list;
}

SGameState reverse_game(SGameState game) {
    Square board[24];

    for (size_t i = 0; i < 24; i++) {
        board[i] = game.board[24 - i];
    }

    for (size_t i = 0; i < 24; i++) {
        game.board[i] = board[i];
    }

    return game;
}

AIListMoves reverse_moves(AIListMoves moves) {
    for (size_t i = 0; i < moves.nombre_mouvements; i++) {
        moves.mouvement[i].src_point = 25 - moves.mouvement[i].src_point;
        moves.mouvement[i].dest_point = 25 - moves.mouvement[i].dest_point;
    }

    return moves;
}
