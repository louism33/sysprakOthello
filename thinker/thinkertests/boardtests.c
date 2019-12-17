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

#define DRAW (0)

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

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 8;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
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

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
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

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int testNoLegalMovesBecauseGameOver() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    for (int i = 0; i < 20; i++) {
        board[i] = getWhite();
    }
    for (int i = 20; i <= 63; i++) {
        board[i] = getBlack();
    }

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int testStartingBoard1() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int testStartingBoard2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    SIDE_TO_MOVE player = switchPlayer(getStartingPlayer());
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
    return 0; // success
}

int testBoardAfterOneMove() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);
    board[27] = getBlack();
    board[26] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
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
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 2;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
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
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 3;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
    return 0; // success
}

int testWeirdImpossibleBoardLinks() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[34] = getWhite();
    board[33] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
    return 0; // success
}

int testWeirdImpossibleBoardRechts() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[37] = getWhite();
    board[38] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
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
        freeBoardStruct(b);
        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);
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
        freeBoardStruct(b);
        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);
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
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);
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
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
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
        freeBoardStruct(b);
        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);
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
        freeBoardStruct(b);
        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);
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
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);
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
        freeBoardStruct(b);
        exit(1);
    }
    freeBoardStruct(b);

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
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

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
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

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
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

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
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

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
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

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
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = getWhite();
    board[35] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[51] = board[52] = getWhite();
    board[59] = board[60] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[48] = board[49] = getWhite();
    board[56] = board[57] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[54] = board[55] = getWhite();
    board[62] = board[63] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten_RechtUnten_LinksUnten() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[51] = board[52] = board[53] = getWhite();
    board[59] = board[60] = board[61] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten_RechtUnten_LinksUnten2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[43] = board[44] = board[45] = getWhite();
    board[51] = board[52] = board[53] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 5;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten_RechtUnten_LinksUnten3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[40] = board[41] = board[42] = getWhite();
    board[48] = board[49] = board[50] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testUnten_RechtUnten_LinksUnten4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[41] = board[42] = board[43] = getWhite();
    board[49] = board[50] = board[51] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 5;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtUnten() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[41] = getWhite();
    board[50] = board[59] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtUnten2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[45] = getWhite();
    board[54] = board[63] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtUnten3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[13] = getWhite();
    board[22] = board[31] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtUnten4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[36] = getWhite();
    board[45] = board[54] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksUnten() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[43] = getWhite();
    board[50] = board[57] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksUnten2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[26] = getWhite();
    board[33] = board[40] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksUnten3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[35] = getWhite();
    board[42] = board[49] = board[56] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtOben() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = getWhite();
    board[12] = board[5] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtOben2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = getWhite();
    board[14] = board[7] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtOben3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[45] = getWhite();
    board[38] = board[31] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtOben4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[40] = getWhite();
    board[33] = board[26] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRechtOben5() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[28] = getWhite();
    board[21] = board[14] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksOben() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[9] = board[0] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksOben2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[20] = getWhite();
    board[11] = board[2] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }

    freeBoardStruct(b);

    return 0; // success
}

int testLinksOben3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[36] = getWhite();
    board[27] = board[18] = board[9] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksOben4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[9] = board[0] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }

    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksOben5() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = getWhite();
    board[10] = board[1] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }

    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinksOben6() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = getWhite();
    board[18] = board[9] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }

    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testOben() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[10] = getWhite();
    board[2] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testOben2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[10] = board[11] = getWhite();
    board[2] = board[3] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }

    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testOben_RechtOben_LinksOben() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[16] = board[17] = board[18] = getWhite();
    board[8] = board[9] = board[10] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testOben_RechtOben_LinksOben2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = board[17] = board[18] = getWhite();
    board[11] = board[9] = board[10] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 5;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testOben_RechtOben_LinksOben3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = board[20] = board[21] = getWhite();
    board[11] = board[12] = board[13] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 5;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testOben_RechtOben_LinksOben4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[22] = board[23] = board[21] = getWhite();
    board[14] = board[15] = board[13] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 4;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRecht() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = getWhite();
    board[22] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRecht2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[22] = getWhite();
    board[23] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testRecht3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = getWhite();
    board[21] = board[22] = board[20] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinks() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[17] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinks2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[17] = getWhite();
    board[16] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 0;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testLinks3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[20] = getWhite();
    board[19] = board[18] = board[17] = getBlack();


    SIDE_TO_MOVE player = getWhite();
    //printBoardLouisSide(b, player);
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
    int myNumberOfMoves = getTotalNumberOfLegalMoves(board, targetPlayer);
    int correctNumberOfMoves = 1;

    if (myNumberOfMoves != correctNumberOfMoves) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected %d moves from this position, but received %d!\n",
                correctNumberOfMoves, myNumberOfMoves);
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testWinner() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));

    initialiseBoardStructToZero(b);
    int *board = b->board;

    for (int i = 0; i < 32; i++) {
        board[i] = getWhite();
    }
    for (int j = 32; j < getBoardSize(); j++) {
        board[j] = getBlack();
    }

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
//    printBoardLouisSide(b, player);
    int connrectGameOver = getGameOver();
    int correctWinner = DRAW;

    int myGameOver = isGameOver(b);
    int myWinner;
    if (myGameOver == connrectGameOver) {
        if (myGameOver == getGameNotOver()) {
//            printf("Game is not over.\n");
            return 0;
        }
        myWinner = getWinner(b);
        if (myWinner != correctWinner) {
            fprintf(stderr, "getWinner is false.\n");
            freeBoardStruct(b);

            exit(1);
        }
    } else {
        fprintf(stderr, "GameOver Test is false.\n");
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testWinner2() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    for (int i = 0; i < 32; i++) {
        board[i] = getWhite();
    }

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
//    printBoardLouisSide(b, player);
    int connrectGameOver = getGameOver();
    int correctWinner = getWhite();

    int myWinner;
    int myGameOver = isGameOver(b);

    if (myGameOver == connrectGameOver) {
        if (myGameOver == getGameNotOver()) {
//            printf("Game is not over.\n");
            return 0;
        }
        myWinner = getWinner(b);
        if (myWinner != correctWinner) {
            fprintf(stderr, "getWinner is false.\n");
            freeBoardStruct(b);

            exit(1);
        }
    } else {
        fprintf(stderr, "GameOver Test is false.\n");
        freeBoardStruct(b);

        exit(1);
    }
    // printf("test successful\n\n");
    freeBoardStruct(b);

    return 0; // success
}

int testWinner3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));;
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[20] = getWhite();
    board[19] = board[18] = board[17] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
//    printBoardLouisSide(b, player);
    int connrectGameOver = getGameNotOver();
    int correctWinner = getBlack();

    int myWinner;
    int myGameOver = isGameOver(b);

    if (myGameOver == connrectGameOver) {
        if (myGameOver == getGameNotOver()) {
            freeBoardStruct(b);
//            printf("Game is not over.\n");
            return 0;
        }
        myWinner = getWinner(b);
        if (myWinner != correctWinner) {
            fprintf(stderr, "getWinner is false.\n");
            freeBoardStruct(b);

            exit(1);
        }
    } else {
        fprintf(stderr, "GameOver Test is false.\n");
        freeBoardStruct(b);

        exit(1);
    }

    // printf("test successful\n\n");
    freeBoardStruct(b);

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

    // one move
    testBoardAfterOneMove();
//    testOnePositionleft();
//    testOnePositionright();

    testWeirdImpossibleBoard();
    testWeirdImpossibleBoard2();
    testWeirdImpossibleBoardLinks();
    testWeirdImpossibleBoardRechts();
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

    // 8 Richtungen test
    testUnten();
    testUnten2();
    testUnten3();
    testUnten4();

    testRechtUnten();
    testRechtUnten2();
    testRechtUnten3();
    testRechtUnten4();

    testLinksUnten();
    testLinksUnten2();
    testLinksUnten3();

    testUnten_RechtUnten_LinksUnten();
    testUnten_RechtUnten_LinksUnten2();
    testUnten_RechtUnten_LinksUnten3();
    testUnten_RechtUnten_LinksUnten4();

    testRechtOben();
    testRechtOben2();
    testRechtOben3();
    testRechtOben4();
    testRechtOben5();

    testLinksOben();
    testLinksOben2();
    testLinksOben3();
    testLinksOben4();
    testLinksOben5();
    testLinksOben6();

    testOben();
    testOben2();

    testOben_RechtOben_LinksOben();
    testOben_RechtOben_LinksOben2();
    testOben_RechtOben_LinksOben3();
    testOben_RechtOben_LinksOben4();

    testRecht();
    testRecht2();
    testRecht3();

    testLinks();
    testLinks2();
    testLinks3();
    //Daoben gibt es 63 Test! und laufen alles gut.

    testWinner();
    testWinner2();
    testWinner3();

    return 0; // success
}

int fullTestSuite() {
    return basicTests();
}