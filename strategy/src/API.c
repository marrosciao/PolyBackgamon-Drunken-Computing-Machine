#include <assert.h>
#include <string.h>

#include "backgammon.h"
#include "AI_main.h"
#include "compact.h"


void InitLibrary(char name[50])
{
    strcpy(name,"La meilleure IA des meilleurs potes");
}

void StartMatch(const unsigned int target_score)
{
    // Non utilis�
}

void StartGame(Player p)
{
    // ai_player est une var globale !
    ai_player = p ;
}

void EndGame()
{
    // Pas de var globale, non utilis�
}

void EndMatch()
{
    // Pas de var globale, non utilis�
}

int DoubleStack(const SGameState * const gameState)
{
	// strat�gie simple : si l'�valuation du plateau nous est TRES favorable
	// on double la mise
    const int value_to_double_stake = 800 ;
    CompactGameState compact_gamestate = gameStateToCompact(*gameState);
    return getValueFromGameState(&compact_gamestate,ai_player) >= value_to_double_stake;
}

int TakeDouble(const SGameState * const gameState)
{
	// strategie toujours simple: 
	// on accepte toujours sauf si on est vraiment en tr�s mauvaise position
    const int value_to_surrender_stake = -1000 ;
    CompactGameState compact_gamestate = gameStateToCompact(*gameState);
    return getValueFromGameState(&compact_gamestate,ai_player) > value_to_surrender_stake;
}

void PlayTurn(const SGameState * const gameStateFat, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{
	assert(gameStateFat);
    CompactGameState gameState = gameStateToCompact(*gameStateFat);
	
	assert(nbMove);
	// ce serait bete de d�r�f�rencer un pointer NULL

    assert(somme_plateau(&gameState,WHITE)==15);
    assert(somme_plateau(&gameState,BLACK)==15);
	// v�rification basique pour voir si on re�oit bien un bon plateau ...

    AIListMoves tmp_moves = getBestMoves(gameState,ai_player,dices);

	for (int i = 0 ; i < 4 ; i++)
	{
		moves[i] = compactToSMove(tmp_moves.mouvement[i]);
	} 

    *nbMove = (unsigned int)tmp_moves.nombre_mouvements ;
    assert(*nbMove<=4);
}
