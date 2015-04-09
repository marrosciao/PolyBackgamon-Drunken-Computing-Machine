#include "backgammon.h"
#include "compact.h"

CompactGameState gameStateToCompact(SGameState gamestate)
{
    CompactGameState compact_gamestate =
    {
        .bar[0]=(uint8_t)gamestate.bar[0],
        .bar[1]=(uint8_t)gamestate.bar[1],
        .whiteScore = gamestate.out[0],
        .blackScore = gamestate.out[1],
        .turn = gamestate.turn,
        .stake = gamestate.stake,
    };
    for (int i = 0 ; i < 24 ; i++)
    {
        compact_gamestate.board[i] = (CompactSquare){
            .owner = gamestate.board[i].owner,
            .nbDames = (uint8_t)gamestate.board[i].nbDames

        };
    }
    return compact_gamestate ;
}

SMove compactToSMove(CompactMove move)
{
    return (SMove){
        .src_point = (unsigned int) move.src_point,
        .dest_point = (unsigned int) move.dest_point
    };
}

