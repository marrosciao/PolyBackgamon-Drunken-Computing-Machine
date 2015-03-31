#include <stdbool.h>
#include <string.h>

#include "backgammon.h"

void InitLibrary(char name[50])
{
    
    strcpy(name,"La meilleure IA des meilleurs potes");

    // Code d'initialisation ici.
}

void StartMatch(const unsigned int target_score)
{
    // TODO : pitetre stocker target_score dans une var globale ?
}

void StartGame(Player p)
{

}

void EndGame()
{

}

void EndMatch()
{

}

void DoubleStack(const SGameState * const gameState)
{
    // on ne double jamais la mise en debut de tour
    return false ;
}

int TakeDouble(const SGameState * const gameState)
{
    // on accepte toujours le videau
    return true ;
}

void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{
    // TODO : prog l'IA

    // pour l'instant elle ne fait aucun mouvement jusqu'à ce qu'elle perde
    *nbMove = 0 ;
}
