#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>

#include "backgammon.h"
#include "graph.h"
#include "init.h"
#include "human.h"
#include "game.h"

Player color;
SDL_Surface* screen;

void InitLibrary(char name[50])
{
    strcpy(name,"Joueur Humain");
}

void StartMatch(const unsigned int target_score)
{
    // Non utilisé
}

void StartGame(Player p)
{
    color = p ;
}

Functions* StartScreen(SDL_Surface* s)
{
//Cette fonction est un ajout par rapport aux librairies d'IA qui nous permet de communiquer au joueur humain l'ecran
//pour que l'on puisse avoir un joueur humain sur l'interface gerée par l'arbitre
// Elle renvoie les fonctions que pourra ensuite appeler l'arbitre
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
    //Dans cette fonction, on demande au joueur s'il souhaite doubler le videau, il peut taper o pour oui ou n pour non.

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
    //Dans cette fonction, on demande au joueur s'il accepte qu'on double le videau, il peut taper o pour oui ou n pour non.
    
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

void PlayTurn( SGameState const * const  state, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries){
    
    //cette fonction à les mêmes parametres que le playturn d'une IA classique, ce qui permet à l'arbitre de ne pas differencier humain et IA

    int nbMoves = 0;
    SGameState* gameState = copy_state(*state);
    int point;
    int src = 0;
    int boucle = 1;
    char coup[] = "coups joues : 0";
    SDL_Color noir = {      //Au final c'est du marron :p
        .r = 31,
        .g = 15,
        .b = 10,
    };

    while (boucle){
        coup[14] = nbMoves+'0';
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        printtext(630, 263, "./Textures/CarnevaleeFreakshow.ttf",39,coup,noir, screen);
        printtext(630, 303, "./Textures/CarnevaleeFreakshow.ttf",30," annuler tour: [backspace]",noir, screen);
        printtext(630, 323, "./Textures/CarnevaleeFreakshow.ttf",30,"valider tour : [enter]",noir, screen);
        if (color == WHITE)
            printtext(230, 283, "./Textures/CarnevaleeFreakshow.ttf",39,"AU TOUR DES BLANCS",noir, screen);
        if (color == BLACK)
            printtext(230, 283, "./Textures/CarnevaleeFreakshow.ttf",39,"AU TOUR DES NOIRS",noir, screen);
        SDL_Flip(screen);
        point= selectPion(gameState,true,color);
        if (point <= 25){
            src = point;
        }
        else if (point == 26){
            gameState=copy_state(*state);
            nbMoves = 0;
        }
        else if (point == 27){
            *nbMove = nbMoves;
            boucle = 0;
        }
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        SDL_Flip(screen);
        if (point <= 25){
        point= selectPion(gameState,false,color);
        }
        if (point <= 25){
            moves[nbMoves].src_point= src;
            moves[nbMoves].dest_point = point;
            nbMoves += 1; 
        } 
        if (point == 26){
            gameState=copy_state(*state);
            nbMoves = 0;
        }
        if (point == 27){
            *nbMove = nbMoves;
            boucle = 0;
        }
        drawBackground(screen);  
        drawBoard(gameState, screen);
        drawDes(dices,screen);
        SDL_Flip(screen);
    }
    free(gameState); 
}
