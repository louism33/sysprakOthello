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

int testStar() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int i = 20;
    board[i] = getWhite();
    board[i - 9] = board[i - 8] = board[i - 7] = board[i - 1] = board[i + 1] = board[i + 7] = board[i + 8] = board[i +
                                                                                                                   9] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 8;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    return 0; // success
}


int testNoLegalMoves() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = getWhite();
    board[20] = getBlack();

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    return 0; // success
}


int testNoLegalMoves2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = getWhite();
    board[63] = getBlack();

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    return 0; // success
}


int testNoLegalMovesBecauseGameOver() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    for (int i = 0; i < 20; i++) {
        board[i] = getWhite();
    }
    for (int i = 20; i < 63; i++) {
        board[i] = getBlack();
    }

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    return 0; // success
}


int testStartingBoard1() {
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testStartingBoard2() {
    // starting board with other player first
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    SIDE_TO_MOVE player = switchPlayer(getStartingPlayer());
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testBoardAfterOneMove() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);
    board[27] = getBlack();
    board[26] = getBlack();
//    printBoardLouisSide(b, getWhite());

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testOnePositionleft() //nach links bewegen
{
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int mypos = 20;    //mein
    int enemypos = 19; //Gegener

    board[mypos] = getWhite();
    board[enemypos] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
//    printBoardLouisSide(b, player);

    int *moves = malloc(64 * sizeof(int));
    int *legalMoves = getLegalMovesOnePosition(board, moves, mypos, getBlack());

    int correctMove = 18;

    if (correctMove != legalMoves[0]) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A MOVE TEST! Expected %d from this position, but received %d!\n",
                correctMove, legalMoves[0]);
        free(b);
        free(moves);
        free(board);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    free(moves);
    free(board);
    return 0; // success
}

int testOnePositionright() //nach rechts bewegen
{
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    int mypos = 18;
    int enemypos = 19;

    board[mypos] = getWhite();
    board[enemypos] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
//    printBoardLouisSide(b, player);

    int *moves = malloc(64 * sizeof(int));
    // int *finalMove=malloc(64 * sizeof(int));
    int *legalMoves = getLegalMovesOnePosition(board, moves, mypos, getBlack());

    int correctMove = 20;

    if (correctMove != legalMoves[0]) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A MOVE TEST! Expected %d from this position, but received %d!\n",
                correctMove, legalMoves[0]);
        free(b);
        free(board);
        free(moves);
        exit(1);
    }

    // printf("test successful\n\n");
    free(b);
    free(board);
    free(moves);
    return 0; // success
}

int testWeirdImpossibleBoard() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = getWhite();
    board[1] = board[8] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testWeirdImpossibleBoard2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = getWhite();
    board[1] = board[8] = board[9] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testWeirdImpossibleBoardOben() // rand test
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = board[20] = board[21] = getWhite();
    board[11] = board[12] = board[13] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 5;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testWeirdImpossibleBoardUnten() // rand test
{
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[44] = board[45] = board[46] = getWhite();
    board[52] = board[53] = board[54] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 5;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidTheDuplicateMove() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = board[4] = getWhite();
    board[1] = board[3] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidTheDuplicateMove3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = board[4] = getWhite();
    board[1] = board[3] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidTheDuplicateMove2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = board[4] = board[10] = getBlack();
    board[1] = board[3] = board[18] = getWhite();

    SIDE_TO_MOVE player = getBlack();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //  printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[0] = board[4] = board[18] = getBlack();
    board[1] = board[3] = board[10] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[56] = board[42] = board[60] = getBlack();
    board[57] = board[50] = board[59] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    //    printBoardLouisSide(board, player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard8() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[34] = board[42] = board[43] = board[44] = getWhite();
    board[49] = board[35] = board[56] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = board[35] = board[34] = board[29] = getBlack();
    board[20] = board[28] = board[36] = board[44] = getWhite();

    SIDE_TO_MOVE player = getBlack();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 7;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[40] = board[48] = board[56] = board[49] = board[50] = getWhite();
    board[41] = board[57] = getBlack();

    SIDE_TO_MOVE player = getBlack();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard5() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[44] = board[45] = board[37] = getWhite();
    board[54] = board[63] = board[36] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard6() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[20] = board[21] = board[29] = getWhite();
    board[28] = board[14] = board[7] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard7() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[53] = board[54] = board[55] = board[63] = getWhite();
    board[46] = board[47] = getBlack();

    SIDE_TO_MOVE player = getBlack();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int testAvoidMovingOffTheSideOfTheBoard9() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[26] = board[27] = board[28] = board[29] = board[30] = board[31] = board[27] = board[35] = board[43] = board[51] = board[52] = board[53] = board[50] = getWhite();
    board[18] = board[19] = board[20] = board[44] = board[58] = getBlack();

    SIDE_TO_MOVE player = getBlack();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 10;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        free(b);
        free(board);
        exit(1);
    }
    // printf("test successful\n\n");
    free(b);
    free(board);
    return 0; // success
}

int basicTests() {
    //no legal moves
    testNoLegalMoves();
    testNoLegalMoves2();
    testNoLegalMovesBecauseGameOver();

    //begin test
    testStartingBoard1();
    testStartingBoard2();

    //one move
    testBoardAfterOneMove();
    testOnePositionleft();
    testOnePositionright();

    testWeirdImpossibleBoard();
    testWeirdImpossibleBoard2();
    testWeirdImpossibleBoardOben();
    testWeirdImpossibleBoardUnten();

    //Duplicate
    testAvoidTheDuplicateMove();
    testAvoidTheDuplicateMove2();

    //random
    testStar();
    testAvoidMovingOffTheSideOfTheBoard();
    testAvoidMovingOffTheSideOfTheBoard2();
    testAvoidMovingOffTheSideOfTheBoard3();
    testAvoidMovingOffTheSideOfTheBoard4();
    testAvoidMovingOffTheSideOfTheBoard5();
    testAvoidMovingOffTheSideOfTheBoard6();
    testAvoidMovingOffTheSideOfTheBoard7();
    testAvoidMovingOffTheSideOfTheBoard8();
    testAvoidMovingOffTheSideOfTheBoard9();

    return 0; // success
}

int fullTestSuite() {
    return basicTests();
}