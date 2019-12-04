//
// Created by louis on 11/27/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "../board.h"
#include "boardtests2.h"
#include "../thinker.h"

int testRemoveDuplicatesNoDuplicates() {
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int));
    int index = 0;

    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 2;
    moves[index++] = 3;
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == getLastMove()) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == getLastMove()) {
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
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int)); // todo replace all this with MOVE
    int index = 0;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == getLastMove()) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == getLastMove()) {
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
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int));
    int index = 0;

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 2;
    moves[index++] = 3;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == getLastMove()) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == getLastMove()) {
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
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int));
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
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (moves[i] == getLastMove()) {
            break;
        }
        for (int j = i + 1;; j++) {
            if (moves[j] == getLastMove()) {
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
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int));
    MOVES movesTest = malloc(getStandardBoardSize() * sizeof(int));
    int index = 0;

    movesTest[0] = 0;
    movesTest[1] = getLastMove();

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (movesTest[i] == getLastMove()) {
            break;
        }

        int fail = 1;
        for (int j = 0;; j++) {
            if (moves[j] == getLastMove()) {
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
            free(movesTest);
            exit(1);
        }
    }

    free(moves);
    free(movesTest);

    return 0; // success
}



// tests to make sure our method does not delete moves
int testRemoveDuplicatesLostMove2() {
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int));
    MOVES movesTest = malloc(getStandardBoardSize() * sizeof(int));
    int index = 0;

    movesTest[0] = 0;
    movesTest[1] = 1;
    movesTest[2] = getLastMove();

    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = 1;
    moves[index++] = 1;
    moves[index++] = 0;
    moves[index++] = 0;
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (movesTest[i] == getLastMove()) {
            break;
        }

        int fail = 1;
        for (int j = 0;; j++) {
            if (moves[j] == getLastMove()) {
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
            free(movesTest);
            exit(1);
        }
    }

    free(moves);
    free(movesTest);

    return 0; // success
}


// tests to make sure our method does not delete moves
int testRemoveDuplicatesLostMove3() {
    MOVES moves = malloc(getStandardBoardSize() * sizeof(int));
    MOVES movesTest = malloc(getStandardBoardSize() * sizeof(int));
    int index = 0;

    movesTest[0] = 0;
    movesTest[1] = 1;
    movesTest[2] = 4;
    movesTest[3] = 2;
    movesTest[4] = 3;
    movesTest[5] = getLastMove();

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
    moves[index++] = getLastMove();

    removeDuplicates(moves, index);

    for (int i = 0;; i++) {
        if (movesTest[i] == getLastMove()) {
            break;
        }

        int fail = 1;
        for (int j = 0;; j++) {
            if (moves[j] == getLastMove()) {
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
            free(movesTest);
            exit(1);
        }
    }

    free(moves);
    free(movesTest);

    return 0; // success
}


int basicTests2() {
    testRemoveDuplicatesNoDuplicates();
    testRemoveDuplicatesAllDuplicates();
    testRemoveDuplicatesManyDuplicates();
    testRemoveDuplicatesManyDuplicates2();

    testRemoveDuplicatesLostMove();
    testRemoveDuplicatesLostMove2();
    testRemoveDuplicatesLostMove3();

    return 0; // success
}

int fullTestSuiteBoard2() {
    return basicTests2();
}