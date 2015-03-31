#include "AI_tree.h"

#include <stdlib.h>
// size_t

struct AIListNodes
{
    AINode* liste ;
    //! tableau des noeuds
    
    size_t taille ;
    //! taille du tableau des noeuds
};

struct AINode
{
    SGameState etat_jeu ; 
    //! etat du jeu pour un noeud donne
    
    AIListNodes liste_noeuds ;
    //! liste des branches (ou noeuds)
    
    int valeur ;
    //! valeur entière de l'etat (plus elevee, plus le joueur a l'avantage & vice versa)    
};

int getValueFromGameState(SGameState etat_jeu, Player player)
{
    // pour une valeur de jeu donnée, renvoie un entier;
    // plus l'entier est grand, plus le joueur est en bonne position
    
}


AIListNodes retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] )
{
    // renvoie une liste de toutes les possibilités à partir d'un GameState

}




void deleteTree(AINode node)
{
    // efface proprement un arbre
    
    if (node.liste_noeuds.liste){
        for (size_t i = 0 ; i < node.liste_noeuds.taille ; i++)
        {
            deleteTree(node.liste_noeuds.liste[i]);
        }
        free(node.liste_noeuds.liste);
    }
}


