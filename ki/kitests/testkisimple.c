//
// Created by louis on 12/4/19.
//

#include "testkisimple.h"

#include "../../thinker/board.h"
#include "../alex.h"
#include <stdlib.h>
#include <stdio.h>

int testKINoLegalMoves() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int moveTime = 1000;

    board[0] = getWhite();
    board[20] = getBlack();

    b->sideToMove = getBlack();

    MOVE correctMove = getPassMove();
    MOVE move = getBestMove(b, moveTime);

    if (move != correctMove) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int testKINoLegalMoves2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int moveTime = 1000;

    board[0] = getWhite();
    board[63] = getBlack();

    b->sideToMove = getBlack();

    MOVE correctMove = getPassMove();
    MOVE move = getBestMove(b, moveTime);

    if (move != correctMove) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int testKINoLegalMovesBecauseGameOver() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;
    int moveTime = 1000;

    for (int i = 0; i < 20; i++) {
        board[i] = getWhite();
    }
    for (int i = 20; i < 63; i++) {
        board[i] = getBlack();
    }

    b->sideToMove = getBlack();

    MOVE correctMove = getPassMove();
    MOVE move = getBestMove(b, moveTime);

    if (move != correctMove) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}



int testKIOneLegalMove() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int moveTime = 1000;

    board[21] = getWhite();
    board[20] = getBlack();

    b->sideToMove = getBlack();

    MOVE correctMove = 22;
    MOVE move = getBestMove(b, moveTime);

    if (move != correctMove) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int testKIOneLegalMove2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int moveTime = 1000;

    board[21] = getWhite();
    board[20] = getBlack();

    b->sideToMove = getWhite();

    MOVE correctMove = 19;
    MOVE move = getBestMove(b, moveTime);

    if (move != correctMove) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int kiTestsSimple() {
    testKINoLegalMoves();
    testKINoLegalMoves2();
    testKINoLegalMovesBecauseGameOver();

    testKIOneLegalMove();
    testKIOneLegalMove2();

    return 0;
}