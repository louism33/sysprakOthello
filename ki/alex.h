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

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK + WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

int getBestMove(BOARD_STRUCT* boardStruct, int moveTime);

#endif; //SYSPRAKOTHELLO_ALEX_H
