#ifndef GRAPH
#define GRAPH
#include<SDL/SDL.h>
#include"backgammon.h"
#include<stdbool.h>

SDL_Surface* initGraph(); //Demmarre la fenetre, et renvoie la Surface screen sur laquelle se feront ajouts d'images
void endGraph(); //Ferme SDL et SDL_ttf
int drawPiece(Player color,int posx,int posy,SDL_Surface* screen); //Dessine un pion à la position donnée
int drawBackground(SDL_Surface* screen); //Dessine le fond du backgammon
int drawDes(unsigned char dices[2], SDL_Surface* screen); //Dessine les dés
int animateDes(unsigned char dices[2], SDL_Surface* screen); //Anime un roulement de dés
int printtext(int posx, int posy, char fontName[],int size, char message[],SDL_Color color, SDL_Surface* screen); // Affiche le texte donné, centré sur posx, et avec le haut sur posy
int drawBoard(SGameState* state, SDL_Surface* screen); //Dessine l'état donné
bool hitbox(int x,int y,int i); //Revoire true si les coordonnées x,y sont dans la case i, false sinon
int selectPion(SGameState* state, bool src, Player color); //permet au joueur de selectionner un pion si src=true, et de selectionner une case ou il posera un pion si src=false

#endif
