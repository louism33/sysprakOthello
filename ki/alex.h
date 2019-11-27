//
// Created by louis on 11/25/19.
//

#ifndef SYSPRAKOTHELLO_ALEX_H
#define SYSPRAKOTHELLO_ALEX_H

#include "thinker/board.h"

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0



// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK + WHITE)



int getBestMove(BOARD_STRUCT* boardStruct, int moveTime);

#endif; //SYSPRAKOTHELLO_ALEX_H
