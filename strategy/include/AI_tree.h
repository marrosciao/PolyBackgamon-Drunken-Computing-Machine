#pragma once

#include <stdlib.h>
// size_t

#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "backgammon.h"
#include "arraylist.h"

typedef struct AIListPossibilities AIListPossibilities ;
typedef struct AIListMoves AIListMoves ;

int getValueFromGameState(SGameState etat_jeu, Player player);
void genererDes(char des[21][2]);
long alphabeta(SGameState etat_jeu, int profondeur, long alpha, long beta, Player joueur_calcule, Player AI_player);
AIListMoves getBestMoves(SGameState etat_jeu, Player player);
int getValueFromGameState(SGameState etat_jeu, Player player);
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements);
AIListPossibilities retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] );
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements);
int isGameFinished( const SGameState etat_jeu);
