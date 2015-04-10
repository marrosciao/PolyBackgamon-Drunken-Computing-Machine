#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "backgammon.h"
#include "arraylist.h"
#include <stdbool.h>
#include "compact.h"
// VAR GLOBALE ATTENTION NE PAS TOUCHER !!!!
extern CompactPlayer ai_player ;
//!!!!! !!!!!


uint8_t somme_plateau(const CompactGameState* etat_jeu, CompactPlayer player);
int getValueFromGameState(const CompactGameState* etat_jeu, CompactPlayer player);
void genererDes(unsigned char des[21][2]);
long alphabeta(CompactGameState etat_jeu, int profondeur,int profondeur_initial, long alpha, long beta, CompactPlayer joueur_calcule, CompactPlayer AI_player,AIListMoves *moves,const unsigned char des[2]);
AIListMoves getBestMoves(CompactGameState etat_jeu, CompactPlayer player,const unsigned char dices[2]);
CompactGameState gameStateFromMovement(CompactGameState etat_jeu, AIListMoves mouvements, CompactPlayer player);
bool isGameFinished(const CompactGameState* etat_jeu);
