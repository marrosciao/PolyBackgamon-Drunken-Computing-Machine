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
Player ai_player ;
//!!!!! !!!!!

AIListMoves getBestMoves(SGameState etat_jeu, Player player,const unsigned char dices[2]);
Player opposing_player(Player player);
