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


int perft(BOARD_STRUCT *boardStruct, int depth) {
    int ans = 0;

    printf("perft depth %d\n", depth);

    BOARD board = boardStruct->board;

    if (depth == 0) {
        return 1;
    }

    if (depth == 1) { // todo // do not ignore leaf nodes with no moves ?
        int i = getTotalNumberOfLegalMoves(board, switchPlayer(boardStruct->sideToMove));

        printf("i: %d\n ", i);
        printBoardLouisSide(boardStruct, boardStruct->sideToMove);
        if (i == 0) {
            exit(1);
        }

        return getTotalNumberOfLegalMoves(board, switchPlayer(boardStruct->sideToMove));
    }

    MOVES moves = malloc(64 * sizeof(MOVE));
    getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    MOVE move;
    int index = 0;
    while (1) {
        move = moves[index++];
        if (move == getLastMove()) {
            break;
        }

        SIDE_TO_MOVE s1 = boardStruct->sideToMove;

        printBoardLouisSide(boardStruct, boardStruct->sideToMove);
        printf("making move %d\n", move);

        makeMove(boardStruct, move);
        printBoardLouisSide(boardStruct, boardStruct->sideToMove);
        SIDE_TO_MOVE s2 = boardStruct->sideToMove;

        if (s1 == s2) {
            fprintf(stderr, "side to move not flipped!!!\n");
            exit(1);
        }

        ans += perft(boardStruct, depth - 1);
        unmakeMove(boardStruct);
    }

    free(moves);

    return ans;
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

    if (0) {
        int received = perft(b, 1);
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
        int received = perft(b, 2);
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

    free(b);

    return 0; // success
}







//void perftTests() {
//    // thanks to http://www.aartbik.com/MISC/reversi.html
//    auto *board = new
//    uint64_t p2 = Perft::perft(board, 2);
//    if (p2 != 12) {
//        throw
//        std::runtime_error("Perft failed on depth 2, expected " + std::__cxx11::to_string(12) + ", got " +
//                           std::__cxx11::to_string(p2));
//    }
//
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