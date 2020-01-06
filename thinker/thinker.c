//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thinkertests/boardtests.h"
#include "board.h"
#include "../ki/alex.h"

MOVE doThink(BOARD_STRUCT *boardStruct, int moveTime) {
    printf("### Received doThink command from connector, time to move %d\n", moveTime);

    MOVE bestMove = getBestMoveMultiThreaded(boardStruct, moveTime);

    if (bestMove == getPassMove()) {
        fprintf(stderr, "### No moves from this position!!!\n");
        return getPassMove();
    }

    return bestMove;
}
