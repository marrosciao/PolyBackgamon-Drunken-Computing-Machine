#include "AI_tree.h"
#include "possibilities.h"

void genererDes(char des[2][2])
{
    size_t i = 0 ;
    for (size_t x = 1 ; x <= 6 ; x++)
    {
        for (size_t y = x ; y <= x ;y++)
        {
            des[++i][0] = x ;
            des[i][0] = y ;
        } 
    }
    // renvoie toutes les combinaisosn de des possibles
     
}

long alphabeta(SGameState etat_jeu, int profondeur, long alpha, long beta, Player joueur_calcule, Player AI_player) 
{
    if (profondeur == 0 || isGameFinished(etat_jeu))
        return getValueFromGameState(etat_jeu, AI_player) ;
    
    char des[2] ;
    des[0] = 2 ; des[0] = 3 ;
    // des test pour l'instant
    
    ArrayList *liste_possibilites = retrieveEveryPossibility(etat_jeu,joueur_calcule,des);
    if (joueur_calcule == AI_player)
    {
        long v = LONG_MIN ; // equivaut à moins l'infini
        for (size_t i = 0 ; i < list_size(liste_possibilites) ; i++)
        {
            AIListMoves moves;
            list_get(liste_possibilites, i, &moves);
            long alpha_calcul = alphabeta( gameStateFromMovement(etat_jeu, moves)
                                    ,profondeur - 1 
                                    ,alpha
                                    ,beta
                                    ,(joueur_calcule == BLACK)?WHITE:BLACK
                                    ,AI_player);
            if (v < alpha_calcul)
                v = alpha_calcul ;
            if (v > alpha)
                alpha = v ;  
            if (beta >= alpha)
                break;
            
        }
        return v ;
    }
    else
    {
        long v = LONG_MAX ; // equivaut à plus l'infini
        for (size_t i = 0 ; i < list_size(liste_possibilites) ; i++)
        {
            AIListMoves moves;
            list_get(liste_possibilites, i, &moves);
            long alpha_calcul = alphabeta( gameStateFromMovement(etat_jeu, moves)
                                    ,profondeur - 1 
                                    ,alpha
                                    ,beta
                                    ,(joueur_calcule == BLACK)?WHITE:BLACK
                                    ,AI_player);
            if (v > alpha_calcul)
                v = alpha_calcul ;
            if (v < beta)
                beta = v ;  
            if (beta <= alpha)
                break;
            
        }
        return v ;
    }
}

ArrayList *getBestMoves(SGameState etat_jeu, Player player)
{
    return list_new();
}

int getValueFromGameState(SGameState etat_jeu, Player player)
{
    // pour une valeur de jeu donnée, renvoie un entier;
    // plus l'entier est grand, plus le joueur est en bonne position
    return 0 ;
}

SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements)
{
    // a partir d'un etat de jeu et de mouvements définis, renvoie un autre etat de jeux.
    // TODO: FIXME !!!
    return (SGameState) {};
}

bool isGameFinished(SGameState etat_jeu)
{
    return false ;
}
