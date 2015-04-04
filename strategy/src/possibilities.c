#include <stdbool.h>

#include "possibilities.h"

/** Pour toutes les fonctions ici, SGameState est normalisé. */

bool is_move_possible(SGameState *game, Player player, uint location);
bool is_valide_move(SGameState *game, Player player, uint from, uint len);
void reverse_game(SGameState*);
void reverse_move(SMove);

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
