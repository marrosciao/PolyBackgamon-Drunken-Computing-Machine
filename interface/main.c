#include<stdbool.h>
#include<assert.h>
#include<dlfcn.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"backgammon.h"
#include"config.h"
#include"init.h"
#include"game.h"
//#include"logger.h"

#define STRINGIFY_HELPER( str ) #str
#define STRINGIFY( str ) STRINGIFY_HELPER( str )

//TODO : faire les test et merge la branche
//TODO : appliquer clang-format
//TODO : refactoring pour que ça soit plus propre
//TODO : gestion erreur
//TODO : faire la gestion des paramêtres en ligne de commande
//TODO : faire le test si on utilise le max des dés

void err(String str){
    fprintf(stderr, "%s -> %s\n",str, dlerror());
    exit(EXIT_FAILURE);
}

Player choose_start_player(unsigned int i)
{
    unsigned char dice[2];
    roll_dice(dice);
    Player tmp = BLACK;
    if( dice[BLACK] > dice[WHITE])
        tmp = BLACK;
    else if( dice[WHITE] > dice[BLACK] )
        tmp = WHITE;
    else if( i<10 )
        tmp = choose_start_player(++i);
    return tmp;
}

int main(int ARGC, const char* ARGV[])
{
    unsigned int target_score = 15 ;

    if (ARGC >= 2)
    {
        char* pEnd;
        target_score = (int)strtol(ARGV[1],&pEnd,0);

        if (strcmp(pEnd,"\0") != 0)
        {
            //Erreur de target_score ...
            perror("ERREUR : Invalide parametre target_score (doit etre entier et 1er parametre)");
            exit(EXIT_FAILURE);
        }

        if (target_score <= 0)
        {
            //stupide de faire un score nul comem objectif ...
            perror("ERREUR : target_score negatif ou nul");
            exit(EXIT_FAILURE);
        }
        printf("Lecture de target_score : %i\n",target_score);
    }
    else
    {
        printf("Pas de target_score fourni, pas defaut %i\n",target_score);
    }

    //init_logger();
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};

    IA players[2];
    players[0].lib_path=(char*)"./strategy/libstrategy.so";
    players[1].lib_path=(char*)"./strategy/libstrategy.so";
    // --- Initialisation des bibliothèques
    for(int i=0; i<2; ++i)
    {
        if (ARGC >= 3+i)
        {
            players[i].lib_path=(char*)calloc(strlen(ARGV[2+i])+1,sizeof(char));
            strcpy(players[i].lib_path,ARGV[2+i]);
        }
        players[i].func = (Functions*)malloc( sizeof(Functions) );
        players[i].lib_handle = NULL;
        init_lib( players[i].lib_path , &(players[i].lib_handle), players[i].func, err);
        players[i].func->initLibrary( (players[i].name) );
        printf("%s I.A. : %s\n", enumToStr[i+1],players[i].name );
    }

    // --- Initialisation du jeux
    SGameState state;
    init_state(&state);

    for(unsigned int i=0; i<24; ++i)
    {
        printf("case %2d : owner %6s, nbDames %d\n", i, enumToStr[state.board[i].owner+1], state.board[i].nbDames);
    }
    players[WHITE].func->startMatch(target_score);
    players[BLACK].func->startMatch(target_score);
    bool finished               = false;
    const unsigned int maxScore = 3;
    unsigned int turn_num       = 1;
    srand(time(NULL));

    // --- Boucle principale
    while(!finished)
    {
        //TODO : faire des affichages pour voir si les fonctions sont bien lancé
        //TODO : faire un logger basic
        //TODO : RAZ du board
        printf("Début de la manche %d\n", turn_num);
        Player current = choose_start_player(0);
        printf("\t%s commence\n", enumToStr[current+1]);
        for(unsigned int i=0; i<2; ++i)
        {
            players[i].func->startGame( (Player)i );
            players[i].tries = 3;
        }
        bool end_of_round      = false;
        state.stake            = 1;
        Player winner          = NOBODY;
        Player lastStaker      = NOBODY;
        state.turn             = 1;
        init_board(&state);
        while(!end_of_round)
        {
            printf("\tDébut du tour %d\n\t\tJoueur : %s\n", state.turn, enumToStr[current+1]);
            end_of_round = gamePlayTurn(&state, players, current, &lastStaker, &winner);
            printf("\tfin du tour %d\n", state.turn);
            current = (Player)(1-current);
            ++state.turn;
        }
        for(unsigned int i=0; i<2; ++i) players[i].func->endGame();
        if(winner==WHITE)
        {
            state.whiteScore+=state.stake;
            finished = state.whiteScore>=maxScore;
        }
        else
        {
            state.blackScore+=state.stake;
            finished = state.blackScore>=maxScore;
        }
        int score = state.blackScore;
        if(winner==WHITE) score = state.whiteScore;
        printf("gagnant : %s, gagne %d points (total %d )\n", enumToStr[winner+1], state.stake, score);
        printf("fin de la manche %d\n", turn_num);
        ++turn_num;
    }
    for(unsigned int i=0; i<2; ++i) players[i].func->endMatch();

    // --- Fermeture des bibliothèques
    for(int i=0; i<2; ++i)
    {
        dlclose(players[i].lib_handle);
        if (ARGC >= 3+i)
            free(players[i].lib_path);
    }
    return EXIT_SUCCESS;
}
