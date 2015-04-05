#pragma once

#include <stdlib.h>
// size_t

#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "possibilities.h"
#include "backgammon.h"
#include "arraylist.h"

// VAR GLOBALE ATTENTION NE PAS TOUCHER !!!!
int ai_player ;
//!!!!! !!!!!


int getValueFromGameState(SGameState etat_jeu, Player player);
void genererDes(char des[21][2]);
long alphabeta(SGameState etat_jeu, int profondeur, long alpha, long beta, Player joueur_calcule, Player AI_player,AIListMoves *moves);
AIListMoves getBestMoves(SGameState etat_jeu, Player player,const unsigned char dices[2]);
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements, Player player);
ArrayList *retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] );
bool isGameFinished(SGameState etat_jeu);
