#ifndef _REFEREE_INCLUDED
#define _REFEREE_INCLUDED

#include"backgammon.h"

/**
 * @file referee.h
 * @author Vincent BONNEVALLE
 * @brief Défini les fonctions nécessaires au déplacement des pions
 * @todo Vérifier qu'on utilise le max de dés possible (on doit utiliser le max de dé)
 */

//TODO : faire les test (cf CMakeLists.txt)
//TODO : revoir les prototypes pour enlever les paramêtre inutiles
//TODO : revoir les pré/post pour faire plus proche de spec

//! typedef définissant le type d'un dé
typedef const unsigned char Dice;
//! raccourci pour const unsigned int
typedef const unsigned int cuint;
//! raccourci pour unsigned int
typedef unsigned int uint;

/**
 * @fn int check_move(const SMove movement, Dice[] dices, cuint nbDice, const Player player, SGameState * const state)
 * @brief Vérifie la validité du mouvement
 * @param movement mouvement dont on veut vérifier la validité
 * @param dices    valeur du lancé de dés
 * @param nbDice   nombre de dés lancé
 * @param player   joueur dont on veut vérifier les mouvements
 * @param state    état du jeux
 * @return 0 -> pas d'erreur, 1 -> le mouvement est invalide
 */
int check_move(const SMove, Dice[], cuint, const Player, SGameState const * const);

int check_number_dices(const SGameState * const, Dice[], cuint, const Player);

/**
 * @fn int check_side(SGameState const * const state, const Player player)
 * @brief Vérifie qu'on peut mettre un pion dans la zone de fin
 * @param state  Etat du jeux
 * @param player joueur courant
 * @return true -> pas d'erreur, false -> on ne peut pas sortir de pion
 */
int check_side(SGameState const * const, const Player);

/**
 * @fn int move_all(SGameState * const state, SMove const * const moves, cuint nb_moves, Dice dices[], cuint nb_dices, const Player player)
 * @brief Déplace les pions selon les mouvements (valide) passé en paramêtre
 * @param state    état du jeux
 * @param moves    liste des mouvements à effectuer
 * @param nb_moves nombre de mouvement à effectuer
 * @param dices    valeur du lancé des dés
 * @param nb_dices nombre de dés lancé
 * @param player   joueur dont c'est le tour
 * @return nombre de mouvement faux
 */
int move_all(SGameState * const, SMove const * const, cuint, Dice[], cuint, const Player);

/**
 * @fn void move(SGameState * const state, SMove const move, const Player player)
 * @brief Déplace un pion
 * @param state  état du jeu
 * @param move   mouvement à effectuer
 * @param player joueur en train de jouer
 * @pre le mouvement est valide
 */
void move(SGameState * const, SMove const, const Player);
/**
 * @fn void move_from_out(SGameState* const state, SMove const move, const Player player)
 * @brief Déplace un pion de la zone "out" à une case
 * @param state  état du jeu
 * @param move   mouvement à effectuer
 * @param player joueur en train de jouer
 * @pre le mouvement est valide
 */
void move_from_out(SGameState * const state, SMove const, const Player);
/**
 * @fn void move_to_end(SGameState* const state, SMove const move, const Player player)
 * @brief déplace un pion dans la zone de fin
 * @param state  état du jeu
 * @param move   mouvement à effectuer
 * @param player joueur en train de jouer
 * @pre le mouvement est valide
 */
void move_to_end(SGameState * const, SMove const, const Player);
/**
 * @fn void move_in_board(SGameState* const state, SMove const move, const Player player)
 * @brief déplace un pion d'une cas à une autre
 * @param state  état du jeu
 * @param move   mouvement à effectuer
 * @param player joueur en train de jouer
 * @pre le mouvement est valide
 */
void move_in_board(SGameState * const, SMove const, const Player);

/**
 * @fn void put_on(Square board[24], uint out[2], cuint dest, const Player player)
 * @brief ajoute un pion dans la case
 * @param board  plateau de jeu
 * @param out    zone "out" pour mettre les pions adverse si ils sont mangé
 * @param dest   case dans laquelle il faut mettre le pion
 * @param player joueur en train de jouer
 * @pre le mouvement est valide
 *
 */
void put_on(Square[24], uint[2], cuint, const Player);
/**
 * @fn void take_from(Square[24] board, cuint source)
 * @brief enleve un pion d'une case
 * @param board  plateau de jeu
 * @param source case ou il faut enlever le pion
 * @pre le mouvement est valide
 */
void take_from(Square[24], cuint);

#endif
