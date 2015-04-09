
#pragma once
#include <stdint.h>
#include "backgammon.h"
/**
 * @brief Définit le contenu d'une case de jeu.
 */
typedef struct {
    Player owner;           /*!<  Joueur contrôlant la case */
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



