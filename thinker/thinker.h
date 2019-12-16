//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_THINKER_H
#define ALEXTHEFRIENDLYAI_THINKER_H

#include "board.h"

void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard);
int doThinks(boardShm *infoBoard, int moveTime);
//MOVE doThink(BOARD_STRUCT *board, int moveTime);
MOVE doThink(BOARD_STRUCT *board, int moveTime);
#endif //ALEXTHEFRIENDLYAI_THINKER_H
