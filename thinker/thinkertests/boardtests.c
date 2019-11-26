//
// Created by louis on 11/23/19.
//
#include "../board.h"
#include "boardtests.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"
#include <stdlib.h>
#include <stdio.h>
#include "../board.c"
#include "../board.h"

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
#define SWITCH_PLAYER_CONSTANT (BLACK + WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

int switchPlayer(SIDE_TO_MOVE sideToMove)
{
    return SWITCH_PLAYER_CONSTANT - sideToMove;
}

int testOnePosition()
{
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int mypos = 20;
    int enemypos = 19;

    board[mypos] = WHITE;
    board[enemypos] = BLACK;

    

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    printBoardLouisSide(b, player);

    int *moves = malloc(64 * sizeof(int));
    int * legalMoves = getLegalMovesOnePosition(board, moves, mypos, BLACK);




    
    int correctMove = 18;

    if (correctMove != legalMoves[0])
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A MOVE TEST! Expected %d from this position, but received %d!\n",
                correctMove, legalMoves[0]);
        free(b);
        exit(1);
    }

    printf("test successful\n\n");
    free(b);
    free(moves);
    return 0; // success
}

int testOnePositionright()
{
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int mypos = 18;
    int enemypos = 19;

    board[mypos] = WHITE;
    board[enemypos] = BLACK;

    

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    printBoardLouisSide(b, player);

    int *moves = malloc(64 * sizeof(int));
    int * legalMoves = getLegalMovesOnePosition(board, moves, mypos, BLACK);




    
    int correctMove = 20;

    if (correctMove != legalMoves[0])
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A MOVE TEST! Expected %d from this position, but received %d!\n",
                correctMove, legalMoves[0]);
        free(b);
        exit(1);
    }

    printf("test successful\n\n");
    free(b);
    free(moves);
    return 0; // success
}

int testStartingBoard1()
{
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[STARTING_WHITE_POSITION_1] = board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;

    SIDE_TO_MOVE player = STARTING_PLAYER;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testNothing()
{
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[20] = WHITE;
    board[19] = board[18] = board[17] = board[16] = board[15] = board[14] = board[13] = board[12] = board[11] = board[10] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    printBoardLouisSide(b, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testStartingBoard2()
{
    // starting board with other player first
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[STARTING_WHITE_POSITION_1] = board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;

    SIDE_TO_MOVE player = switchPlayer(STARTING_PLAYER);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testBoardAfterOneMove()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = board[STARTING_BLACK_POSITION_2] = BLACK;
    board[27] = BLACK;
    board[26] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testWeirdImpossibleBoard()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = WHITE;
    board[1] = board[8] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testWeirdImpossibleBoardright()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[5] = board[13] = board[21] = WHITE;
    board[14] = board[6] = board[22] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}
int testWeirdImpossibleBoard2()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = WHITE;
    board[1] = board[8] = board[9] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testSides()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[1] = board[9] = board[17] = WHITE;
    board[2] = board[10] = board[18] = BLACK;

    SIDE_TO_MOVE player = BLACK;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(b, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testSides2()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[5] = board[13] = board[21] = WHITE;
    board[6] = board[14] = board[22] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(b, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidTheDuplicateMove()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = board[4] = WHITE;
    board[1] = board[3] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidTheDuplicateMove2()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = board[4] = board[10] = BLACK;
    board[1] = board[3] = board[18] = WHITE;

    SIDE_TO_MOVE player = BLACK;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard()
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    ;
    int *board = b->board;

    board[0] = board[4] = board[18] = BLACK;
    board[1] = board[3] = board[10] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves)
    {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    printf("test successful\n\n");
    free(b);
    return 0; // success
}

int basicTests()
{

    testOnePosition();
    testOnePositionright();

    testNothing();
    testStartingBoard1();
    testStartingBoard2();
    testBoardAfterOneMove();
    testWeirdImpossibleBoardright();
    testWeirdImpossibleBoard();
    testWeirdImpossibleBoard2();

    testSides();
    // testSides2();

    //    testAvoidTheDuplicateMove();
    //    testAvoidTheDuplicateMove2();
    //
    //    testAvoidMovingOffTheSideOfTheBoard();

    return 0; // success
}

int fullTestSuite()
{
    return basicTests();
}