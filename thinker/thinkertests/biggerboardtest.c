//
// Created by louis on 12/1/19.
//

#include <stdlib.h>
#include <stdio.h>

#include "../board.h"
#include "biggerboardtest.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"

int testStartingBoardBigger() {
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZeroCustom(b, 12, 12);
    int *board = b->board;

    resetBoardToZero(board);

    board[41] = board[54] = getWhite();
    board[42] = board[53] = getBlack();

//    printBoardLouis(b);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);

    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);

        MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
        getLegalMovesAllPositions(board, switchPlayer(b->sideToMove), moves);
        printf("moves:\n");
        printMoves(moves);

        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }

//    printf("test successful\n\n");
    freeBoardStruct(b);
    return 0; // success
}


int testSuiteBigBoard() {
    testStartingBoardBigger();
}