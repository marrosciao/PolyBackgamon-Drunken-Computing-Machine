#ifndef _REFEREE_INCLUDED
#define _REFEREE_INCLUDED

#include"backgammon.h"

typedef const unsigned char Dice;
typedef const unsigned int cuint;
typedef unsigned int uint;

//! return 0 if the movement are correct, 1 else
int check_move(const SMove, Dice[], cuint);

#endif
