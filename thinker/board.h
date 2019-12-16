//
// Created by louis on 11/24/19.
//

#ifndef SYSPRAKOTHELLO_BOARD_H
#define SYSPRAKOTHELLO_BOARD_H

#include <stdint.h>

typedef int DIRECTION;
typedef unsigned long long int DIRECTION_MASK;

typedef int MOVE;
typedef int SIDE_TO_MOVE;


typedef int64_t STACK_OBJECT;
typedef STACK_OBJECT *STACK;
typedef MOVE *MOVE_STACK;
typedef int STACK_INDEX;

typedef int *BOARD;

typedef struct boardShm {
    int breite;
    int hoehe;
    BOARD board;
    SIDE_TO_MOVE currentPlayerId; 
} boardShm;

typedef struct BOARD_STRUCT {
    // BOARD has our board array, a side to move to determine the current player, and a stack to enable unmakeMove()
    BOARD board;
    SIDE_TO_MOVE sideToMove;

    STACK stack; // used to store moves made
    MOVE_STACK moveStack; // used to store move kill data

    STACK_INDEX stackIndexObject; // used to remember where we are in the stack, object
    STACK_INDEX stackIndexMove; // used to remember where we are in the stack, move

} BOARD_STRUCT;

// can't have more than 64 moves (and can't have exactly 64 either)
typedef int *MOVES;

int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER);

int countMoves(MOVES allMoves);

void printBoardSide(BOARD_STRUCT *boardStruct);

void printMoves(MOVES moves);

char *getPrettyMove(int move, char *antwort);

void printBoard(BOARD board);

void initialiseBoardStructToStarter(BOARD_STRUCT *boardStruct);

void initialiseBoardStructToZero(BOARD_STRUCT *boardStruct);

void initialiseBoardStructToZeroCustom(BOARD_STRUCT *boardStruct, int rows, int columns);

void resetBoardToStarter(BOARD board); // todo do we want to export this one?
void resetBoardToZero(BOARD board); // todo do we want to export this one?

void freeBoardStruct(BOARD_STRUCT *boardStruct);

int removeDuplicates(MOVES speicher, int index);

int getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE TARGET_PLAYER, MOVES allMoves);

SIDE_TO_MOVE switchPlayer(SIDE_TO_MOVE sideToMove);

SIDE_TO_MOVE switchPlayerStruct(BOARD_STRUCT *boardStruct);

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


int makeMoveSide(BOARD_STRUCT *boardStruct, int legalPosition, SIDE_TO_MOVE TARGET_PLAYER);

int makeMove(BOARD_STRUCT *boardStruct, int legalPosition);


int pushObject(BOARD_STRUCT *boardStruct, STACK_OBJECT stackObject);

STACK_OBJECT popObject(BOARD_STRUCT *boardStruct);

int pushMove(BOARD_STRUCT *boardStruct, MOVE moveStackObject);

STACK_OBJECT popMove(BOARD_STRUCT *boardStruct);

int addToStackObject(STACK_OBJECT *stackObject, int direction, int numberOfKills);

int getDirectionSize();

DIRECTION getNorth();

DIRECTION getNorthWest();

DIRECTION getWest();

DIRECTION getSouthWest();

DIRECTION getSouth();

DIRECTION getSouthEast();

DIRECTION getEast();

DIRECTION getNorthEast();



int getWinner(BOARD_STRUCT *boardStruct);
int isGameOver(BOARD_STRUCT *boardStruct);



int getBoardSize();

void setBoardSize(int rows, int columns);

int getRowSize();

int getColumnSize();

void setRowSize(int rows);

void setColumnSize(int columns);

int getStandardBoardSize();

int setBoardToStandardSize();

int setBoardToCustomSize(int rows, int columns);


#endif //SYSPRAKOTHELLO_BOARD_H


