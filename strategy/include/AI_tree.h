#include "backgammon.h"



typedef struct AINode AINode ;
// pour un noeud donné, stocke la liste de tous les eventuels sous noeuds possible
// stocke un etat de board donné
// stocke un entier, la "valeur" du board, plus elle est élevée, plus le joueur est dans un etat avantageux

typedef struct AIListPossibilities AIListPossibilities ;

int getValueFromGameState(SGameState etat_jeu, Player player);
AIListPossibilities retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] );
void deleteTree(AINode node);
