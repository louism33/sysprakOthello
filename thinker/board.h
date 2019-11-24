//
// Created by louis on 11/24/19.
//

#ifndef SYSPRAKOTHELLO_BOARD_H
#define SYSPRAKOTHELLO_BOARD_H

#include <stdint.h>

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

typedef int MOVE;
typedef int SIDE_TO_MOVE;

typedef struct STACK_OBJECT {
    // hack because we set BLACK and WHITE to one and two,
    // and we want to access these through array index without caring about conversion
    int64_t pieces[3];
} STACK_OBJECT;

typedef struct STACK {
    // we allow 64 moves to be stored on the stack. Technically still risky, as more than 64 moves can occur due to passing,
    // but unrealistic given compute constraints
    STACK_OBJECT stackArray[64];
} STACK;

typedef int* BOARD;

typedef struct BOARD_STRUCT  {
    // BOARD has our board array, a side to move to determine the current player, and a stack to enable unmakeMove()
    BOARD board;
    SIDE_TO_MOVE sideToMove;
    STACK stack; // used to unmake a move
} BOARD_STRUCT;

// can't have more than 64 moves (and can't have exactly 64 either)
typedef int* MOVES;

int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER);

void printBoard(BOARD board);

#endif //SYSPRAKOTHELLO_BOARD_H


