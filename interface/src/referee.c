#include"referee.h"

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

#include"error.h"
#include"logger.h"

static const char* enumToStr[] = { "NOBODY", "BLACK", "WHITE" };
//TODO : tester et vérifier si c'est bon
//TODO : faire le cas où il y a des pions dans la zone out et zone de fin
//TODO : vérifier qu'on utilise les plus grands dés
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
    //TODO : 0 -> zone out
    //TODO : 25 -> zone de fin
    //TODO : faire en sorte que ça marche pour la sortie de la zone out pour tout
    //les joueurs (black sort au niveau des ~20)
    uint err = 0;
    int delta_move = (move.dest_point - move.src_point);
    if(move.src_point==0 && player==BLACK)
    {
        delta_move = 25-move.dest_point;
    }
    else if(move.dest_point==25)
    {
        if(player==BLACK)
        {
            delta_move = move.src_point;
        }
        else
        {
            delta_move = move.dest_point - move.src_point;
        }
    }
    if(delta_move<0)
    {
       delta_move=-delta_move;
    }
    bool can_take_from   = false;
    if(move.src_point==0)
    {
        can_take_from = state->bar[player]>0;
    }
    else
    {
        can_take_from =state->board[move.src_point-1].nbDames>0 && state->board[move.src_point-1].owner==player;
    }
    //TODO : faire la vérif de sortie des dames (cf wikipedia)
    bool can_put_to = false;
    if(move.dest_point==25)
    {
        can_put_to = !check_side(state, player);
    }
    else
    {
        can_put_to = state->board[move.dest_point-1].owner==player || state->board[move.dest_point-1].nbDames<2;
    }
    const bool has_out = state->bar[player]>0;
    if ( !can_take_from ||
         !can_put_to ||
         (has_out && move.src_point!=0)
         )
    {
        err = 1;
    }
    else
    {
        err = 1;
        uint i=0;
        while(i<nb_dices && err!=0)
        {
            if( dices[i]!=delta_move || (move.dest_point==25 && dices[i]<delta_move) )
            {
                err = 1;
            }
            else
            {
                err = 0;
            }
            ++i;
        }
    }
    if(err>0)
    {
        char mess[50];
        sprintf(mess, "%s à fait une erreur\n", enumToStr[player+1]);
        logging("referee_logger", mess, WARNING);
    }
    return err;
}

int check_side(SGameState const * const state, const Player player)
{
    int err            = false;
    unsigned int index = 7;
    unsigned int end   = 24;
    if(player == WHITE)
    {
        index = 1;
        end   = 19;
    }
    while(index<end && !err)
    {
        if( state->board[index-1].owner == player)
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
    SGameState copy = *state;
    while(i<nb_moves && errors==0)
    {
        if(check_move(moves[i], dices, nb_dices, player, state))
        {
            ++errors;
            *state = copy;
        }
        else
        {
            move(state, moves[i], player);
        }
        ++i;
    }
    return errors;
}

void move(SGameState * const state, SMove const movement, const Player player)
{
    char mess[50];
    sprintf(mess, "%s bouge de %d à %d\n", enumToStr[player+1], movement.src_point, movement.dest_point);
    logging("referee_logger", mess, INFO);
    if(movement.dest_point == 25)
        move_to_end(state, movement, player);
    else if(movement.src_point == 0)
        move_from_out(state, movement, player);
    else
        move_in_board(state, movement, player);
}

void move_from_out(SGameState * const state, SMove const movement, const Player player)
{
    state->bar[player]--;
    put_on(state->board, state->bar, movement.dest_point, player);
}

void move_to_end(SGameState * const state, SMove const movement, const Player player)
{
    take_from(state->board, movement.src_point);
    state->out[player]++;
}

void move_in_board(SGameState * const state, SMove const movement, const Player player)
{
    take_from(state->board, movement.src_point);
    put_on(state->board, state->bar, movement.dest_point, player);
}

void put_on(Square board[24], uint bar[2], cuint dest, const Player p)
{
    if( board[dest-1].owner != p && board[dest-1].nbDames<2 )
    {
        if(board[dest-1].owner!=NOBODY && board[dest-1].nbDames>0)
        {
            bar[1-p]++;
            char mess[50];
            sprintf(mess, "%s mange un pion de %s\n", enumToStr[p+1], enumToStr[(1-p)+1]);
            logging("referee_logger", mess, INFO);
        }
        char mess[50];
        sprintf(mess, "la case %i passe de %s à %s\n", dest, enumToStr[p+1], enumToStr[board[dest-1].owner+1]);
        logging("referee_logger", mess, INFO);
        board[dest-1].owner = p;
        board[dest-1].nbDames = 0;
    }
    board[dest-1].nbDames++;
}

void take_from(Square board[24], cuint src)
{
    board[src-1].nbDames--;
    if(board[src-1].nbDames==0) board[src-1].owner=NOBODY;
}
