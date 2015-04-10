#ifndef GRAPH
#define GRAPH
#include<SDL/SDL.h>
#include"backgammon.h"
#include<stdbool.h>

/**
 * @fn SDL_Surface* initGraph()
 * @brief Demarre la fenètre SDL
 * @return un ecran sur lequel tout sera affiché
 */
SDL_Surface* initGraph();
/**
 * @fn void endGraph()
 * @brief Termine la SDL
 */
void endGraph(); 
/**
 * @fn void drawPiece(Player color,int posx,int posy,SDL_Surface* screen)
 * @brief Dessine un pion à la position donnée
 * @param color     couleur du pion 
 * @param posx      coordonnée x
 * @param posy      coordonnée y
 * @param screen    surface sur laquelle on le dessine
 */
void drawPiece(Player color,int posx,int posy,SDL_Surface* screen);
/**
 * @fn void drawBackground(SDL_Surface* screen)
 * @brief Dessine le fond du jeu
 * @param screen    surface sur laquelle on le dessine
 */
void drawBackground(SDL_Surface* screen);
/**
 * @fn void drawDes(unsigned char dices[2], SDL_Surface* screen)
 * @brief dessineles des donnés
 * @param dices     Des à dessiner
 * @param screen    surface sur laquelle on les dessine
 */
void drawDes(const unsigned char dices[2], SDL_Surface* screen); 
/**
 * @fn void animateDes(unsigned char dices[2], SDL_Surface* screen)
 * @brief annime le roulement des des donnés
 * @param dices     Des à dessiner
 * @param screen    surface sur laquelle on les dessine
 */
void animateDes(unsigned char dices[2], SDL_Surface* screen);
/**
 * @fn void printtext(int posx, int posy, char fontName[],int size, char message[],SDL_Color color, SDL_Surface* screen)
 * @brief affiche un texte donné
 * @param posx      coordonnée x du milieu du texte
 * @param posy      coordonnée y du haut du texte
 * @param fontName  police utilisée
 * @param size      taille de police utilisée
 * @param message   ce qu'il faut ecrire
 * @param color     couleur d'ecriture
 * @param screen    surface sur laquelle on les dessine
 */
void printtext(int posx, int posy, char fontName[],int size, char message[],SDL_Color color, SDL_Surface* screen);
/**
 * @fn void drawBoard(SGameState* state, SDL_Surface* screen)
 * @brief Dessine le board (pions, videau, bar, out)
 * @param state     l'état courant à dessiner
 */
void drawBoard(SGameState const * const state, SDL_Surface* screen);
/**
 * @fn bool hitbox(int x,int y,int i)
 * @brief verifie si les coordonnées x,y correspondent à une case du jeu i 
 * @param x     coordonnée x
 * @param y     coordonnée y
 * @param i     indice de la case que l'on verifie  
 * @return true si on est dans la case, false sinon
 */
bool hitbox(int x,int y,int i); 
/**
 * @fn int selectPion(SGameState* state, bool src, Player color)
 * @brief permet au joueur d'interagir avec le jeu en selectionnant les pions qu'il veut bouger ou en annulant ses coups ou en validant ses coups 
 * @param state     L'état du jeu
 * @param src       un paramètre qui permet de choisir si on veut que le joueur selectionne un pion à deplacer(avec clic gauche):src=true ou une case ou le poser (avec clic droit):src=false
 * @param color     la couleur que joue le joueur, pour l'empecher de bouget des pions enemis  
 * @return un nombre entre 0 et 27 (de 0 à 25: cases du plateau; 26: validation des coups; 27: annulation des coups):
 */
int selectPion(SGameState* state, bool src, Player color);


#endif
