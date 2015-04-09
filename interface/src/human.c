#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>

#include "backgammon.h"
#include "graph.h"
#include "init.h"
#include "human.h"

Player color;
SDL_Surface* screen;

void InitLibrary(char name[50])
{

    strcpy(name,"Joueur Humain");

    // Code d'initialisation ici.

    // Sauf qu'on a pas d'intialisation à faire vu notre algorithme
    // Tout va bien
}

void StartMatch(const unsigned int target_score)
{
    // Non utilisé
}

void StartGame(Player p)
{
    // ai_player est une var globale !
    color = p ;
}

Functions* StartScreen(SDL_Surface* s)
{
	screen = s;
    Functions* func = malloc(sizeof(Functions));
    func->initLibrary = InitLibrary;
    func->startMatch  = StartMatch;
    func->startGame   = StartGame;
    func->endGame     = EndGame;
    func->endMatch    = EndMatch;
    func->doubleStack = DoubleStack;
    func->takeDouble  = TakeDouble;
    func->playTurn    = PlayTurn;
    return func;   
}

void EndGame()
{
    // Pas de var globale, non utilisé
}

void EndMatch()
{
    // Pas de var globale, non utilisé
}

int DoubleStack(const SGameState * const gameState)
{
    return false;
}

int TakeDouble(const SGameState * const gameState)
{
    return true;
}

void PlayTurn( SGameState *  state, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries){
    int nbMoves = dices[0] == dices[1] ? 4 : 2;
    *nbMove = nbMoves;
    SGameState* gameState = state;
    char coup[] = "0 COUPS RESTANTS";
    //SDL_Color blanc = {
    //    .r = 100,
    //    .g = 100,
    //    .b = 100,
    //};
    SDL_Color noir = {
        .r = 0,
        .g = 0,
        .b = 0,
    };

    for (int i=0; i<nbMoves; i++){
        coup[0] = nbMoves-i +48;
        printtext(630, 290, "./Textures/CowboyMovie.ttf",50,coup,noir, screen);
        if (color == WHITE)
            printtext(230, 290, "./Textures/CowboyMovie.ttf",50,"AU TOUR DES BLANCS",noir, screen);
        if (color == BLACK)
            printtext(230, 290, "./Textures/CowboyMovie.ttf",50,"AU TOUR DES NOIRS",noir, screen);
        SDL_Flip(screen);
        moves[i].src_point= selectPion(gameState,screen,true,color);
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        SDL_Flip(screen);
        moves[i].dest_point = selectPion(gameState,screen,false,color);
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        SDL_Flip(screen);
    }

}
