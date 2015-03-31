#include "AI_tree.h"

#include <stdlib.h>
// size_t

struct AIListPossibilities
{
    AINode* liste_noeuds ;
    //! tableau des noeuds
    
    SMove* liste_mouvements ;
    //! tableau des mouvements
    // Pour aller à la position liste_noeuds[i], il faut faire le mouvement liste_mouvements[i]
    // Par conséquence liste_mouvements a la même taille que liste_noeuds
    
    
    size_t taille ;
    //! taille du tableau des noeuds
};

struct AINode
{
    SGameState etat_jeu ; 
    //! etat du jeu pour un noeud donne
    
    AIListPossibilities liste_possibilites ;
    //! liste des branches (ou noeuds)
    
    int valeur ;
    //! valeur entière de l'etat (plus elevee, plus le joueur a l'avantage & vice versa)    
};

int getValueFromGameState(SGameState etat_jeu, Player player)
{
    // pour une valeur de jeu donnée, renvoie un entier;
    // plus l'entier est grand, plus le joueur est en bonne position
    
}


AIListPossibilities retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] )
{
    // renvoie une liste de toutes les possibilités à partir d'un GameState
    // liste_noeuds doit être egal à NULL dans la structure renvoyée
}




void deleteTree(AINode node)
{
    // efface proprement un arbre
    
    if (node.liste_possibilites.liste_noeuds){
        for (size_t i = 0 ; i < node.liste_possibilites.taille ; i++)
        {
            deleteTree(node.liste_possibilites.liste_noeuds[i]);
            
        }
        free(node.liste_possibilites.liste_noeuds);
    }
    if (node.liste_possibilites.liste_mouvements)
                free(node.liste_possibilites.liste_mouvements);
}


