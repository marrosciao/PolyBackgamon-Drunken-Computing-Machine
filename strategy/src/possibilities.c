#include <stdbool.h>

#include "possibilities.h"
#include "utils.h"

/** Pour toutes les fonctions ici, CompactGameState est normalisé (voir
 * `reverse_game` et `reverse_moves`). */

/**
 * @brief Fonction récursive calculant tous les mouvements possibles.
 *
 * @param game Le plateau courant.
 * @param player Le joueur courant.
 * @param max_nb_dice_used Le nombre maximum de dés déjà utilisés, pour éviter
 *                         de retourner des mouvements qui n'utilisent pas assez
 *                         de dés.
 * @param nb_dices_used Le nombre de dés déjà utilisés dans la récursion.
 * @param nb_dices Le nombre de dés restant à tester.
 * @param dices Les dés à insérer.
 * @param list Liste dans laquelle seront insérés les mouvements valides.
 * @param moves Les mouvements déjà validés dans la récursion.
 *
 * @return Le nombre maximum de dés utilisés.
 */
static size_t insert_all_dices(CompactGameState game,
                               CompactPlayer player,
                               size_t max_nb_dice_used,
                               size_t nb_dices_used,
                               size_t nb_dices,
                               const uc dices[nb_dices],
                               ArrayList *list,
                               AIListMoves moves);

/**
 * @brief Vérifie si le joueur peut placer une dame à l'endroit indiqué.
 *
 * Cette fonction sert à simplifier le code de `is_move_possible`.
 *
 * @param game Le plateau concerné.
 * @param player Le joueur courant.
 * @param location L'indice de la case à tester.
 *
 * @return `true` si une dame peut être posée sur la case.
 */
static bool is_move_possible(CompactGameState *game, CompactPlayer player, uint location);

/**
 * @brief Vérifie si un mouvement est valide.
 *
 * Cette fonction est appelée par `insert_all_dices`.
 *
 * @param game Le plateau concerné.
 * @param player Le joueur courant.
 * @param move Le mouvement à tester.
 *
 * @return `true` si le mouvement est valide.
 */
static bool is_valide_move(CompactGameState *, CompactPlayer, CompactMove);

/**
 * @brief Vérifie si toutes les dames sont en position pour la sortie du
 * plateau.
 *
 * @param game Le plateau concerné.
 * @param player Le joueur courant.
 *
 * @return `true` si la condition est vérifiée.
 */
static bool all_dames_in_inner_board(CompactGameState *game, CompactPlayer player);

// defines utilisés pour alléger le code suivant.
#define CHECK_FROM_BOARD {if (game->board[from - 1].owner != player) return false;}
#define CHECK_FROM_BAR {if (!game->bar[player]) return false;}

static bool is_valide_move(CompactGameState *game, CompactPlayer player, CompactMove move) {
    uint8_t from = move.src_point,
            to = move.dest_point;

    if (to < 25) {
        // déplacement hors sortie du plateau.
        if (from && !game->bar[player]) {
            // On prend une dame sur le plateau.
            CHECK_FROM_BOARD;
        } else if (!from){
            // On prend une dame sur la barre
            CHECK_FROM_BAR;
        } else {
            return false;
        }
        return is_move_possible(game, player, to);

    } else if (to == 25 && from) {
        // Sortie classique d'une dame.
        CHECK_FROM_BOARD;
        return all_dames_in_inner_board(game, player);

    } else if (to > 25 && from){
        // Sortie d'une dame en utilisant un dé plus grand que nécessaire, par
        // exemple en utilisant un 4 pour sortir une dame sur la dernière case.
        CHECK_FROM_BOARD;
        if (!all_dames_in_inner_board(game, player)) {
            return false;
        }

        // On vérifie qu'il n'y a pas de dame plus éloignée de la sortie.
        for (uint8_t i = 18; i < from - 1; i++) {
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

static bool is_move_possible(CompactGameState *game, CompactPlayer player, uint location) {
    if (game->board[location - 1].owner == player ||
        game->board[location - 1].owner == CNOBODY) {
        return true;
    } else {
        return game->board[location - 1].nbDames < 2;
    }
}

static bool all_dames_in_inner_board(CompactGameState *game, CompactPlayer player) {
    size_t count = game->bar[player];

    for (size_t i = 0; i < 18; i++) {
        if (game->board[i].owner == player) {
            count += game->board[i].nbDames;
        }
    }

    return count == 0;
}

ArrayList *retrieveEveryPossibility(CompactGameState game, CompactPlayer player, const unsigned char dices[2]) {
    /*
     * Dans cette fonction, on met en place la récursion dans
     * `insert_all_dices`.
     */
    if (player == CBLACK) {
        // On normalise le plateau pour simplifier les traitements.
        game = reverse_game(game);
    }

    ArrayList *list = list_new();
    size_t max_nb_dices_used = 0;

    if (dices[0] == dices[1]) {
        // On insère quatre fois le même dé.
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
        // On insère les dés 1 puis 2, puis les dés 2 puis 1.
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

    if (player == CBLACK) {
        list_foreach(list, reverse_moves);
    }
    return list;
}

static size_t insert_all_dices(CompactGameState game,
                               CompactPlayer player,
                               size_t max_nb_dice_used,
                               size_t nb_dices_used,
                               size_t nb_dices,
                               const uc dices[nb_dices],
                               ArrayList *list,
                               AIListMoves moves) {
    /*
     * Pour toutes les cases, on essaye d'utiliser le premier dé à insérer. Si
     * le mouvement est valide, on récurse avec le dé en moins.
     * `max_nb_dice_used` permet de ne pas garder les mouvements qui sont plus
     * courts que le plus long mouvement calculé.
     */
    for (uint8_t i = 0; nb_dices && i <= 24; i++) {
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
        // Si aucun dé n'a été utilisé, on pousse le mouvement précédant la
        // récursion.
        max_nb_dice_used = nb_dices_used;
        list_push(list, moves);
    }

    return max_nb_dice_used;
}
