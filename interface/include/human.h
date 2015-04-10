#ifndef HUMAN
#define HUMAN

#include "backgammon.h"
#include <SDL/SDL.h>
#include "init.h"

void InitLibrary(char name[50]);
void StartMatch(const unsigned int target_score);
void StartGame(Player p);
/**
 * @fn Functions* StartScreen(SDL_Surface* s)
 * @brief Permet de communiquer l'ecran sur lequel est affiché le jeu pour que le joueur humain
aie accès à l'interface graphique, de plus, revoie des pointeurs vers toutes les fonctions qu'iutilisera l'IA, pour ne pas avoir à faire de libraire pour ce joueur "special"
 * @param s     l'ecran que l'on communique au joueur
 * @return renvoie un pointeur vers toutes autres fonctions de human, qui fonctionnent toutes exactement comme des fonctions d'une IA normale 
 */
Functions* StartScreen(SDL_Surface* s);
void EndGame();
void EndMatch();
int DoubleStack(const SGameState * const gameState);
int TakeDouble(const SGameState * const gameState);
void PlayTurn( SGameState const * const  gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries);

#endif
