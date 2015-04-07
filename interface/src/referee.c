#include"referee.h"

#include<stdbool.h>
#include<stdio.h>

#include"error.h"

//TODO : tester et vérifier si c'est bon
//TODO : faire le cas où il y a des pions dans la zone out et zone de fin
int check_number_dices(
        const SGameState * const state,
        Dice dices[],
        cuint nb_moves,
        const Player player)
{
    uint err = false;
    if(
        !(dices[0]==dices[1] && nb_moves==4) &&
        !(dices[0]!=dices[1] && nb_moves==2)
        )
    {
        uint dice_nb   = 0;
        uint idx       = 0;
        uint num_moves = 0;
        while( idx<24 && (
                    (num_moves<=2 && dices[0]!=dices[1]) ||
                    (num_moves<=4 && dices[0]==dices[1])
                ) )
        {
            if( state->board[idx].owner==player)
            {
                SMove move = { idx+1, idx+1+dices[dice_nb] };
                if(!check_move(move, dices, 2, player, state))
                {
                    dice_nb = (dice_nb+1)%2;
                    ++num_moves;
                    idx = 0;
                }
            }
            ++idx;
        }
        err = !( num_moves==nb_moves );
    }
    return err;
}

//TODO : changer les paramêtres pour enlever les trucs inutiles
//TODO : refactoring ?
//TODO : verifier qu'on utilise pas deux fois le même dé
//TODO : verif de l'utilisation max des dés
int check_move(const SMove move,
        Dice dices[],
        cuint nb_dices,
        const Player player,
        SGameState const * const state)
{
    // Si player==BLACK 1-player == WHITE, de même si player==WHITE.
    // Si player==BLACK==0, 1-player==1, -1*(1-player)==-1, inversement pour player==WHITE.
    // Le joueur noir se déplace de la case
    // 24 vers la case 0, donc dans le sens négatif.
    // Pour vérifier si le déplacement est valide, on prend la valeur absolue 
    // de la différence dest - src en multipliant par -1 si le joueur est 
    // le joueur noir et par 1 si il est blanc.
    //TODO : 0 -> zone out
    //TODO : 25 -> zone de fin
    //TODO : faire en sorte que ça marche pour la sortie de la zone out pour tout
    //les joueurs (black sort au niveau des ~20)
    uint err                   = 0;
    int delta_move            = (move.dest_point - move.src_point);
    if(move.src_point==0) delta_move = 24-move.dest_point;
    if(delta_move<0) delta_move=-delta_move;
    bool can_take_from   = false;
    if(move.src_point==0) can_take_from = state->bar[player]>0;
    else                  can_take_from =state->board[move.src_point-1].nbDames>0 && state->board[move.src_point-1].owner==player;
    //TODO : verif overflow
    const bool can_put_to      = state->board[move.dest_point-1].owner==player || state->board[move.dest_point-1].nbDames<2;
    const bool has_out         = state->bar[player]>0;
    const bool can_put_out     = check_side(state, player);
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    if ( !can_take_from ||
         !can_put_to || 
         (has_out && move.src_point!=0) ||
         (move.dest_point==25 && !can_put_out))
    {
        if( !can_take_from )
            printf("\t\t%s : can't take from %d : owner %s, nbDames %d\n", enumToStr[player+1], move.src_point, enumToStr[state->board[move.src_point-1].owner+1], state->board[move.src_point-1].nbDames);
        if( !can_put_to )
            printf("\t\t%s : can't put to %d : owner %s, nbDames %d\n", enumToStr[player+1], move.dest_point, enumToStr[state->board[move.dest_point-1].owner+1], state->board[move.dest_point-1].nbDames);
        if( has_out && move.src_point!=0 )
            printf("\t\t%s : has piece out\n", enumToStr[player+1]);
        if( !can_put_out && move.dest_point==25)
            printf("\t\t%s : can't put piece to the end\n", enumToStr[player+1]);
        err = 1;
    }
    else
    {
        err = 1;
        uint i=0;
        while(i<nb_dices && err!=0)
        {
            /*const bool authorized_move = dices[i]==delta_move;*/
            if( dices[i]!=delta_move)
            {
                printf("\t\t%s : Can't move from %d to %d, dice result is %d, delta_move=%d\n", enumToStr[player+1], move.src_point, move.dest_point, dices[i], delta_move);
                err = 1;
            }
            else
            {
                err = 0;
                //mettre dice à un valeur invalide
            }
            ++i;
        }
    }
    printf("\t\t%s : %d erreur\n\n", enumToStr[player+1], err);
    return err;
}

int check_side(SGameState const * const state, const Player player)
{
    int err            = false;
    unsigned int index = 6;
    unsigned int end   = 24;
    if(player == WHITE)
    {
        index = 1;
        end   = 19;
    }
    while(index<end && !err)
    {
        if( state->board[index].owner == player)
        {
            err = true;
        }
        ++index;
    }
    return err;
    
}

//TODO : changer les paramêtres pour enlever les trucs inutiles
//TODO : si erreur -> arrêt
int move_all(
        SGameState *const state,
        SMove const * const moves,
        cuint nb_moves,
        Dice dices[],
        cuint nb_dices,
        const Player player )
{
    uint errors = 0;
    uint i = 0;
    while(i<nb_moves && errors==0)
    {
        if(check_move(moves[i], dices, nb_dices, player, state))
        {
            ++errors;
        }
        else
        {
            //TODO : 0 -> zone out
            //TODO : 25 -> zone de fin
            move(state, moves[i], player);
        }
        ++i;
    }
    return errors;
}

void move(SGameState * const state, SMove const movement, const Player player)
{
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    printf("\t\t\t%s : move from %d to %d\n", enumToStr[player+1], movement.src_point, movement.dest_point);
    if(movement.dest_point == 25)
        move_to_end(state, movement, player);
    else if(movement.src_point == 0)
        move_from_out(state, movement, player);
    else
        move_in_board(state, movement, player);
}

void move_from_out(SGameState * const state, SMove const movement, const Player player)
{
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    printf("\t\t\t%s : take from bar\n",enumToStr[player+1]);
    state->bar[player]--;
    put_on(state->board, state->bar, movement.dest_point, player);
}

void move_to_end(SGameState * const state, SMove const movement, const Player player)
{
    take_from(state->board, movement.src_point);
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    printf("\t\t\t%s : put piece to end zone\n",enumToStr[player+1]);
    state->out[player]++;
}

void move_in_board(SGameState * const state, SMove const movement, const Player player)
{
    take_from(state->board, movement.src_point);
    put_on(state->board, state->bar, movement.dest_point, player);
}

void put_on(Square board[24], uint bar[2], cuint dest, const Player p)
{
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    if( board[dest-1].owner != p && board[dest-1].nbDames<2 )
    {
        printf("\t\t\t%d change owner : from %s to %s\n", dest, enumToStr[board[dest-1].owner+1], enumToStr[p+1]);
        if(board[dest-1].owner!=NOBODY && board[dest-1].nbDames>0) bar[1-p]++;
        board[dest-1].owner = p;
        board[dest-1].nbDames = 0;
    }
    board[dest-1].nbDames++;
    printf("\t\t\t%d has now %d piece and is owned by %s\n", dest, board[dest-1].nbDames, enumToStr[board[dest-1].owner+1]);
}

void take_from(Square board[24], cuint src)
{
    const char* const enumToStr[] = {"NOBODY", "BLACK", "WHITE"};
    board[src-1].nbDames--;
    if(board[src-1].nbDames==0) board[src-1].owner=NOBODY;
    printf("\t\t\t%d has now %d piece and is owned by %s\n", src, board[src-1].nbDames, enumToStr[board[src-1].owner+1]);
}
