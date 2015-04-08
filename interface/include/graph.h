#ifndef GRAPH
#define GRAPH
#include<SDL/SDL.h>
#include"backgammon.h"

SDL_Surface* initGraph();
void endGraph();
int drawPiece(Player color,int posx,int posy,SDL_Surface* screen);
int drawBackground(SDL_Surface* screen);
int drawDes(unsigned char dices[2], SDL_Surface* screen);
int animateDes(unsigned char dices[2], SDL_Surface* screen);
int printtext(int posx, int posy, char fontName[],int size, char message[],SDL_Color color, SDL_Surface* screen);
int drawBoard(SGameState* state, SDL_Surface* screen);
bool hitbox(int x,int y,int i);
int selectPion(SGameState* state, SDL_Surface* screen, bool src, Player color);
int PlayTurn( SGameState *  gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries, SDL_Surface* screen, Player color);

#endif