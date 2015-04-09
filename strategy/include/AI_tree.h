#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "backgammon.h"
#include "arraylist.h"

// VAR GLOBALE ATTENTION NE PAS TOUCHER !!!!
extern Player ai_player ;
//!!!!! !!!!!


unsigned int somme_plateau(const SGameState* etat_jeu, Player player);
int getValueFromGameState(const SGameState* etat_jeu, Player player);
void genererDes(unsigned char des[21][2]);
long alphabeta(SGameState etat_jeu, int profondeur,int profondeur_initial, long alpha, long beta, Player joueur_calcule, Player AI_player,AIListMoves *moves,const unsigned char des[2]);
AIListMoves getBestMoves(SGameState etat_jeu, Player player,const unsigned char dices[2]);
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements, Player player);
bool isGameFinished(const SGameState* etat_jeu);
