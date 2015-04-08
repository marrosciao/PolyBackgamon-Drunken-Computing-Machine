#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "backgammon.h"
#include "arraylist.h"

// VAR GLOBALE ATTENTION NE PAS TOUCHER !!!!
extern Player ai_player ;
//!!!!! !!!!!

AIListMoves getBestMoves(SGameState etat_jeu, Player player,const unsigned char dices[2]);
SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements, Player player);
bool isGameFinished(SGameState etat_jeu);
