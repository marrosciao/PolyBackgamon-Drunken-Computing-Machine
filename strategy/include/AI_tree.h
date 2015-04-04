#pragma once

#include <stdlib.h>
// size_t

#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "backgammon.h"
#include "arraylist.h"

int getValueFromGameState(SGameState etat_jeu, Player player);
void genererDes(char des[21][2]);
long alphabeta(SGameState etat_jeu, int profondeur, long alpha, long beta, Player joueur_calcule, Player AI_player);
ArrayList *getBestMoves(SGameState etat_jeu, Player player);
int getValueFromGameState(SGameState etat_jeu, Player player);
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements);
ArrayList *retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] );
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements);
bool isGameFinished(SGameState etat_jeu);
