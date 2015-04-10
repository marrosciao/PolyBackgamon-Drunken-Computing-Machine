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
    fprintf(stderr,"couleur = %d",color);
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
    int dobble = false;
    int continuer = 1;
    SDL_Event event;
    SDL_Color noir = {
        .r = 31,
        .g = 15,
        .b = 10,
    };
    drawBackground(screen);  
    drawBoard(gameState, screen);
    if (color == WHITE)
        printtext(230, 283, "./Textures/CarnevaleeFreakshow.ttf",39,"AU TOUR DES BLANCS",noir, screen);
    if (color == BLACK)
        printtext(230, 283, "./Textures/CarnevaleeFreakshow.ttf",39,"AU TOUR DES NOIRS",noir, screen);
    printtext(630, 266, "./Textures/CarnevaleeFreakshow.ttf",39,"Doubler le Videau?",noir, screen);
    printtext(630, 306, "./Textures/CarnevaleeFreakshow.ttf",39,"o:oui    n:non",noir, screen);
    SDL_Flip(screen);
    while (continuer){
        SDL_Rect pos;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                endGraph();
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_o){
                    dobble = true;
                    continuer = 0;
                }
                if(event.key.keysym.sym == SDLK_n){
                    dobble = false;
                    continuer = 0;
                }
                break;
        }
    }
    drawBackground(screen);  
    drawBoard(gameState, screen);
    SDL_Flip(screen);
    return dobble;
}

int TakeDouble(const SGameState * const gameState)
{
    
    int dobble = false;
    int continuer = 1;
    SDL_Event event;
    SDL_Color noir = {
        .r = 31,
        .g = 15,
        .b = 10,
    };
    drawBackground(screen);  
    drawBoard(gameState, screen);
    printtext(630, 266, "./Textures/CarnevaleeFreakshow.ttf",39,"Accepter le Videau?",noir, screen);
    printtext(630, 306, "./Textures/CarnevaleeFreakshow.ttf",39,"o:oui    n:non",noir, screen);
    SDL_Flip(screen);
    while (continuer){
        SDL_Rect pos;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                endGraph();
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_o){
                    dobble = true;
                    continuer = 0;
                }
                if(event.key.keysym.sym == SDLK_n){
                    dobble = false;
                    continuer = 0;
                }
                break;
        }
    }
    drawBackground(screen);  
    drawBoard(gameState, screen);
    SDL_Flip(screen);
    return dobble;

}

void PlayTurn( SGameState *  state, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries){
    int nbMoves = dices[0] == dices[1] ? 4 : 2;
    *nbMove = nbMoves;
    SGameState* gameState = state;
    char coup[] = "coups restants : 0";
    //SDL_Color blanc = {
    //    .r = 255,
    //    .g = 255,
    //    .b = 255,
    //};
    SDL_Color noir = {
        .r = 31,
        .g = 15,
        .b = 10,
    };

    for (int i=0; i<nbMoves; i++){
        coup[17] = nbMoves-i +48;
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        printtext(630, 283, "./Textures/CarnevaleeFreakshow.ttf",39,coup,noir, screen);
        if (color == WHITE)
            printtext(230, 283, "./Textures/CarnevaleeFreakshow.ttf",39,"AU TOUR DES BLANCS",noir, screen);
        if (color == BLACK)
            printtext(230, 283, "./Textures/CarnevaleeFreakshow.ttf",39,"AU TOUR DES NOIRS",noir, screen);
        SDL_Flip(screen);
        moves[i].src_point= selectPion(gameState,true,color);
        fprintf(stderr,"src: %d",moves[i].src_point);
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        SDL_Flip(screen);
        moves[i].dest_point = selectPion(gameState,false,color);
        fprintf(stderr,"dest: %d",moves[i].dest_point);
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        SDL_Flip(screen);
    }

}
