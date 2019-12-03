//
// Created by louis on 11/30/19.
//

#include "perft.h"
#include <stdlib.h>

#include <stdio.h>
#include "makemovetests.h"
#include "../board.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"


int perftFunction(BOARD_STRUCT *boardStruct, int depth, int passed, int debug) {
    int ans = 0;

    BOARD board = boardStruct->board;

    if (depth == 0) {
        return 1;
    }

    if (depth == 1) {
        int i = getTotalNumberOfLegalMoves(board, switchPlayer(boardStruct->sideToMove));
        return i > 0 ? i : 1; // if there are no moves from here, it is still a end node
    }

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        if (passed) {
            return 0; // gameover
        }

        switchPlayerStruct(boardStruct);
        ans += perftFunction(boardStruct, depth - 1, 1, debug);
        switchPlayerStruct(boardStruct);
    } else {
        MOVE move;
        int index = 0;
        while (1) {
            move = moves[index++];
            if (move == getLastMove()) {

                break;
            }

            BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
            initialiseBoardStructToZero(b);
            copyBoardStruct(b, boardStruct, getStandardBoardSize());

            SIDE_TO_MOVE s1 = boardStruct->sideToMove;

            if (debug) {
                printf("\n\n\n\n");
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
                printf("   MAKING move %d\n", move);
                printf("   index move %d\n", boardStruct->stackIndexMove);
                printf("   ->  stack move-1 %d\n", boardStruct->moveStack[boardStruct->stackIndexMove - 1]);
                printf("   index object %d\n", boardStruct->stackIndexObject);
                printf("   -> stack object-1 %lu\n", boardStruct->stack[boardStruct->stackIndexObject - 1]);
            }

            makeMove(boardStruct, move);
            if (debug) {
                printf("made\n");
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
            }

            SIDE_TO_MOVE s2 = boardStruct->sideToMove;

            if (s1 == s2) {
                fprintf(stderr, "side to move not flipped!!!\n");
                exit(1);
            }

            ans += perftFunction(boardStruct, depth - 1, 0, debug);

            if (debug) {
                printf("after perft with depth %d\n", (depth - 1));
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
                printf("     UNnNNNNNNnNNMAKING move %d\n", move);
                printf("   index move %d\n", boardStruct->stackIndexMove);
                printf("   ->  stack move-1 %d\n", boardStruct->moveStack[boardStruct->stackIndexMove - 1]);
                printf("   index object %d\n", boardStruct->stackIndexObject);
                printf("   -> stack object-1 %lu\n", boardStruct->stack[boardStruct->stackIndexObject - 1]);
            }

            unmakeMove(boardStruct);

            if (debug) {
                printf("unmade\n");
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
                printf("\n\n\n\n\n");
            }

            if (areBoardStructsDifferent(b, boardStruct, getStandardBoardSize())) {
                printf("My struct:\n");
                printBoardSide(boardStruct);
                printf("correct:\n");
                printBoardSide(b);
                fprintf(stderr, "issue in move() or unmake()!!!\n");
                exit(1);
            }

            freeBoardStruct(b);
        }
    }

    free(moves);

    return ans;
}

int perft(BOARD_STRUCT *boardStruct, int depth, int passed) {
    return perftFunction(boardStruct, depth, passed, 0);
}


int perftDivide(BOARD_STRUCT *boardStruct, int depth) {
    BOARD board = boardStruct->board;

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    printBoardSide(boardStruct);
    printf("moves from this position: %d\n", totalMoves);

    int totalNodes = 0;
    MOVE move;
    int index = 0;
    char *m = malloc(3 * sizeof(char));
    while (1) {
        move = moves[index++];
        if (move == getLastMove()) {
            break;
        }

        printf("move: %s, index %d, ", getPrettyMove(move, m), move);
        printf("total children: ");

        makeMove(boardStruct, move);

        int children = perft(boardStruct, depth - 1, 0);
        totalNodes += children;
        printf("%d\n", children);

        unmakeMove(boardStruct);
    }

    printf("total nodes from this position: %d\n", totalNodes);

    free(moves);
    free(m);

    return 0;
}

int fromCommandLine(int depth) {
    int boardSize = getStandardBoardSize();
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    perftDivide(b, depth - 9);

    freeBoardStruct(b);
}

int testBasicBoard() {
    int boardSize = getStandardBoardSize();
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    BOARD_STRUCT *testBoardStruct = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(testBoardStruct);

    copyBoardStruct(testBoardStruct, b, boardSize);

    SIDE_TO_MOVE player = getStartingPlayer();
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);

    if (1) {
        int received = perft(b, 1, 0);
        int correct = 4;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 2, 0);
        int correct = 12;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 3, 0);
        int correct = 56;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 4, 0);
        int correct = 244;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 5, 0);
        int correct = 1396;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 6, 0);
        int correct = 8200;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 7, 0);
        int correct = 55092;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }


    if (1) {
        int received = perft(b, 8, 0);
        int correct = 390216;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 9, 0);
        int correct = 3005288;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    if (0) {
        int received = perft(b, 10, 0);
        int correct = 24571284;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            freeBoardStruct(b);
            freeBoardStruct(testBoardStruct);
            exit(1);
        }
    }

    freeBoardStruct(b);
    freeBoardStruct(testBoardStruct);

    return 0; // success
}


int perftSuite() {

    testBasicBoard();

    return 0;
}