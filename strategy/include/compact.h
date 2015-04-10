
#pragma once
#include <stdint.h>
#include "backgammon.h"
#include <stdint.h>

/*	le but de ce fichier est de réduire les tailles des structures, pour réduire la place mémoire qu'elles prennent
	quand la profondeur est élevée, la place mémoire prise est gigantesque
	il faut faire toutes les optimisations nécessaires pour réduire la mémoire utilisée
*/

// On essaye de faire un enum ne prenant qu'un seule byte au lieu de 4
typedef enum __attribute__ ((packed)) 
{
	CNOBODY = -1 ,
	CBLACK = 0 ,
	CWHITE = 1
} CompactPlayer;



/**
 * @brief Définit le contenu d'une case de jeu.
 */
typedef struct __attribute__ ((packed)) {
    CompactPlayer owner;           /*!<  Joueur contrôlant la case */
    uint8_t nbDames;   /*!<  Nombre de dames sur la case (non utilisé si
                                  `owner == NOBODY.`) */
} CompactSquare ;


/**
 * @brief Contient toutes les informations relatives à une partie en cours.
 *
 * Une struct contenant toutes les informations du jeu permet des tests plus
 * faciles.
 */
typedef struct __attribute__ ((packed))  {
    CompactSquare board[24];           /*!< Les 24 cases du tableau, en partant du bord blanc. */
    uint8_t bar[2];
    uint8_t out[2];
    unsigned int whiteScore;    /*!< Score du joueur blanc */
    unsigned int blackScore;    /*!< Score du joueur noir */
    unsigned int turn;          /*!< Numéro du tour en cours (initialisé à 0) */
    unsigned int stake;            /*!< Mise courante de la partie */
} CompactGameState;

// Structure de représentation d'un mouvement
typedef struct __attribute__ ((packed)) 
{
    uint8_t src_point;
    uint8_t dest_point;
} CompactMove;

CompactGameState gameStateToCompact(SGameState gamestate);
SMove compactToSMove(CompactMove move);



