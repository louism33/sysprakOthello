//
// Created by louis on 11/23/19.
//

#include "boardtests.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"
#include <stdlib.h>
#include <stdio.h>

#define MOVE int
#define SIDE_TO_MOVE int
#define BOARD int*
#define MOVES int*

#define BLACK 2
#define WHITE 1

#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

#define STARTING_PLAYER BLACK
#define SWITCH_PLAYER_CONSTANT 3

int switchPlayer(SIDE_TO_MOVE sideToMove){
    return SWITCH_PLAYER_CONSTANT - sideToMove;
}

int testStartingBoard1(){
    // starting board normal
    BOARD board = malloc(64*sizeof(int));

    board[STARTING_WHITE_POSITION_1] = board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;

    printBoardLouis(board);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, STARTING_PLAYER);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves){
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }

    return 0; // success
}

int testStartingBoard2(){
    // starting board with other player first
    BOARD board = malloc(64*sizeof(int));

    board[STARTING_WHITE_POSITION_1] = board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;

    printBoardLouis(board);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, switchPlayer(STARTING_PLAYER));
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves){
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }

    return 0; // success
}

int basicTests(){
    testStartingBoard1();
    testStartingBoard2();

    return 0; // success
}