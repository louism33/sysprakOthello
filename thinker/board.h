//
// Created by louis on 11/24/19.
//

#ifndef SYSPRAKOTHELLO_BOARD_H
#define SYSPRAKOTHELLO_BOARD_H

#include <stdint.h>

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
    STACK_OBJECT *stackArray;
} STACK;

typedef int *BOARD;

typedef struct BOARD_STRUCT {
    // BOARD has our board array, a side to move to determine the current player, and a stack to enable unmakeMove()
    BOARD board;
    SIDE_TO_MOVE sideToMove;
    STACK *stack; // used to unmake a move
} BOARD_STRUCT;

// can't have more than 64 moves (and can't have exactly 64 either)
typedef int *MOVES;

int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER);

void printBoardSide(BOARD_STRUCT *boardStruct);

void printBoard(BOARD board);

void initialiseBoardStructToStarter(BOARD_STRUCT *boardStruct);

void initialiseBoardStructToZero(BOARD_STRUCT *boardStruct);

void resetBoardToStarter(BOARD board); // todo do we want to export this one?

void freeBoardStruct(BOARD_STRUCT *boardStruct);

int *removeDuplicates(MOVES speicher, int index);

MOVES getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE TARGET_PLAYER, MOVES allMoves);

SIDE_TO_MOVE switchPlayer(SIDE_TO_MOVE sideToMove);
SIDE_TO_MOVE switchPlayerStruct(BOARD_STRUCT* boardStruct);

SIDE_TO_MOVE getStartingPlayer();

MOVE getLastMove();

SIDE_TO_MOVE getBlack();

SIDE_TO_MOVE getWhite();

SIDE_TO_MOVE getEmpty();

int unmakeMove(BOARD_STRUCT *boardStruct);

int copyBoardStruct(BOARD_STRUCT *destinationBoardStruct, BOARD_STRUCT *sourceBoardStruct, int n);

int copyBoard(BOARD destinationBoard, BOARD sourceBoard, int n);

int areBoardStructsDifferent(BOARD_STRUCT *destinationBoardStruct, BOARD_STRUCT *sourceBoardStruct, int n);

int areBoardsDifferent(BOARD destinationBoard, BOARD sourceBoard, int n);



BOARD makeMoveSide(BOARD_STRUCT* boardStruct, int legalPosition, SIDE_TO_MOVE TARGET_PLAYER);
BOARD makeMove(BOARD_STRUCT* boardStruct, int legalPosition);

#endif //SYSPRAKOTHELLO_BOARD_H


