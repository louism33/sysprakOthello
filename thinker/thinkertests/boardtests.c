//
// Created by louis on 11/23/19.
//

#include "boardtests.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../printBoard2.c"
#include "../../printBoard2.h"

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

int switchPlayer(SIDE_TO_MOVE sideToMove) {
    return SWITCH_PLAYER_CONSTANT - sideToMove;
}

int testStartingBoard1() {
    // starting board normal
    BOARD board = malloc(64 * sizeof(int));

    board[STARTING_WHITE_POSITION_1] = board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;

    SIDE_TO_MOVE player = STARTING_PLAYER;
//    printBoardLouisSide(board, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }

    printf("test successful\n\n");
    return 0; // success
}

int testStartingBoard2() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[STARTING_WHITE_POSITION_1] = board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;

    SIDE_TO_MOVE player = switchPlayer(STARTING_PLAYER);
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}

int testBoardAfterOneMove() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;
    board[27] = BLACK;
    board[26] = BLACK;

    SIDE_TO_MOVE player = WHITE;
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}


int testWeirdImpossibleBoard() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[0] = WHITE;
    board[1] = board[8] = BLACK;


    SIDE_TO_MOVE player = WHITE;
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}

int testWeirdImpossibleBoard2() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[0] = WHITE;
    board[1] = board[8] = board[9] = BLACK;


    SIDE_TO_MOVE player = WHITE;
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}

int testAvoidTheDuplicateMove() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[0] = board[4] = WHITE;
    board[1] = board[3] = BLACK;


    SIDE_TO_MOVE player = WHITE;
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}

int testAvoidTheDuplicateMove2() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[0] = board[4] = board[10] = BLACK;
    board[1] = board[3] = board[18] = WHITE;


    SIDE_TO_MOVE player = BLACK;
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard() {
    // starting board with other player first
    BOARD board = malloc(64 * sizeof(int));

    board[0] = board[4] = board[10] = BLACK;
    board[1] = board[3] = board[18] = WHITE;


    SIDE_TO_MOVE player = WHITE;
//    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, player);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(board, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        exit(1);
    }
    printf("test successful\n\n");
    return 0; // success
}

int basicTests() {
    testStartingBoard1();
    testStartingBoard2();
    testBoardAfterOneMove();
//
    testWeirdImpossibleBoard();
//    testWeirdImpossibleBoard2();
//
//    testAvoidTheDuplicateMove();
//    testAvoidTheDuplicateMove2();

//    testAvoidMovingOffTheSideOfTheBoard();

    return 0; // success
}