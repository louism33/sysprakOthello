//
// Created by louis on 12/4/19.
//

#include "testkibasicthinking.h"

#include "../../thinker/board.h"
#include "../alex.h"
#include <stdlib.h>
#include <stdio.h>


int testOneTrivialBestMove() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    int *board = b->board;
    int moveTime = 1000;

    for (int i = 0; i < 63; i++) {
        board[i] = getBlack();
    }

    for (int i = 0; i < 8; i++) {
        board[i] = getWhite();
        board[48 + i] = getWhite();
        board[i * 8] = getWhite();
    }

    board[0] = getEmpty();
    board[2] = getBlack();

    board[41] = getWhite();
    board[42] = getWhite();
    board[43] = getWhite();

    board[54] = getBlack();
    board[18] = getWhite();
    b->sideToMove = getWhite();

//    printBoardSide(b);
//    int www = 0;
//    int bbb = 0;
//    printBoardSide(b);
//    makeMove(b, 63);
//    makeMove(b, 0);
//
//    printBoardSide(b);
//
//    for (int i = 0; i < 64; i++) {
//        if (board[i] == getBlack()){
//            bbb++;
//        }else if (board[i] == getWhite()){
//            www++;
//        }
//    }
//
//    printf("w: %d, b: %d\n", www, bbb);
//


//    printBoardSide(b);
    // there are two legal moves from this position, 0 and 63. 63 wins, 0 loses
    MOVE correctMove = 63;
    MOVE move = getBestMove(b, moveTime);

    makeMove(b, move);

    if (move != correctMove || getWinner(b) != getWhite()) {
//        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}


int testOneTrivialBestMoveSwitch() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    int *board = b->board;
    int moveTime = 1000;

    for (int i = 0; i < 63; i++) {
        board[i] = getBlack();
    }

    for (int i = 0; i < 8; i++) {
        board[i] = getWhite();
        board[48 + i] = getWhite();
        board[i * 8] = getWhite();
    }

    board[0] = getEmpty();
    board[2] = getBlack();

    board[41] = getWhite();
    board[42] = getWhite();
    board[43] = getWhite();

    board[54] = getBlack();
    board[18] = getWhite();
    b->sideToMove = getBlack();

    printBoardSide(b);
    int www = 0;
    int bbb = 0;
//    printBoardSide(b);
//    makeMove(b, 63);
//    makeMove(b, 0);

//    printBoardSide(b);

//    for (int i = 0; i < 64; i++) {
//        if (board[i] == getBlack()) {
//            bbb++;
//        } else if (board[i] == getWhite()) {
//            www++;
//        }
//    }
//
//    printf("w: %d, b: %d\n", www, bbb);



//    printBoardSide(b);
    // there are two legal moves from this position, 0 and 63. 63 wins, 0 loses
    MOVE correctMove = 63;
    MOVE move = getBestMove(b, moveTime);

    makeMove(b, move);

    if (move != correctMove || getWinner(b) != getBlack()) {
//        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}




int testPossibleGameWin() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;
    int moveTime = 1000;

    board[20] = board[28] = getBlack();
    board[19] = board[12] = getWhite();

    b->sideToMove = getWhite();

    MOVE correctMove = 36;
    MOVE move = getBestMove(b, moveTime);

    makeMove(b, move);

    if (move != correctMove || getWinner(b) != getWhite()) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}


int testPossibleGameWin2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;
    int moveTime = 1000;

    board[20] = board[28] = board[36] = getBlack();
    board[19] = board[12] = getWhite();

    b->sideToMove = getWhite();

    MOVE correctMove = 44;
    MOVE move = getBestMove(b, moveTime);

    makeMove(b, move);

    if (move != correctMove || getWinner(b) != getWhite()) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}



int testPossibleGameWin3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;
    int moveTime = 1000;

    board[20] = board[28] = board[36] = board[44] = getBlack();
    board[19] = board[12] = getWhite();

    b->sideToMove = getWhite();

    MOVE correctMove = 52;
    MOVE move = getBestMove(b, moveTime);

    makeMove(b, move);

    if (move != correctMove || getWinner(b) != getWhite()) {
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

// very important test. Black has the opportunity to make a move, which loses the game next turn. He should not make it!
int testAvoidLossFromPreviousTest() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;
    int moveTime = 1000;

    board[20] = getBlack();
    board[19] = board[12] = board[28] = getWhite();

    b->sideToMove = getBlack();

    MOVE incorrectMove = 36;
    MOVE move = getBestMove(b, moveTime);

    if (move == incorrectMove) {
        printBoardSide(b);
        makeMove(b, move);
        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! You will lose game next turn. Received move:'%d'!\n",
                move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}


// very important test. Black has the opportunity to make a move, which loses the game next turn. He should not make it!
int testAvoidLossNextMove() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;
    int moveTime = 1000;

    board[20] = getBlack();
    board[19] = board[12] = board[21] = getWhite();

    b->sideToMove = getBlack();

//    printBoardSide(b);

    MOVE incorrectMove1 = 18;
    MOVE incorrectMove2 = 22;
    MOVE move = getBestMove(b, moveTime);
    makeMove(b, move);
//    printBoardSide(b);
    MOVE move2 = getBestMove(b, moveTime);

    makeMove(b, move2);
//    printBoardSide(b);

//
//    if (move == incorrectMove1 || move == incorrectMove2) {
//        printBoardSide(b);
//        makeMove(b, move);
//        printBoardSide(b);
//        fprintf(stderr, "*** FAILED AN AI TEST! You will lose game next turn. Received move:'%d'!\n",
//                move);
//        freeBoardStruct(b);
//        exit(1);
//    }

    freeBoardStruct(b);
    return 0; // success
}

int testPickDrawOverLoss() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    int *board = b->board;
    int moveTime = 1000;

    for (int i = 0; i < 63; i++) {
        board[i] = getBlack();
    }

    for (int i = 0; i < 8; i++) {
        board[i] = getWhite();
        board[48 + i] = getWhite();
        board[i * 8] = getWhite();
    }

    board[0] = getEmpty();
    board[2] = getBlack();

    board[41] = getWhite();
    board[42] = getWhite();
    board[43] = getWhite();

    board[54] = getBlack();
    board[18] = getWhite();

    board[7] = getBlack();
    b->sideToMove = getWhite();

    MOVE correctMove = 63;
    MOVE move = getBestMove(b, moveTime);

    makeMove(b, move);

    MOVE move2 = getBestMove(b, moveTime);
    makeMove(b, move2);

    if (move != correctMove || getWinner(b) != getDraw()) {
//        printBoardSide(b);
        fprintf(stderr, "*** FAILED AN AI TEST! Expected move: '%d' from this position, but received move:'%d'!\n",
                correctMove, move);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int kiTestsBasicThinking() {
    testOneTrivialBestMove();
    testOneTrivialBestMoveSwitch();

    testPossibleGameWin();
    testPossibleGameWin2();
    testPossibleGameWin3();

    testAvoidLossFromPreviousTest();
    testAvoidLossNextMove();

    testPickDrawOverLoss();

    return 0;
}