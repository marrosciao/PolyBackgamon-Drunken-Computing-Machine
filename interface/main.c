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
#include"logger.h"

#define STRINGIFY_HELPER( str ) #str
#define STRINGIFY( str ) STRINGIFY_HELPER( str )

//TODO : faire les test et merge la branche
//TODO : appliquer clang-format
//TODO : refactoring pour que ça soit plus propre
//TODO : gestion erreur

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

int main(){
    init_logger();
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    IA players[2];
    //TODO : faire la gestion des paramêtres en ligne de commande
    // --- Initialisation des bibliothèques 
    for(unsigned int i=0; i<2; ++i)
    {
        players[i].lib_path = (char*)calloc(strlen(LIB_PATH) + strlen("/strategy/libstrategy.so")+1, sizeof(char));
        sprintf( players[i].lib_path , "%s/strategy/libstrategy.so", LIB_PATH);
        players[i].func = (Functions*)malloc( sizeof(Functions) );
        players[i].lib_handle = NULL;
        init_lib( players[i].lib_path , &(players[i].lib_handle), players[i].func, err);
        players[i].func->initLibrary( (players[i].name) );
        printf("%s I.A. : %s\n", enumToStr[i+1],players[i].name );
    }
    
    // --- Initialisation du jeux 
    SGameState state;
    init_state(&state);

    const unsigned int target_score = 1;
    players[WHITE].func->startMatch(target_score);
    players[BLACK].func->startMatch(target_score);
    bool finished = false;
    const unsigned int maxScore = 3;
    unsigned int turn_num = 1;
    srand(time(NULL));

    // --- Boucle principale
    while(!finished)
    {
        //TODO : faire des affichages pour voir si les fonctions sont bien lancé
        //TODO : faire un logger basic
        printf("Début de la manche %d\n", turn_num);
        Player current = choose_start_player(0);
        printf("\t%s commence\n", enumToStr[current+1]);
        for(unsigned int i=0; i<2; ++i){
            players[i].func->startGame((Player)i);
            players[i].tries = 3;
        }
        bool end_of_round = false;
        state.stake = 1;
        Player winner = NOBODY;
        Player lastStaker = NOBODY;
        unsigned int round_num = 1;
        while(!end_of_round)
        {
            printf("\tDébut du tour %d\n\t\tJoueur : %s\n", round_num, enumToStr[current+1]);
            end_of_round = gamePlayTurn(&state, players, current, &lastStaker, &winner);
            printf("\tfin du tour %d\n", round_num);
            current = (Player)(1-current);
        }
        for(unsigned int i=0; i<2; ++i) players[i].func->endGame();
        if(winner==WHITE)
        {
            state.whiteScore+=state.stake;
            finished = state.whiteScore==maxScore;
        }
        else
        {
            state.blackScore+=state.stake;
            finished = state.blackScore==maxScore;
        }
        printf("fin de la manche %d\n", turn_num);
        printf("gagnant : %s\n", enumToStr[winner+1]);
        ++turn_num;
    }
    for(unsigned int i=0; i<2; ++i) players[i].func->endMatch();

    // --- Fermeture des bibliothèques 
    for(unsigned int i=0; i<2; ++i)
    {
        dlclose(players[i].lib_handle);
        free(players[i].lib_path);
    }
    return EXIT_SUCCESS;
}
