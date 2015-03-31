#include "backgammon.h"
#include <stdlib.h>
// size_t

typedef struct AIListPossibilities AIListPossibilities ;

int getValueFromGameState(SGameState etat_jeu, Player player);
AIListPossibilities retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] );
SGameState gameStateFromMovement(SGameState etat_jeu, SMove moves[4], size_t nombre_mouvements);
