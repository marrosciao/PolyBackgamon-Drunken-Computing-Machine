#include "AI_tree.h"

struct AIListPossibilities
{    
    SMove* liste_mouvements[4] ;
    //! tableau des tableaux des mouvements
    // Pour aller à la position liste_noeuds[i], il faut faire le mouvement liste_mouvements[i]
    // Par conséquence liste_mouvements a la même taille que liste_noeuds
    
    int* nombre_mouvements ;
    //! nombre de mouvements créés pour arriver au noeud (entre 1 et 4)
    
    
    size_t taille ;
    //! taille du tableau des noeuds
};

int getValueFromGameState(SGameState etat_jeu, Player player)
{
    // pour une valeur de jeu donnée, renvoie un entier;
    // plus l'entier est grand, plus le joueur est en bonne position
}

SGameState gameStateFromMovement(SGameState etat_jeu, SMove moves[4], size_t nombre_mouvements)
{
    // a partir d'un etat de jeu et de mouvements définis, renvoie un autre etat de jeux.
}

AIListPossibilities retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] )
{
    // renvoie une liste de toutes les possibilités à partir d'un GameState
    // liste_noeuds doit être egal à NULL dans la structure renvoyée
}

