#ifndef _INIT_INCLUDED
#define _INIT_INCLUDED

#include"error.h"
#include"backgammon.h"

/**
 * @file init.h
 * @author Vincent BONNEVALLE
 * @brief Défini les fonctions servant à charger et initialiser les bibliothèques
 */

/**
 * @struct Functions
 * @brief Structure rassemblant les fonctions de l'API.
 *
 * Cette structure sert à faciliter l'initialisation des fonctions : 
 * on passe la structure à une fonction initialisant les pointeurs de fonctions.
 */
typedef struct{
	//! fonction d'initialisation de la stratégie
	pfInitLibrary	initLibrary;
	//! fonction démarant un match
	pfStartMatch	startMatch;
	//! fonction démarant une manche
	pfStartGame		startGame;
	//! fonction terminant une manche
	pfEndGame		endGame;
	//! fonction terminant un match
	pfEndMatch		endMatch;
	//! fonction renvoyant si l'IA double la mise
	pfDoubleStack	doubleStack;
	//! fonction retournant si l'IA accepte de doubler la mise ou abandonne
	pfTakeDouble	takeDouble;
	//! fonction retournant les mouvements à effectuer
	pfPlayTurn		playTurn;
} Functions;

/**
 * @fn void init_func(void* handle, Functions* function, err_func errfunc)
 * @brief Initialise les fonctions de la bibliothèque dynamique
 * @param handle   pointeur sur la bibliothèque dynamique
 * @param function fonctions à initialiser
 * @param errfunc  fonction à appeler en cas d'erreur
 * @warning les appels à dlsym() déclenchent des warnings avec l'option pedantic. Ces warnings sont due à un défaut de conception de dlsym().
 */
void init_func(void*, Functions*, err_func);
/**
 * @fn void init_lib(const char* libPath, void** handle, Functions* func, err_func errfunc)
 * @brief Ouvre la bibliothèque et initialise les fonction
 * @param libPath chemin de la bibliothèque dynamique
 * @param handle  "double" pointeur sur la bibliothèque dynamique.
 * @param func    fonctions à initialiser
 * @param errfunc fonction à appeler en cas d'erreur
 * @warning init_lib n'est pas responsable de la bibliothèque dynamique
 * @warning tout valeur précédante de handle sera perdu (et causera une fuite de mémoire)
 */
void init_lib(const char*, void**, Functions*, err_func);
/**
 * @fn void init_state(SGameState* state)
 * @brief initialise l'état du jeu
 * @param state pointeur sur l'état du jeu
 * @warning init_state n'est pas resopnsable de state
 */
void init_state(SGameState*);

void init_board(SGameState*);
#endif
