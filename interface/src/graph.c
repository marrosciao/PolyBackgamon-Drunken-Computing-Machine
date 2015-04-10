#include<stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "backgammon.h"
#include <time.h>
#include <stdlib.h>

typedef unsigned int uint;

SDL_Surface* initGraph(){   //Lance une nouvelle fenetre SDL
    int largeur = 1000;
    int hauteur = 627;
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	screen = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Backgammon des Potits Pedestres", NULL);
    return screen;
}

void endGraph(){    //Ferme les fenetres SDL
    TTF_Quit();
    SDL_Quit();
}


int drawPiece(Player color,int posx,int posy,SDL_Surface* screen){ //Changer le int en Player quand je ferais l'import
    SDL_Surface *img = NULL;
    SDL_Surface *imgOk = NULL;
    SDL_Rect pos;
    pos.x = posx;
    pos.y = posy;
    if (color == WHITE)  {
        img = SDL_LoadBMP("./Textures/Blanc.bmp"); //idem
    }
    else {
        img = SDL_LoadBMP("./Textures/Noir.bmp");
    }
    imgOk = (SDL_Surface*) SDL_DisplayFormat( img );
    SDL_FreeSurface(img);
    SDL_SetColorKey(imgOk, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( imgOk->format, 0, 0, 0xFF ));
    SDL_BlitSurface(imgOk, NULL, screen, &pos);
    SDL_FreeSurface(imgOk);
    return EXIT_SUCCESS;
}

int drawBackground(SDL_Surface* screen){
    SDL_Surface *background = NULL; 
    background = SDL_LoadBMP("./Textures/background.bmp");
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_FreeSurface(background);
    return EXIT_SUCCESS;
}

int drawDes(unsigned char dices[2], SDL_Surface* screen){
        char nom1[] = "./Textures/De5.bmp";
        char nom2[] = "./Textures/De5.bmp";
        nom1[13] = dices[0]+'0';
        nom2[13] = dices[1]+'0';
        SDL_Surface *img1 = NULL, *imgOk1 = NULL, *img2, *imgOk2;
        SDL_Rect pos1;
        pos1.x = 829;
        pos1.y = 283;
        SDL_Rect pos2;
        pos2.x = 908;
        pos2.y = 283;
        img1 = SDL_LoadBMP(nom1); 
        img2 = SDL_LoadBMP(nom2); 
        imgOk1 = (SDL_Surface*) SDL_DisplayFormat( img1 );
        imgOk2 = (SDL_Surface*) SDL_DisplayFormat( img2 );
        SDL_FreeSurface(img1);
        SDL_FreeSurface(img2);
        SDL_SetColorKey(imgOk1, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( imgOk1->format, 0, 0, 0xFF ));
        SDL_SetColorKey(imgOk2, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( imgOk2->format, 0, 0, 0xFF ));
        SDL_BlitSurface(imgOk1, NULL, screen, &pos1);
        SDL_BlitSurface(imgOk2, NULL, screen, &pos2);
        SDL_FreeSurface(imgOk1);
        SDL_FreeSurface(imgOk2);
        return EXIT_SUCCESS;
}   
int animateDes(unsigned char dices[2], SDL_Surface* screen){
    unsigned char rollingDices[2];
    for (float i=50; i>10; i=i/1.5){
        rollingDices[0] = rand() %6 +1;;
        rollingDices[1] = rand() %6 +1;
        drawDes(rollingDices, screen);
        SDL_Flip( screen );
        SDL_Delay(1000/i);
    }
    drawDes(dices,screen);
    SDL_Flip( screen ); 
    SDL_Delay(1000);
	return EXIT_SUCCESS;
}

void printtext(int posx, int posy, char fontName[],int size, char message[],SDL_Color color, SDL_Surface* screen) {
    
    TTF_Font *font = TTF_OpenFont(fontName,size);
    SDL_Surface *text = TTF_RenderText_Blended(font, message, color);
    SDL_Rect pos;
    pos.x = posx-(text->w/2);
    pos.y = posy;
    SDL_BlitSurface(text, NULL, screen, &pos);
    TTF_CloseFont(font);
    SDL_FreeSurface(text);
}


int drawBoard(SGameState* state, SDL_Surface* screen){
    char affichenb[20];
    SDL_Color couleurTexte = {
        .r = 255,
        .g = 255,
        .b = 255,
    };
    for (int i=5; i>=0; i--){
        for (uint j = 0; j < state->board[i+18].nbDames && j<5; j++) {
            drawPiece(state->board[i+18].owner,480+53*i,43+j*38,screen);
        }
        if (state->board[i+18].nbDames > 5){
            sprintf(affichenb,"%d",state->board[i+18].nbDames);
            printtext(500+53*i, 12, "./Textures/CowboyMovie.ttf",32,affichenb,couleurTexte, screen);
        }
        for (uint j = 0; j < state->board[i+12].nbDames && j<5; j++) {
            drawPiece(state->board[i+12].owner,75+53*i,43+j*38,screen);
        }
	    if (state->board[i+12].nbDames > 5){
            sprintf(affichenb,"%d",state->board[i+12].nbDames);
            printtext(95+53*i, 12, "./Textures/CowboyMovie.ttf",32,affichenb,couleurTexte, screen);
        }
    }
    for (int i=0; i<6; i++){
        for (uint j = 0; j < state->board[i+6].nbDames && j<5; j++)
            drawPiece(state->board[i+6].owner,340-53*i,542-j*38,screen);     
        if (state->board[i+6].nbDames > 5){
            sprintf(affichenb,"%d",state->board[i+6].nbDames);
            printtext(360-53*i, 587, "./Textures/CowboyMovie.ttf",32,affichenb,couleurTexte, screen);
        }
        for (uint j = 0; j < state->board[i].nbDames && j<5; j++){
            if (i!=5){ 
            	drawPiece(state->board[i].owner,747-53*i,542-j*38,screen);
            }
	        if (i == 5){
            	drawPiece(state->board[i].owner,480,542-j*38,screen);
            }
        }         
    	if (state->board[i].nbDames > 5){
            sprintf(affichenb,"%d",state->board[i].nbDames);
            if (i!=5)
                printtext(767-53*i, 587, "./Textures/CowboyMovie.ttf",32,affichenb,couleurTexte, screen);
            if (i==5)
                printtext(500, 587, "./Textures/CowboyMovie.ttf",32,affichenb,couleurTexte, screen);
        }
    }
        for (uint j = 0; j < state->bar[0]; j++)
            drawPiece(BLACK,411,100+j*30,screen);     
        for (uint j = 0; j < state->bar[1]; j++)
            drawPiece(WHITE,411,527-j*30,screen);     
        for (uint j = 0; j < state->out[1]; j++) {
            if (j%2==1)
                drawPiece(WHITE,860,75+j*10,screen);
            else
                drawPiece(WHITE,908,85+j*10,screen);
        }        
        for (uint j = 0; j < state->out[0]; j++) {
            if (j%2==1)
                drawPiece(BLACK,860,520-j*10,screen);
            else
                drawPiece(BLACK,908,510-j*10,screen);
        }
        SDL_Surface *img = SDL_LoadBMP("./Textures/Videau.bmp"); 
        SDL_Surface *imgOk = (SDL_Surface*) SDL_DisplayFormat( img );
        SDL_FreeSurface(img);
        SDL_SetColorKey(imgOk, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( imgOk->format, 0, 0, 0xFF ));
        SDL_Rect pos;
        pos.x = 401;
        pos.y = 280;
        SDL_BlitSurface(imgOk, NULL, screen, &pos);
        SDL_FreeSurface(imgOk);
        sprintf(affichenb,"%d",state->stake);
        printtext(430, 295, "./Textures/RioGrande.ttf",26,affichenb,couleurTexte, screen);
        sprintf(affichenb,"%d",state->whiteScore);
        printtext(904, 568, "./Textures/RioGrande.ttf",32,affichenb,couleurTexte, screen);
        sprintf(affichenb,"%d",state->blackScore);
        printtext(904, 25, "./Textures/RioGrande.ttf",32,affichenb,couleurTexte, screen);

        
    

    
    
    
    return EXIT_SUCCESS;
}
bool hitbox(int x,int y,int i){
    if (i== -1)
        return (x<460 && x>400);
    else if (i>=0 && i<6)
        return (x< 793-53*i && x>793-53*(i+1) && y <582 && y>357);
    else if (i>=6 && i<12)
        return (x< 386-53*(i-6) && x>386-53*(i-5) && y <582 && y>357); 
    else if (i>=12 && i<18)
        return (x< 69+53*(i-11) && x>69+53*(i-12) && y < 270 && y>45); 
    else if (i>=18 && i<24)
        return (x< 474+53*(i-17) && x>474+53*(i-18) && y <270 && y>45); 
    else if (i == 24)
        return (x<956 && x>853);
    else
        return false;
}
int selectPion(SGameState* state, bool src, Player color){
    int continuer = 1;
    SDL_Event event;
    int i;
    int val;
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
            case SDL_MOUSEBUTTONDOWN:
                pos.x = event.button.x;
                pos.y = event.button.y;
                for (i=-1; i<25; i++){
                    if (hitbox(pos.x,pos.y,i)==true){
                        if (event.button.button == SDL_BUTTON_RIGHT && src==false){ 
                            if(i==24){
                                continuer = 0;
                                fprintf(stderr,"col:%d",color);
                                state->out[color] += 1;
                                val = i;
                            }
                            else if( ((state->board[i].nbDames == 1) || (color == state->board[i].owner) || (state->board[i].owner== NOBODY))){
                                continuer = 0;
                                if ((state->board[i].owner == color)||(state->board[i].owner)==NOBODY){
                                    state->board[i].nbDames ++;
                                }
                                state->board[i].owner = color;
                                val = i;
                            }
                        }
                        if (event.button.button == SDL_BUTTON_LEFT && src==true ){
                            if (state->board[i].nbDames != 0 && color == state->board[i].owner){
                                state->board[i].nbDames --;
                                continuer = 0;
                                val = i;
                            }
                            else if (i==-1){
                                state->bar[color] -= 1;
                                val = i;
                                continuer = 0;
                            }
                        }
                    }
                }
                break;
    }
}
    return val+1;
}

