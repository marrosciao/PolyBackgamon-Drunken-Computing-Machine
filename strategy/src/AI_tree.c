#include "AI_tree.h"
#include "possibilities.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

Player opposing_player(Player player)
{
    assert(player != NOBODY);
    if (player == WHITE)
        return BLACK ;
    else
        return WHITE ;
}

AIListMoves getBestMoves(SGameState etat_jeu, Player player,const unsigned char dices[2])
{
	AIListMoves moves ;
	ArrayList *liste_possibilites = retrieveEveryPossibility(etat_jeu,player,dices);
	size_t nombre_possibilites = list_size(liste_possibilites);
	int i = rand() % nombre_possibilites ;
	list_get(liste_possibilites,i,&moves);	
	list_free(liste_possibilites);
    return moves ;
}
