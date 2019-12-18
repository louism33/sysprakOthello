//
// Created by louis on 11/30/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "unmakemovetests.h"
#include "../board.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"

int flipTurnTest()
{
    int boardSize = getStandardBoardSize();
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    switchPlayerStruct(b);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are the same after slipping turn!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    switchPlayerStruct(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are different after two flips!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    switchPlayerStruct(b);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(testBoardStruct);
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: board structs are the same after slipping turn!!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    switchPlayerStruct(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
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

int copyBoardStructTest()
{
    int boardSize = getStandardBoardSize();

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

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
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

int copyBoardStructTest2()
{
    int boardSize = getStandardBoardSize();

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

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
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

int stackpushPopTest()
{
    int boardSize = getStandardBoardSize();

    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    BOARD board = b->board;
    resetBoardToStarter(board);

    STACK_OBJECT stackObject = 666;

    pushObject(b, stackObject);

    if (popObject(b) != stackObject)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }

    MOVE moveStackObject = 0;

    pushMove(b, moveStackObject);

    if (popMove(b) != moveStackObject)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }

    free(b);
    return 0; // success
}

int stackpushPopManyTest()
{
    int boardSize = getStandardBoardSize();

    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);

    BOARD board = b->board;
    resetBoardToStarter(board);

    pushObject(b, 1);
    pushObject(b, 11);
    pushObject(b, 2);
    pushObject(b, 22);
    pushObject(b, 3);

    if (popObject(b) != 3)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }
    if (popObject(b) != 22)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }
    if (popObject(b) != 2)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }
    if (popObject(b) != 11)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }

    pushMove(b, 0);
    pushMove(b, 43);
    if (popMove(b) != 43)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }

    if (popMove(b) != 0)
    {
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }

    if (popObject(b) != 1)
    {
        fprintf(stderr, "xxxFAILED A UNMAKEMOVE TEST: push and pop are different!!\n");
        free(b);
        exit(1);
    }
    free(b);
    return 0; // success
}

int manualBabyTest()
{
    int boardSize = getStandardBoardSize();
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    BOARD board = b->board;

    resetBoardToZero(board);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    board[0] = player;
    board[8] = targetPlayer;

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    copyBoardStruct(testBoardStruct, b, boardSize);

    MOVE move = 16;

    // in this test we simulate making a move by manually adding everything
    board[move] = board[8] = player;
    switchPlayerStruct(b);

    STACK_OBJECT stackObject = 0;

    addToStackObject(&stackObject, getNorth(), 1);

    if (stackObject == 0)
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, stackObject did not seem to get updated\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    pushObject(b, stackObject);

    pushMove(b, move);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int manualBaby2Test()
{
    int boardSize = getStandardBoardSize();
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    BOARD board = b->board;

    resetBoardToZero(board);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    board[16] = player;
    board[8] = targetPlayer;

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    copyBoardStruct(testBoardStruct, b, boardSize);

    MOVE move = 0;

    // in this test we simulate making a move by manually adding everything
    board[move] = board[8] = player;
    switchPlayerStruct(b);

    STACK_OBJECT stackObject = 0;

    addToStackObject(&stackObject, getSouth(), 1);

    if (stackObject == 0)
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, stackObject did not seem to get updated\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    pushObject(b, stackObject);

    pushMove(b, move);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int startingBoard1MANUALTest()
{
    int boardSize = getStandardBoardSize();
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

    MOVE move = 26;

    // in this test we simulate making a move by manually adding everything
    board[move] = board[27] = player;
    switchPlayerStruct(b);

    STACK_OBJECT stackObject = 0;

    addToStackObject(&stackObject, getEast(), 1);

    if (stackObject == 0)
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, stackObject did not seem to get updated\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    pushObject(b, stackObject);
    pushMove(b, move);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int startingBoard1MANUAL2Test()
{
    int boardSize = getStandardBoardSize();
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

    MOVE move = 26;

    // in this test we simulate making a move by manually adding everything
    board[move] = board[27] = player;
    switchPlayerStruct(b);

    STACK_OBJECT stackObject = 0;

    addToStackObject(&stackObject, getEast(), 1);

    if (stackObject == 0)
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, stackObject did not seem to get updated\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    pushObject(b, stackObject);

    pushMove(b, move);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    MOVE move2 = 20;

    board[move2] = board[28] = switchPlayer(player);
    switchPlayerStruct(b);

    STACK_OBJECT stackObject2 = 0;

    addToStackObject(&stackObject2, getSouth(), 1);

    pushObject(b, stackObject2);

    pushMove(b, move2);

    unmakeMove(b);
    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int startingBoard1MANUAL3Test()
{
    int boardSize = getStandardBoardSize();
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

    MOVE move = 26;

    // in this test we simulate making a move by manually adding everything
    board[move] = board[27] = player;
    switchPlayerStruct(b);

    STACK_OBJECT stackObject = 0;

    addToStackObject(&stackObject, getEast(), 1);

    if (stackObject == 0)
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, stackObject did not seem to get updated\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    pushObject(b, stackObject);

    pushMove(b, move);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    MOVE move2 = 20;
    board[move2] = board[28] = switchPlayer(player);
    switchPlayerStruct(b);
    STACK_OBJECT stackObject2 = 0;
    addToStackObject(&stackObject2, getSouth(), 1);
    pushObject(b, stackObject2);
    pushMove(b, move2);

    MOVE move3 = 37;
    board[move3] = board[36] = player;
    switchPlayerStruct(b);
    STACK_OBJECT stackObject3 = 0;
    addToStackObject(&stackObject3, getWest(), 1);
    pushObject(b, stackObject3);
    pushMove(b, move3);

    MOVE move4 = 25;
    board[move4] = board[26] = board[27] = switchPlayer(player);
    switchPlayerStruct(b);
    STACK_OBJECT stackObject4 = 0;
    addToStackObject(&stackObject4, getEast(), 2);
    pushObject(b, stackObject4);
    pushMove(b, move4);

    MOVE move5 = 19;
    board[move5] = board[28] = board[27] = player;
    switchPlayerStruct(b);
    STACK_OBJECT stackObject5 = 0;
    addToStackObject(&stackObject5, getSouth(), 1);
    addToStackObject(&stackObject5, getSouthEast(), 1);
    pushObject(b, stackObject5);
    pushMove(b, move5);

    unmakeMove(b);
    unmakeMove(b);
    unmakeMove(b);
    unmakeMove(b);
    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int moveunmakeTest()
{
    int boardSize = getStandardBoardSize();
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

    MOVE move = 26;

    makeMove(b, move);

    STACK_OBJECT stackObject = 0;

    addToStackObject(&stackObject, getEast(), 1);

    if (stackObject == 0)
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, stackObject did not seem to get updated\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    pushObject(b, stackObject);

    pushMove(b, move);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    MOVE move2 = 20;

    board[move2] = board[28] = switchPlayer(player);
    switchPlayerStruct(b);

    STACK_OBJECT stackObject2 = 0;

    addToStackObject(&stackObject2, getSouth(), 1);

    pushObject(b, stackObject2);

    pushMove(b, move2);

    unmakeMove(b);
    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int moveunmakeStackTest()
{
    int boardSize = getStandardBoardSize();
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

    MOVE move = 26;
    //    printBoardSide(b);
    makeMove(b, move);
    //    printBoardSide(b);

    if (!areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "FAILED A UNMAKEMOVE TEST, made move but board structs are the same!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    //    MOVE move2 = 20;
    //
    //    board[move2] = board[28] = switchPlayer(player);
    //    switchPlayerStruct(b);
    //
    //    STACK_OBJECT stackObject2 = 0;
    //
    //    addToStackObject(&stackObject2, getSouth(), 1);
    //
    //    pushObject(b, stackObject2);
    //
    //    pushMove(b, move2);
    //
    //    unmakeMove(b);
    unmakeMove(b);

    if (areBoardStructsDifferent(b, testBoardStruct, boardSize))
    {
        printBoardSide(b);
        fprintf(stderr, "xFAILED A UNMAKEMOVE TEST, move() unmakemove() called, but structs different!\n");
        free(b);
        free(testBoardStruct);
        exit(1);
    }

    free(b);
    free(testBoardStruct);
    return 0; // success
}

int fullTestSuiteUnmakeMoveTests()
{
    flipTurnTest();
    copyBoardStructTest();
    copyBoardStructTest2();

    stackpushPopTest();
    stackpushPopManyTest();

    manualBabyTest();
    manualBaby2Test();
    startingBoard1MANUALTest();
    startingBoard1MANUAL2Test();
    startingBoard1MANUAL3Test();

    moveunmakeTest();
    moveunmakeStackTest();
    return 0;
}
