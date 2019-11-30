//
// Created by louis on 11/30/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "unmakemovetests.h"
#include "../board.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"

int flipTurnTest() {
    int boardSize = 64;
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    switchPlayerStruct(b);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are the same after slipping turn!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    switchPlayerStruct(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are different after two flips!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }


    switchPlayerStruct(b);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are the same after slipping turn!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }


    switchPlayerStruct(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are different after two flips!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }


    free(b);
    free(testBoardStruct);
    return 0; // success
}

int copyBoardStructTest() {
    int boardSize = 64;

    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    BOARD board = b->board;
    resetBoardToStarter(board);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    copyBoardStruct(testBoardStruct, b, boardSize);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are different after calling copy()!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}


int copyBoardStructTest2() {
    int boardSize = 64;

    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    BOARD board = b->board;
    resetBoardToStarter(board);

    board[10] = board[11] = board[63] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    copyBoardStruct(testBoardStruct, b, boardSize);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are different after calling copy()!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int startingBoard1Test() {
    int boardSize = 64;
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    BOARD board = b->board;

    resetBoardToStarter(board);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    copyBoardStruct(testBoardStruct, b, boardSize);

//    printBoardSide(b);
    makeMove(b, 26);
//    printBoardSide(b);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    unmakeMove(b);
//    printBoardSide(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }


    printf("test successful\n\n");
    free(b);
    free(testBoardStruct);
    return 0; // success
}

int fullTestSuiteUnmakeMoveTests() {
    flipTurnTest();
    copyBoardStructTest();
    copyBoardStructTest2();
    startingBoard1Test();
}
