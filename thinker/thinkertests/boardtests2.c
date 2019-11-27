//
// Created by louis on 11/27/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "../board.h"
//#include "../board.c"
#include "boardtests2.h"
#include "../thinker.h"

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

#define LAST_MOVE (-1)


int testRemoveDuplicatesNoDuplicates() {
    MOVES moves = malloc(64 * sizeof(int));
    int index = 0;

    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 2;
    moves[index++] = 3;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == LAST_MOVE) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            if (moves[i] == moves[j]) {
                fprintf(stderr, "FAILED A BOARD TEST! Found duplicate move\n");
                free(moves);
                exit(1);
            }
        }
    }

    free(moves);

    return 0; // success
}


int testRemoveDuplicatesAllDuplicates() {
    MOVES moves = malloc(64 * sizeof(int));
    int index = 0;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == LAST_MOVE) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            if (moves[i] == moves[j]) {
                fprintf(stderr, "FAILED A BOARD TEST! Found duplicate move\n");
                free(moves);
                exit(1);
            }
        }
    }

    free(moves);

    return 0; // success
}


int testRemoveDuplicatesManyDuplicates() {
    MOVES moves = malloc(64 * sizeof(int));
    int index = 0;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 2;
    moves[index++] = 3;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == LAST_MOVE) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            if (moves[i] == moves[j]) {
                fprintf(stderr, "FAILED A BOARD TEST! Found duplicate move\n");
                free(moves);
                exit(1);
            }
        }
    }

    free(moves);

    return 0; // success
}


int testRemoveDuplicatesManyDuplicates2() {
    MOVES moves = malloc(64 * sizeof(int));
    int index = 0;

    moves[index++] = 4;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 2;
    moves[index++] = 3;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 1;
    moves[index++] = 1;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 3;
    moves[index++] = 1;
    moves[index++] = 4;
    moves[index++] = 4;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == LAST_MOVE) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            if (moves[i] == moves[j]) {
                fprintf(stderr, "FAILED A BOARD TEST! Found duplicate move\n");
                free(moves);
                exit(1);
            }
        }
    }

    free(moves);

    return 0; // success
}


// tests to make sure our method does not delete moves
int testRemoveDuplicatesLostMove() {
    MOVES moves = malloc(64 * sizeof(int));
    MOVES movesTest = malloc(64 * sizeof(int));
    int index = 0;

    movesTest[0] = 0;
    movesTest[1] = LAST_MOVE;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (movesTest[i] == LAST_MOVE) {
            break;
        }

        int fail = 1;
        for (int j = 0;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            // we have found our move, no need to fail
            if (movesTest[i] == moves[j]) {
                fail = 0;
            }
        }

        if(fail) {
            fprintf(stderr, "FAILED A BOARD TEST! findDuplicates deleted a move!!!\n");
            free(moves);
            exit(1);
        }
    }

    free(moves);

    return 0; // success
}



// tests to make sure our method does not delete moves
int testRemoveDuplicatesLostMove2() {
    MOVES moves = malloc(64 * sizeof(int));
    MOVES movesTest = malloc(64 * sizeof(int));
    int index = 0;

    movesTest[0] = 0;
    movesTest[1] = 1;
    movesTest[2] = LAST_MOVE;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 1;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

//    printf("---\n");
//    printf("->%d\n", movesTest);
//    printf("->%d\n", movesTest[0]);

    for (int i = 0;; i++) {
//        printf("->%d\n", movesTest[i]);
        if (movesTest[i] == LAST_MOVE) {
            break;
        }

        int fail = 1;
        for (int j = 0;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            // we have found our move, no need to fail
            if (movesTest[i] == moves[j]) {
                fail = 0;
            }
        }

        if(fail) {
            fprintf(stderr, "FAILED A BOARD TEST! findDuplicates deleted a move!!!\n");
            free(moves);
            exit(1);
        }
    }

    free(moves);

    return 0; // success
}


// tests to make sure our method does not delete moves
int testRemoveDuplicatesLostMove3() {
    MOVES moves = malloc(64 * sizeof(int));
    MOVES movesTest = malloc(64 * sizeof(int));
    int index = 0;

    movesTest[0] = 0;
    movesTest[1] = 1;
    movesTest[2] = 4;
    movesTest[3] = 2;
    movesTest[4] = 3;
    movesTest[5] = LAST_MOVE;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 1;
    moves[index++] = 0;
    moves[index++] = 2;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 2;
    moves[index++] = 1;
    moves[index++] = 3;
    moves[index++] = 3;
    moves[index++] = 4;
    moves[index++] = LAST_MOVE;

    removeDuplicates(moves, index);

//    printf("---\n");
//    printf("->%d\n", movesTest);
//    printf("->%d\n", movesTest[0]);

    for (int i = 0;; i++) {
//        printf("->%d\n", movesTest[i]);
        if (movesTest[i] == LAST_MOVE) {
            break;
        }

        int fail = 1;
        for (int j = 0;; j++) {
            if (moves[j] == LAST_MOVE) {
                break;
            }
            // we have found our move, no need to fail
            if (movesTest[i] == moves[j]) {
                fail = 0;
            }
        }

        if(fail) {
            fprintf(stderr, "FAILED A BOARD TEST! findDuplicates deleted a move!!!\n");
            free(moves);
            exit(1);
        }
    }

    free(moves);

    return 0; // success
}


int basicTests2() {
    testRemoveDuplicatesNoDuplicates();
    testRemoveDuplicatesAllDuplicates();
    testRemoveDuplicatesManyDuplicates();
    testRemoveDuplicatesManyDuplicates2();

    testRemoveDuplicatesLostMove();
    testRemoveDuplicatesLostMove2();

    return 0; // success
}

int fullTestSuiteBoard2() {
    return basicTests2();
}