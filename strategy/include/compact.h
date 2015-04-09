
#pragma once
#include <stdint.h>
#include "backgammon.h"
#include <stdint.h>


// C'est sale, mais ça fait l'équivalent d'un enum
typedef uint8_t CompactPlayer ;
static const CompactPlayer CNOBODY = -1 ;
static const CompactPlayer CBLACK = 0 ;
static const CompactPlayer CWHITE = 1 ;

/*
// On essaye de faire un enum ne prenant qu'un seule byte au lieu de 4 (pour l'alignement)
// problème : ne marche pas
typedef enum
{
	CNOBODY = -1 ,
	CBLACK = 0 ,
	CWHITE = 1
} CompactPlayer __attribute__ ((packed));
*/


/**
 * @brief Définit le contenu d'une case de jeu.
 */
typedef struct {
    CompactPlayer owner;           /*!<  Joueur contrôlant la case */
    uint8_t nbDames;   /*!<  Nombre de dames sur la case (non utilisé si
                                  `owner == NOBODY.`) */
} CompactSquare;


/**
 * @brief Contient toutes les informations relatives à une partie en cours.
 *
 * Une struct contenant toutes les informations du jeu permet des tests plus
 * faciles.
 */
typedef struct {
    CompactSquare board[24];           /*!< Les 24 cases du tableau, en partant du bord blanc. */
    uint8_t bar[2];
    uint8_t out[2];
    unsigned int whiteScore;    /*!< Score du joueur blanc */
    unsigned int blackScore;    /*!< Score du joueur noir */
    unsigned int turn;          /*!< Numéro du tour en cours (initialisé à 0) */
    unsigned int stake;            /*!< Mise courante de la partie */
} CompactGameState;

// Structure de représentation d'un mouvement
typedef struct
{
    uint8_t src_point;
    uint8_t dest_point;
} CompactMove;

CompactGameState gameStateToCompact(SGameState gamestate);
SMove compactToSMove(CompactMove move);



