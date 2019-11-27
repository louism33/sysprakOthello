//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_THINKER_H
#define ALEXTHEFRIENDLYAI_THINKER_H

#include "board.h"

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35


void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard);

MOVE doThink(BOARD_STRUCT* board, int moveTime);

#endif //ALEXTHEFRIENDLYAI_THINKER_H
