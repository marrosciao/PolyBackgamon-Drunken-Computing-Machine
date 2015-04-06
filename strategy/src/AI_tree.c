#include "AI_tree.h"
#include <math.h>

long moyenne(long alpha_valeurs[21])
{
	long alpha = 0;

	// MOYENNE
	
	for (int i = 0 ; i < 21 ; i++)
	{
		alpha += alpha_valeurs[i] ;
	}

	alpha = alpha / 21 ;

	// DISTANCE D'EUCLIDE

	/*
	for (int i = 0 ; i < 21 ; i++)
	{
		alpha += alpha_valeurs[i] * alpha_valeurs[i] ;
	}
	alpha = (long) sqrt(alpha);
	*/

	return alpha;
}

void genererDes(unsigned char des[21][2])
{
    size_t i = 0 ;
    for (size_t x = 1 ; x <= 6 ; x++)
    {
        for (size_t y = x ; y <= 6 ;y++)
        {
            des[i][0] = x ;
            des[i++][1] = y ;
        } 
    }
    // renvoie toutes les combinaisosn de des possibles
     
}

long alphabeta(SGameState etat_jeu, int profondeur, long alpha, long beta, Player joueur_calcule, Player AI_player,AIListMoves *moves , const unsigned char des[2]) 
{
    assert(joueur_calcule >= 0);
    // on verifie que le joueur duquel on se place est correct ...

    assert(AI_player >= 0);
    // on verifie aussi que notre AI est correcte ...

    assert(moves);
    // que le pointeur de moves != NULL (sinon difficile de d'affecter une valeur à l'adresse NULL)

    assert(des[0] >= 1 && des[0] <= 6 && des[1] >= 1 && des[1] <= 6 );
    // on verifie que les dés envoyés sont valides

    if (profondeur == 0 || isGameFinished(etat_jeu))
        return getValueFromGameState(etat_jeu, AI_player) ;
    
    unsigned char toutes_combinaisons_des[21][2] ;
	genererDes(toutes_combinaisons_des);
    // on genere toutes les combinaisons de des possibles pour la suite

    ArrayList *liste_possibilites = retrieveEveryPossibility(etat_jeu,joueur_calcule,des);
    assert(liste_possibilites);

    long v;

    if (joueur_calcule == AI_player)
    {
        v = LONG_MIN ; // equivaut à moins l'infini
        for (size_t i = 0 ; i < list_size(liste_possibilites) ; i++)
        {
            AIListMoves temp_moves;
            list_get(liste_possibilites, i, &temp_moves);
            long alpha_valeurs[21] ;
            // les valeurs de alpha-beta pour chaque combinaison de dé
            // par la suite on fera la moyenne de ces valeurs

			for ( int combinaison_de = 0 ; combinaison_de < 21 ; combinaison_de++)
			{
                unsigned char set_de_actuel[2] ;
                memcpy(set_de_actuel,toutes_combinaisons_des,2*sizeof(set_de_actuel[0]));
                // set de dés utilisés pour le calcul ; i.e. (1,2) ou (5,6) ou (6,6) ...

				alpha_valeurs[combinaison_de] = alphabeta(	gameStateFromMovement(etat_jeu, temp_moves, joueur_calcule)
											,profondeur - 1 
											,alpha
											,beta
											,(joueur_calcule == BLACK)?WHITE:BLACK
											,AI_player
											,moves
											,set_de_actuel);
			}
			long alpha_calcul = moyenne(alpha_valeurs);

            if (v < alpha_calcul)
			{
				*moves = temp_moves ;
                v = alpha_calcul ;
			}
            if (v > alpha)
                alpha = v ;  
            if (beta >= alpha)
                break;
            
        }
    }
    else
    {
        v = LONG_MAX ; // equivaut à plus l'infini
        for (size_t i = 0 ; i < list_size(liste_possibilites) ; i++)
        {
            AIListMoves temp_moves;
            list_get(liste_possibilites, i, &temp_moves);
			long alpha_valeurs[21] ;
			for ( int combinaison_de = 0 ; combinaison_de < 21 ; combinaison_de++)
			{
				unsigned char set_de_actuel[2] ;
                *set_de_actuel = *toutes_combinaisons_des[combinaison_de];
                // set de dés utilisés pour le calcul ; i.e. (1,2) ou (5,6) ou (6,6) ...

				alpha_valeurs[combinaison_de] = alphabeta(	gameStateFromMovement(etat_jeu, temp_moves, joueur_calcule)
											,profondeur - 1 
											,alpha
											,beta
											,(joueur_calcule == BLACK)?WHITE:BLACK
											,AI_player
											,moves
											,set_de_actuel);
			}
			long alpha_calcul = moyenne(alpha_valeurs);
            if (v > alpha_calcul)
			{
				*moves = temp_moves ;
                v = alpha_calcul ;
			}
            if (v < beta)
                beta = v ;  
            if (beta <= alpha)
                break;
            
        }
    }

    list_free(liste_possibilites);
    return v;
}

// objectif : a partir d'un GameState, trouver le meilleur set de mouvement
AIListMoves getBestMoves(SGameState etat_jeu, Player player,const unsigned char dices[2])
{
	/*
	solution : algorithme alpha beta
	similaire à l'algorithme minimax
	principe : on calcule toutes les possibilités jusqu'à une profondeur donnée
	a chaque feuille (noeud final), on retourne une valeur qui decrit en un entier l'etat du joueur
	plus elle est élevée, plus le joueur se porte bien dans la partie
	plus elle est faible, plus le joueur se trouve dans une position non avantageuse

	on cherche à maximiser nos gains et minimiser ceux de l'adversaire

	minimax cherche à toujours prendre le chemin le plus sur;
	on part du principe que l'ennemi fait toujours le meilleur choix
	
	alphabeta est une version améliorée de minimax qui évite de calculer toutes les branches,
	si l'une des branches aboutit sur une valeur plus faible qu'une branche frère antérieure, 
	on arrete le calcul pour ce set de branche
	(plus de détail sur l'algorithme : chercher AlphaBeta Pruning sur un moteur de recherche)
	*/


	AIListMoves moves ;
	// appel theorique de alphabeta : alphabeta(Noeud,profondeur_de_base,-infini,+infini)
	alphabeta(	etat_jeu, // etat du jeu courant, necessaire pour calculer les possibilites
				3, // profondeur de calcul souhaité, attention, augmenter de 1 peut prendre beaucou plus de temps!
				LONG_MIN, // moins l'infini version machine
				LONG_MAX, // plus l'infini version machine
				player, // quel joueur nous sommes
				player, // quel joueur nous simulons le tour de jeu (au debut, nous, apr_s, l'adversaire)
				&moves,// il faut bien recuperer les mouvements qu'on a fait au final, c'est en envoyant ce pointeur qu'on le fait
				dices);// dés à disposition
	// 
    return moves ;
}



// pour un etat de jeu donné, renvoie un entier decrivant l'état du joueur player
// plus il est élevé, plus le joueur est dans une bonne position
// les états sont normalement symétriques 
int getValueFromGameState(SGameState etat_jeu, Player player)
{

	const int BAR_VALUE = -5 ; 
	const int OUT_VALUE = 35 ;
	const int INPLAY_VALUE_BASE = 0 ;
	const int INPLAY_VALUE_DELTA = 1 ;

	int heuristic_value = 0 ;
	// calcul de la valeur heuristique en partant du principe qu'on est le joueur WHITE
	// (on multipliera par -1 si on est en réalité le joueur BLACK) 

	heuristic_value += etat_jeu.bar[WHITE]* BAR_VALUE;	
	heuristic_value -= etat_jeu.bar[BLACK]* BAR_VALUE;
	// prise en compte des pions sur la barre verticale

	heuristic_value += etat_jeu.out[WHITE]* OUT_VALUE;	
	heuristic_value -= etat_jeu.out[BLACK]* OUT_VALUE;
	// prise en compte des pions sortis du jeu

	for (int i = 0 ; i < 24 ; i++)
	{
		Square current_square = etat_jeu.board[i] ;
		if (current_square.owner == WHITE)
		{
			heuristic_value += current_square.nbDames * (INPLAY_VALUE_BASE + ((i+1) * INPLAY_VALUE_DELTA));	
		}
		else if (current_square.owner == BLACK)
		{
			heuristic_value -= current_square.nbDames * (INPLAY_VALUE_BASE + ((24-i) * INPLAY_VALUE_DELTA));
		}
	}

	if (player == BLACK)
		heuristic_value *= -1; 
    
    return heuristic_value ;
}

SGameState gameStateFromMovement(SGameState etat_jeu, AIListMoves mouvements,Player player)
{
    // a partir d'un etat de jeu et de mouvements définis, renvoie un autre etat de jeux.
	// WARNING : CELA NE VERIFIE PAS QUE LE MOUVEMENT EST VALIDE !
	// A UTILISER AVEC PARCIMONIE !

	for (size_t i = 0 ; i < mouvements.nombre_mouvements ; i++)
	{
		SMove current_move = mouvements.mouvement[i] ;
		if (current_move.src_point == 0 || current_move.src_point == 25)
		{
			etat_jeu.bar[player] -= 1 ;
		}
		else
		{

            etat_jeu.board[current_move.src_point-1].nbDames -= 1 ;
			int nbDames = etat_jeu.board[current_move.src_point-1].nbDames ;
            assert(nbDames >= 0);

			if(nbDames == 0)
				etat_jeu.board[current_move.src_point-1].owner = NOBODY;
			
		}

		if (current_move.dest_point == 0 || current_move.dest_point == 25)
		{
			etat_jeu.out[player] += 1 ;
		}
		else
		{
			
			etat_jeu.board[current_move.dest_point-1].nbDames += 1 ;
			etat_jeu.board[current_move.dest_point-1].owner = player ;
		}

	
	}

    return etat_jeu;
}

bool isGameFinished(SGameState etat_jeu)
{
    return (etat_jeu.out[WHITE] >= 15 || etat_jeu.out[BLACK] >= 15 ) ;
}
