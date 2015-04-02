#include "AI_tree.h"

struct AIListPossibilities
{    
    AIListMoves* liste_mouvements;
    //! tableau des listes de mouvements
    // Pour aller à la position liste_noeuds[i], il faut faire les mouvements liste_mouvements[i]

    size_t taille ;
    //! taille du tableau des possibilites
};


// structure qui stocke une liste de mouvements faits en 1 tour
struct AIListMoves 
{
    SMove mouvement[4] ;
    // tableau des mouvements, jusqu'à 4 possibles
    
    int nombre_mouvements ;
    // nombre de mouvements viables dans cette structure ( entre 0 et 4)
};

void genererDes(char des[21][2])
{
    int i = 0 ;
    for (int x = 1 ; x <= 6 ; x++)
    {
        for (int y = x ; y <= x ;y++)
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
    
    AIListPossibilities liste_possibilites 
    = retrieveEveryPossibility(etat_jeu,joueur_calcule,des) ;
    if (joueur_calcule == AI_player)
    {
        long v = LONG_MIN ; // equivaut à moins l'infini
        for (int i = 0 ; i < liste_possibilites.taille ; i++)
        {
            
            long alpha_calcul = alphabeta( gameStateFromMovement(etat_jeu, liste_possibilites.liste_mouvements[i]) 
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
        for (int i = 0 ; i < liste_possibilites.taille ; i++)
        {
            long alpha_calcul = alphabeta( gameStateFromMovement(etat_jeu, liste_possibilites.liste_mouvements[i]) 
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

AIListMoves getBestMoves(SGameState etat_jeu, Player player)
{

    AIListMoves moves ;
    moves.nombre_mouvements = 0 ;
    
    return moves ;
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
}

AIListPossibilities retrieveEveryPossibility(SGameState game, Player player, const unsigned char dices[2] )
{
    // renvoie une liste de toutes les possibilités à partir d'un GameState et de dés donnés
    
    AIListPossibilities liste_possibilites ;
    liste_possibilites.taille = 0 ;
    
    // renvoie une liste vide pour l'instant (pour les tests)
    return liste_possibilites ;
}

int isGameFinished( const SGameState etat_jeu)
{
    
    return false ;
}
