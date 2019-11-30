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


int perft(BOARD_STRUCT *boardStruct, int depth, int passed) {
    return perftFunction(boardStruct, depth, passed, 0);
}

int perftFunction(BOARD_STRUCT *boardStruct, int depth, int passed, int debug) {
    int ans = 0;

    BOARD board = boardStruct->board;

    if (depth == 0) {
        return 1;
    }

    if (depth == 1) { // todo // do not ignore leaf nodes with no moves ?
        int i = getTotalNumberOfLegalMoves(board, switchPlayer(boardStruct->sideToMove));
        return getTotalNumberOfLegalMoves(board, switchPlayer(boardStruct->sideToMove));
    }

    MOVES moves = malloc(64 * sizeof(MOVE));
    getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    int totalMoves = countMoves(moves);

    if (totalMoves == 0) {
        if (passed) {
            return 0; // gameover
        }

        switchPlayerStruct(boardStruct);
        ans += perft(boardStruct, depth - 1, 1);
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
            copyBoardStruct(b, boardStruct, 64);

            SIDE_TO_MOVE s1 = boardStruct->sideToMove;

            if (debug) {
                printf("\n\n\n\n");
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
                printf("   MAKING move %d\n", move);
                printf("   index move %d\n", boardStruct->stackIndexMove);
                printf("   ->  stack move-1 %d\n", boardStruct->moveStack[boardStruct->stackIndexMove - 1]);
                printf("   index object %d\n", boardStruct->stackIndexObject);
                printf("   -> stack object-1 %d\n", boardStruct->stack[boardStruct->stackIndexObject - 1]);
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

            ans += perft(boardStruct, depth - 1, 0);

            if (debug) {
                printf("after perft with depth %d\n", (depth - 1));
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
                printf("     UNnNNNNNNnNNMAKING move %d\n", move);
                printf("   index move %d\n", boardStruct->stackIndexMove);
                printf("   ->  stack move-1 %d\n", boardStruct->moveStack[boardStruct->stackIndexMove - 1]);
                printf("   index object %d\n", boardStruct->stackIndexObject);
                printf("   -> stack object-1 %d\n", boardStruct->stack[boardStruct->stackIndexObject - 1]);
            }

            unmakeMove(boardStruct);

            if (debug) {
                printf("unmade\n");
                printBoardLouisSide(boardStruct, boardStruct->sideToMove);
                printf("\n\n\n\n\n");
            }

            if (areBoardStructsDifferent(b, boardStruct, 64)) {
                printf("My struct:\n");
                printBoardSide(boardStruct);
                printf("correct:\n");
                printBoardSide(b);
                fprintf(stderr, "issue in move() or unmake()!!!\n");
                exit(1);
            }

            free(b);
        }
    }

    free(moves);

    return ans;
}


int perftDivide(BOARD_STRUCT *boardStruct, int depth) {
    BOARD board = boardStruct->board;

    MOVES moves = malloc(64 * sizeof(MOVE));
    getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    int totalMoves = countMoves(moves);

    printBoardSide(boardStruct);
    printf("total moves from this position: %d\n", totalMoves);

    MOVE move;
    int index = 0;
    while (1) {
        move = moves[index++];
        if (move == getLastMove()) {
            break;
        }

        printf("move: %d ", move);
        printf("total children: ");

        makeMove(boardStruct, move);

        int children = perft(boardStruct, depth - 1, 0);

        printf("%d\n", children);

        unmakeMove(boardStruct);
    }

    free(moves);

    return 0;
}


int fromCommandLine(int depth) {
    int boardSize = 64;
    // starting board normal
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    resetBoardToStarter(board);

    perftDivide(b, depth);
}

int testBasicBoard() {
    int boardSize = 64;
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
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 2, 0);
        int correct = 12;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 3, 0);
        int correct = 56;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }

    if (1) {
        int received = perft(b, 4, 0);
        int correct = 244;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }

    if (0) {
//        perftDivide(b, 5);
//        exit(0);
        int received = perft(b, 5, 0);
        int correct = 1396;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }

    if (0) {
        int received = perft(b, 6, 0);
        int correct = 8200;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }

    if (0) {
        int received = perft(b, 7, 0);
        int correct = 55092;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }


    if (0) {
        int received = perft(b, 8, 0);
        int correct = 390216;
        if (received != correct) {
            fprintf(stderr, "FAILED A PERFT TEST! wrong number of moves received: %d, but correct: %d\n", received,
                    correct);
            free(b);
            exit(1);
        }

        if (areBoardStructsDifferent(b, testBoardStruct, boardSize)) {
            printBoardSide(testBoardStruct);
            printBoardSide(b);
            fprintf(stderr, "FAILED A perft TEST: board structs are different after calling perft!!\n");
            free(b);
            free(testBoardStruct);
            exit(1);
        }
    }


    free(b);

    return 0; // success
}







//void perftTests() {
//
//    uint64_t p3 = Perft::splitPerft(board, 3);
////    uint64_t p3 = Perft::perftP(board, 3);
//    if (p3 != 56) {
//        throw
//        std::runtime_error("Perft failed on depth 3, expected " + std::__cxx11::to_string(56) + ", got " +
//                           std::__cxx11::to_string(p3));
//    }
//
//    uint64_t p4 = Perft::perft(board, 4);
//    if (p4 != 244) {
//        throw
//        std::runtime_error("Perft failed on depth 4, expected " + std::__cxx11::to_string(244) + ", got " +
//                           std::__cxx11::to_string(p4));
//    }
//
//    uint64_t p5 = Perft::perft(board, 5);
//    if (p5 != 1396) {
//        throw
//        std::runtime_error("Perft failed on depth 5, expected " + std::__cxx11::to_string(1396) + ", got " +
//                           std::__cxx11::to_string(p5));
//    }
//
//    uint64_t p6 = Perft::perft(board, 6);
//    if (p6 != 8200) {
//        throw
//        std::runtime_error("Perft failed on depth 6, expected " + std::__cxx11::to_string(8200) + ", got " +
//                           std::__cxx11::to_string(p6));
//    }
//
////    uint64_t p7 = Perft::perftP(board, 7);
//    uint64_t p7 = Perft::splitPerft(board, 7);
//    if (p7 != 55092) {
//        throw
//        std::runtime_error("Perft failed on depth 7, expected " + std::__cxx11::to_string(55092) + ", got " +
//                           std::__cxx11::to_string(p7));
//    }
//
//}

int perftSuite() {

    testBasicBoard();

    return 0;
}