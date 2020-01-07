//
// Created by louis on 12/9/19.
//

#include "testkibasicstrategy.h"

#include "../../thinker/board.h"
#include "../alex.h"
#include <stdlib.h>
#include <stdio.h>

int testPickUpCorner() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(b);
    int *board = b->board;
    int moveTime = 4000;

    board[2] = board[8] = getBlack();
    board[16] = board[1] = getWhite();

    b->sideToMove = getBlack();

    MOVE bestMove = 0;
    MOVE move = getBestMoveMultiThreaded(b, moveTime);

    if (move != bestMove) {
//        printBoardSide(b);
//        makeMove(b, move);
//        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Did not move to corner. Received move:'%d'!\n",
                move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int kiTestsBasicStrategy() {
    testPickUpCorner();

    return 0;
}