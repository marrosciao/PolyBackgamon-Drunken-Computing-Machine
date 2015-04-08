#include <assert.h>
#include "utils.h"

SGameState reverse_game(SGameState game) {
    Square board[24];

    for (size_t i = 0; i < 24; i++) {
        board[i] = game.board[23 - i];
    }

    for (size_t i = 0; i < 24; i++) {
        game.board[i] = board[i];
    }

    return game;
}

AIListMoves reverse_moves(AIListMoves moves) {
    for (size_t i = 0; i < moves.nombre_mouvements; i++) {
        if (moves.mouvement[i].src_point > 0) {
            moves.mouvement[i].src_point = 25 - moves.mouvement[i].src_point;
        }
        if (moves.mouvement[i].dest_point < 25) {
            moves.mouvement[i].dest_point = 25 - moves.mouvement[i].dest_point;
        }
    }

    return moves;
}

SGameState apply_move(SGameState game, Player player, SMove move) {
    assert(move.src_point < 25);
    assert(move.dest_point > 0);
    if (move.src_point == 0)
    {
        game.bar[player] -= 1 ;
    }
    else
    {

        game.board[move.src_point-1].nbDames -= 1 ;
        int nbDames = game.board[move.src_point-1].nbDames ;
        assert(nbDames >= 0);

        if(nbDames == 0)
            game.board[move.src_point-1].owner = NOBODY;

    }

    if (move.dest_point == 25)
    {// on sort le pion du plateau (definitif)
        game.out[player] += 1 ;
    }
    else if (game.board[move.dest_point-1].owner!=player && game.board[move.dest_point-1].nbDames == 1)
    {// cas où on mange un pion ennemi
        game.bar[opposing_player(player)] += 1 ;
        game.board[move.dest_point-1].owner = player ;
    }
    else
    {
        game.board[move.dest_point-1].nbDames += 1 ;
        game.board[move.dest_point-1].owner = player ;
    }

    return game;
}

long max_long(long a, long b) {
    return a >= b ? a : b;
}

size_t max_size_t(size_t a, size_t b) {
    return a >= b ? a : b;
}

uint max_uint(uint a, uint b) {
    return a >= b ? a : b;
}

long min_long(long a, long b) {
    return a <= b ? a : b;
}

size_t min_size_t(size_t a, size_t b) {
    return a <= b ? a : b;
}
