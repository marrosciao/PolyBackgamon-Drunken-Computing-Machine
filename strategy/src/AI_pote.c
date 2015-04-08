#include <stdbool.h>
#include <string.h>

#include "backgammon.h"
#include "AI_tree.h"


void InitLibrary(char name[50])
{
    
    strcpy(name,"La meilleure IA des meilleurs potes");

    // Code d'initialisation ici.

	// Sauf qu'on a pas d'intialisation à faire vu notre algorithme
	// Tout va bien
}

void StartMatch(const unsigned int target_score)
{
    // Non utilisé
}

void StartGame(Player p)
{
	// ai_player est une var globale !
	ai_player = p ;
}

void EndGame()
{
	// Pas de var globale, non utilisé	
}

void EndMatch()
{
	// Pas de var globale, non utilisé
}

int DoubleStack(const SGameState * const gameState)
{
	return false ;
}

int TakeDouble(const SGameState * const gameState)
{
	return true ;
}

void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{
    
	AIListMoves tmp_moves = getBestMoves(*gameState,ai_player,dices);
    
	moves[0] = tmp_moves.mouvement[0] ;
	moves[1] = tmp_moves.mouvement[1] ;
	moves[2] = tmp_moves.mouvement[2] ;
	moves[3] = tmp_moves.mouvement[3] ;
	// la flemme d'utiliser memcpy pour 4 lignes

    *nbMove = tmp_moves.nombre_mouvements ;
    assert(0<=tmp_moves.nombre_mouvements && tmp_moves.nombre_mouvements<=4);
    assert(0<=*nbMove && *nbMove<=4);
}
