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



// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)




void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard);

MOVE doThink(BOARD_STRUCT* board, int moveTime);

#endif //ALEXTHEFRIENDLYAI_THINKER_H
