#include"referee.h"

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"error.h"
#include"logger.h"

#define stringify_helper(str) #str
#define stringify(str) stringify_helper(str)

//TODO : faire la vérif de sortie des dames (cf wikipedia)
static const char* enumToStr[] = { "NOBODY", "BLACK", "WHITE" };
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

static int compute_delta_move(cuint src, cuint dest, const Player player)
{
    int delta_move = dest - src;
    if(src==0 && player==BLACK)
    {
        delta_move = 25-dest;
    }
    else if(dest==25)
    {
        delta_move = player==BLACK ? src : dest-src;
    }
    return delta_move<0 ? -delta_move : delta_move;
}
static bool compute_can_take_from(cuint src, cuint bar[2], const Square board[24], const Player player){
    bool can_take_from = false;
    if(src==0)
    {
        can_take_from = bar[player]>0;
    }
    else
    {
        can_take_from = board[src-1].owner==player && board[src-1].nbDames>0;
    }
    return can_take_from;
}
static bool has_farer_piece(const Square board[24], cuint dest, const Player player)
{
    bool has_farer = false;
    if(player==BLACK)
    {
        unsigned int index = 6;
        unsigned int end   = dest+1;
        for(;index>end; --index)
        {
            if(board[index-1].owner==player)
            {
                has_farer = true;
            }
        }
    }
    if(player == WHITE)
    {
        unsigned int index = 19;
        unsigned int end   = dest-1;
        for(;index<end; ++index)
        {
            if(board[index-1].owner==player)
            {
                has_farer = true;
            }
        }
    }
    return has_farer;
}
 static bool compute_can_put_to(int delta , cuint src, cuint dest, const SGameState* const state, const Player player, Dice dices[2])
{
    bool can_put_to = false;
    if(dest==25)
    {
        can_put_to = !check_side(state, player) &&
                     ( !has_farer_piece(state->board, src, player) ||
                       dices[0] == delta ||
                       dices[1] == delta
                     );
    }
    else
    {
        can_put_to = state->board[dest-1].owner==player ||
                     state->board[dest-1].owner==NOBODY ||
                     state->board[dest-1].nbDames<2;
    }
    return can_put_to;
}

//TODO : changer les paramêtres pour enlever les trucs inutiles
//TODO : refactoring ?
//TODO : 0 -> zone out
//TODO : 25 -> zone de fin
int check_move(const SMove move,
        Dice dices[],
        cuint nb_dices,
        const Player player,
        SGameState const * const state)
{
    uint err = 0;
    int delta_move = compute_delta_move(move.src_point, move.dest_point, player);
    bool can_take_from = compute_can_take_from(move.src_point, state->bar, state->board, player);
    bool can_put_to = compute_can_put_to(delta_move, move.src_point, move.dest_point, state, player, dices);
    const bool has_out = state->bar[player]>0;
    char messTmp[20];
    if ( !can_take_from ||
         !can_put_to ||
         (has_out && move.src_point!=0)
         )
    {
        if(!can_put_to) strcpy(messTmp, stringify(!can_put_to));
        if(!can_take_from) strcpy(messTmp,stringify(!can_take_from));
        if(has_out && move.src_point!=0) strcpy(messTmp,stringify(has_out));
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
                strcpy(messTmp,stringify(!can_move));
            }
            else
            {
                err = 0;
                if(dices[0] != dices[1]) dices[i] = 7;
            }
            ++i;
        }
    }
    if(err>0)
    {
        char mess[50];
        sprintf(mess, "%s à fait une erreur : %s\n", enumToStr[player+1], messTmp);
        logging("referee_logger", mess, ERROR);
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
            char mess[50];
            sprintf(mess, "%s essaie de sortir un pion alors qu'il lui reste des pions hors de la zone de fin\n", enumToStr[player+1]);
            logging("referee_logger", mess, WARNING);
        }
        ++index;
    }
    return err;

}

int move_all(
        SGameState *const state,
        SMove const * const moves,
        cuint nb_moves,
        Dice dices[],
        cuint nb_dices,
        const Player player )
{
    set_level("referee_logger", LOG_LVL);
    uint errors = 0;
    uint i = 0;
    SGameState copy = *state;
    while(i<nb_moves && errors==0)
    {
        if(check_move(moves[i], dices, nb_dices, player, state))
        {
            ++errors;
            logging("referee_logger", "Annulation des mouvements\n", WARNING);
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
    {
        move_to_end(state, movement, player);
    }
    else if(movement.src_point == 0)
    {
        move_from_out(state, movement, player);
    }
    else
    {
        move_in_board(state, movement, player);
    }
    unsigned int nbDame = 0;
    if(movement.src_point>0) nbDame = state->board[movement.src_point-1].nbDames;
    else nbDame = state->bar[player];
    sprintf(mess, "la case %2d à %2d pions\n", movement.src_point, nbDame);
    logging("referee_logger", mess, INFO);
    nbDame = 0;
    if(movement.dest_point>24) nbDame = state->out[player];
    else nbDame = state->board[movement.dest_point-1].nbDames;
    sprintf(mess, "la case %2d à %2d pions\n", movement.dest_point, nbDame);
    logging("referee_logger", mess, INFO);
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
