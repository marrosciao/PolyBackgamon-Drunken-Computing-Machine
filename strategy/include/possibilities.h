#pragma once

#include <stddef.h>

#include "backgammon.h"
#include "arraylist.h"

typedef unsigned int uint;

ArrayList *retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2]);
