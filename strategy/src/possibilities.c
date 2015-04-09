#include <stdbool.h>

#include "possibilities.h"
#include "utils.h"

/** Pour toutes les fonctions ici, CompactGameState est normalisé. */

static size_t      insert_all_dices(CompactGameState game,
                                    Player player,
                                    size_t max_nb_dice_used,
                                    size_t nb_dices_used,
                                    size_t nb_dices,
                                    const uc dices[nb_dices],
                                    ArrayList *list,
                                    AIListMoves moves);
static bool        is_move_possible(CompactGameState *game, Player player, uint location);
static bool        is_valide_move(CompactGameState *, Player, CompactMove);
static bool        all_dames_in_inner_board(CompactGameState *game, Player player);

#define CHECK_FROM_BOARD {if (game->board[from - 1].owner != player) return false;}
#define CHECK_FROM_BAR {if (!game->bar[player]) return false;}

static bool is_valide_move(CompactGameState *game, Player player, CompactMove move) {
    uint from = move.src_point,
         to = move.dest_point;

    if (to < 25) {
        if (from && !game->bar[player]) {
            CHECK_FROM_BOARD;
        } else if (!from){
            CHECK_FROM_BAR;
        } else {
            return false;
        }
        return is_move_possible(game, player, to);

    } else if (to == 25 && from) {
        CHECK_FROM_BOARD;
        return all_dames_in_inner_board(game, player);

    } else if (to > 25 && from){
        CHECK_FROM_BOARD;
        if (!all_dames_in_inner_board(game, player)) {
            return false;
        }

        for (size_t i = 18; i < from - 1; i++) {
            if (game->board[i].nbDames &&
                game->board[i].owner == player) {
                return false;
            }
        }

        return true;

    } else {
        return false;
    }
}

static bool is_move_possible(CompactGameState *game, Player player, uint location) {
    if (game->board[location - 1].owner == player ||
        game->board[location - 1].owner == NOBODY) {
        return true;
    } else {
        return game->board[location - 1].nbDames < 2;
    }
}

static bool all_dames_in_inner_board(CompactGameState *game, Player player) {
    size_t count = game->bar[player];

    for (size_t i = 0; i < 18; i++) {
        if (game->board[i].owner == player) {
            count += game->board[i].nbDames;
        }
    }

    return count == 0;
}

ArrayList *retrieveEveryPossibility(CompactGameState game, Player player, const unsigned char dices[2]) {
    if (player == BLACK) {
        game = reverse_game(game);
    }

    ArrayList *list = list_new();
    size_t max_nb_dices_used = 0;

    if (dices[0] == dices[1]) {
        uc dices_tmp[4] = {dices[0], dices[0], dices[0], dices[0]};
        max_nb_dices_used = insert_all_dices(game,
                                             player,
                                             max_nb_dices_used,
                                             0,
                                             4,
                                             dices_tmp,
                                             list,
                                             (AIListMoves) { .nombre_mouvements = 0 });
    } else {
        uc dices_tmp[2] = {dices[0], dices[1]};
        max_nb_dices_used = insert_all_dices(game,
                                             player,
                                             max_nb_dices_used,
                                             0,
                                             2,
                                             dices_tmp,
                                             list,
                                             (AIListMoves) { .nombre_mouvements = 0 });
        dices_tmp[0] = dices[1];
        dices_tmp[1] = dices[0];
        max_nb_dices_used = insert_all_dices(game,
                                             player,
                                             max_nb_dices_used,
                                             0,
                                             2,
                                             dices_tmp,
                                             list,
                                             (AIListMoves) { .nombre_mouvements = 0 });

    }

    {
        // On vire les mouvements qui utilisent le moins de dés. Par
        // construction, ils sont tous au début.
        size_t i = 0;
        AIListMoves moves;
        for (; list_get(list, i, &moves) && moves.nombre_mouvements < max_nb_dices_used; i++);

        list_splice(list, 0, i);
    }

    if (player == BLACK) {
        list_foreach(list, reverse_moves);
    }
    return list;
}

static size_t insert_all_dices(CompactGameState game,
                               Player player,
                               size_t max_nb_dice_used,
                               size_t nb_dices_used,
                               size_t nb_dices,
                               const uc dices[nb_dices],
                               ArrayList *list,
                               AIListMoves moves) {
    for (uint i = 0; nb_dices && i <= 24; i++) {
        CompactMove move = {
            .src_point = i,
            .dest_point = i + dices[0],
        };
        if (is_valide_move(&game, player, move)) {
            move.dest_point = min_uint(move.dest_point, 25);
            AIListMoves moves_tmp = moves;
            moves_tmp.mouvement[moves_tmp.nombre_mouvements] = move;
            moves_tmp.nombre_mouvements += 1;
            max_nb_dice_used = insert_all_dices(apply_move(game, player, move),
                                                player,
                                                max_nb_dice_used,
                                                nb_dices_used + 1,
                                                nb_dices - 1,
                                                dices + 1,
                                                list,
                                                moves_tmp);
        }
    }

    if (nb_dices_used >= max_nb_dice_used) {
        max_nb_dice_used = nb_dices_used;
        list_push(list, moves);
    }

    return max_nb_dice_used;
}
