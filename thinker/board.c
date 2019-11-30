#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "board.h"

#define ZEILE 8
#define SPALTE 8

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

MOVE getLastMove() {
    return LAST_MOVE;
}

SIDE_TO_MOVE getStartingPlayer() {
    return STARTING_PLAYER;
}

SIDE_TO_MOVE getBlack() {
    return BLACK;
}


SIDE_TO_MOVE getWhite() {
    return WHITE;
}


SIDE_TO_MOVE getEmpty() {
    return EMPTY;
}

SIDE_TO_MOVE switchPlayer(SIDE_TO_MOVE sideToMove) {
    return SWITCH_PLAYER_CONSTANT - sideToMove;
}

SIDE_TO_MOVE switchPlayerStruct(BOARD_STRUCT *boardStruct) {
    boardStruct->sideToMove = switchPlayer(boardStruct->sideToMove);
    return boardStruct->sideToMove;
}

void resetBoardToStarter(BOARD board) {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
    // todo, if the coordinates are not 8x8, this would be wrong, so make sure not to call this in gameloop
    board[STARTING_WHITE_POSITION_1] = WHITE;
    board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = BLACK;
    board[STARTING_BLACK_POSITION_2] = BLACK;
}

void resetBoardToZero(BOARD board) {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
}

void freeBoardStruct(BOARD_STRUCT *boardStruct) {
    //    free(boardStruct->stack->stackArray);
    //    free(boardStruct->stack);
    free(boardStruct->board);
}

void initialiseBoardStructMemory(BOARD_STRUCT *boardStruct) {
    boardStruct->board = malloc(64 * sizeof(int)); //todo careful of magic numbers!
    boardStruct->sideToMove = STARTING_PLAYER;
    boardStruct->stack = malloc(64 * sizeof(STACK_OBJECT)); //todo careful of magic numbers!
    boardStruct->moveStack = malloc(64 * sizeof(STACK_OBJECT)); //todo careful of magic numbers!
    boardStruct->stackIndexMove = 0;
    boardStruct->stackIndexObject = 0;
}

void initialiseBoardStructToStarter(BOARD_STRUCT *boardStruct) {
    initialiseBoardStructMemory(boardStruct);
    resetBoardToStarter(boardStruct->board);
}

void initialiseBoardStructToZero(BOARD_STRUCT *boardStruct) {
    initialiseBoardStructMemory(boardStruct);
    resetBoardToZero(boardStruct->board);
}


void printBoardSide(BOARD_STRUCT *boardStruct) {
    printBoard(boardStruct->board);
    if (boardStruct->sideToMove == BLACK) {
        printf("BLACK to move\n");
    } else {
        printf("WHITE to move\n");
    }
}

void printBoard(BOARD board) {
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");

    for (int i = 0; i < 8; i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < 8; j++) {
            int p = board[8 * i + j];
            if (p == BLACK) {
                printf("B ");
            } else if (p == WHITE) {
                printf("W ");
            }
                //            if (p)
                //            {
                //                printf("%d ", p);
                //            }
            else {
                printf("  ");
            }
        }
        printf("| %d", i + 1);
        printf("\n");
    }

    printf("  +-----------------+ \n");
    printf("    A B C D E F G H \n");
}

void addColourToSquare(BOARD board, SIDE_TO_MOVE sideToMove, MOVE move) {
    if (move < 0 || move > 63) {
        printf("Die Koordinaten liegen außerhalb des gültigen Bereichs. Bitte geben Sie sie erneut ein.\n");
        exit(1);
    } else if (board[move] != 0) {
        printf("Die Koordinaten sind bereits belegt!\n");
        exit(1);
    } else {
        if (sideToMove == BLACK) {
            board[move] = BLACK;
        } else {
            board[move] = WHITE;
        }
    }
}

int *getLegalMovesOnePosition(BOARD board, int *speicher, int position, SIDE_TO_MOVE TARGET_PLAYER) {
    int index = 0;
    int MY_PLAYER = 3 - TARGET_PLAYER;
    int zeile = (8 - position / 8);
    int spalte = position % 8;

    if (board[position] != MY_PLAYER) {
        printf("i don't have a player on this square\n");
        exit(1);
    }

    //for-Schleifer um nach rechts zu prüfen
    if (spalte != 6 && spalte != 7) {
        if (board[position + 1] == TARGET_PLAYER) {
            int i = position + 2;
            while (1) {
                if (i % 8 == 0) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i++;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach links zu prüfen
    if (spalte != 0 && spalte != 1) {
        if (board[position - 1] == TARGET_PLAYER) {
            int i = position - 2;
            while (1) {
                if (i % 8 == 7) {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i--;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach unten zu prüfen
    if (zeile != 1 && zeile != 2) {
        if (board[position + 8] == TARGET_PLAYER) {
            int i = position + 16;
            while (1) {
                if (i >= 64) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += 8;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }
    // for-Schleifer um nach oben zu prüfen
    if (zeile != 8 && zeile != 7) {
        if (board[position - 8] == TARGET_PLAYER) {
            int i = position - 16;
            while (1) {
                if (i < 0) //zeile
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i -= 8;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach rechts oben zu prüfen
    if (spalte != 6 && spalte != 7 && zeile != 8 && zeile != 7) {
        if (board[position - 7] == TARGET_PLAYER) {
            int i = position - 14;
            while (1) {
                if (i % 8 == 0) //spalte
                {
                    break;
                }
                if (i < 0) //zeile
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i -= 7;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach links oben zu prüfen
    if (spalte != 0 && spalte != 1 && zeile != 8 && zeile != 7) {
        if (board[position - 9] == TARGET_PLAYER) {
            int i = position - 18;
            while (1) {
                if (i % 8 == 7) //zeile
                {
                    break;
                }
                if (i < 0) //spalte
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i -= 9;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }
    // for-Schleifer um nach rechts unten zu prüfen
    if (spalte != 6 && spalte != 7 && zeile != 1 && zeile != 2) {
        if (board[position + 9] == TARGET_PLAYER) {
            int i = position + 18;
            while (1) {
                if (i >= 64) { //zeile
                    break;
                }
                if (i % 8 == 0) //spalte
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += 9;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }
    //  for-Schleifer um nach links unten zu prüfen
    if (spalte != 0 && spalte != 1 && zeile != 1 && zeile != 2) {
        if (board[position + 7] == TARGET_PLAYER) {
            int i = position + 14;
            while (1) {
                if (i >= 64) {
                    break;
                }
                if (i % 8 == 7) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += 7;
                    continue;
                }
                if (board[i] == EMPTY) {
                    speicher[index++] = i;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    speicher[index] = LAST_MOVE;
    return speicher;
}

// todo, optional, currently complexity of O(n^3), can be made to have complexity of O(n)
int *removeDuplicates(MOVES speicher, int index) {
    for (int i = 0; i < index - 1; i++) {
        for (int j = i + 1; j < index;) {
            if (speicher[i] == speicher[j]) {
                for (int k = j; k < index - 1; k++) {
                    speicher[k] = speicher[k + 1];
                }
                index--;
            } else {
                j++;
            }
        }
    }
    speicher[index] = LAST_MOVE;
    return speicher;
}
//todo board can be more than 8x8 !!!!

MOVES getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE TARGET_PLAYER, MOVES allMoves) {
    //MOVES allMoves= malloc(64 * sizeof(int)); // todo, clean up memory
    MOVES speicher = malloc(64 * sizeof(int));
    SIDE_TO_MOVE me = 3 - TARGET_PLAYER;
    int index = 0;
    for (int pos = 0; pos < 64; pos++) {
        if (board[pos] == me) {
            MOVES legalMovesFromHere = getLegalMovesOnePosition(board, speicher, pos, TARGET_PLAYER);
            int j = 0;
            while (1) {
                if (legalMovesFromHere[j] == LAST_MOVE) {
                    break;
                }
                allMoves[index++] = legalMovesFromHere[j++];
            }
        }
    }
    removeDuplicates(allMoves, index);
    free(speicher);
    return allMoves;
}

int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER) {
    MOVES allMoves = malloc(64 * sizeof(int));
    MOVES finalspeicher = getLegalMovesAllPositions(board, TARGET_PLAYER, allMoves);
    int total = 0;

    for (int i = 0; i < 64; i++) {
        if (finalspeicher[i] == LAST_MOVE) {
            return total;
        }
        total++;
    }
    printf("did not find a LAST_MOVE... are you sure you did not make a mistake\n");
    exit(1);
}

int copyBoardStruct(BOARD_STRUCT *destinationBoardStruct, BOARD_STRUCT *sourceBoardStruct, int n) {
    copyBoard(destinationBoardStruct->board, sourceBoardStruct->board, n);
    destinationBoardStruct->sideToMove = sourceBoardStruct->sideToMove;
    // todo , copy stack?
    return 0;
}

int copyBoard(BOARD destinationBoard, BOARD sourceBoard, int n) {
    for (int i = 0; i < n; i++) {
        destinationBoard[i] = sourceBoard[i];
    }
    return 0;
}

int areBoardStructsDifferent(BOARD_STRUCT *destinationBoardStruct, BOARD_STRUCT *sourceBoardStruct, int n) {
    if (!areBoardsDifferent(destinationBoardStruct->board, sourceBoardStruct->board, n)) {
        return destinationBoardStruct->sideToMove != sourceBoardStruct->sideToMove;
    }
    return 1; // they are different
}

int areBoardsDifferent(BOARD destinationBoard, BOARD sourceBoard, int n) {
    for (int i = 0; i < n; i++) {
        if (destinationBoard[i] != sourceBoard[i]) {
            return 1; // yes they are different
        }
    }
    return 0; // they are the same
}


BOARD makeMoveSide(BOARD_STRUCT *boardStruct, int legalPosition, SIDE_TO_MOVE targetPlayer) {
    switchPlayerStruct(boardStruct);
    return NULL;
}

BOARD makeMove(BOARD_STRUCT *boardStruct, int legalPosition) {
    return makeMoveSide(boardStruct, legalPosition, boardStruct->sideToMove);
}


int pushObject(BOARD_STRUCT *boardStruct, STACK_OBJECT stackObject) {
    boardStruct->stack[boardStruct->stackIndexObject++] = stackObject;
    return 0;
}

STACK_OBJECT popObject(BOARD_STRUCT *boardStruct) {
    return boardStruct->stack[--boardStruct->stackIndexObject];
}

int pushMove(BOARD_STRUCT *boardStruct, MOVE moveStackObject) {
    boardStruct->moveStack[boardStruct->stackIndexMove++] = moveStackObject;
    return 0;
}

STACK_OBJECT popMove(BOARD_STRUCT *boardStruct) {
    return boardStruct->moveStack[--boardStruct->stackIndexMove];
}

#define DIRECTION_SIZE 8
//static DIRECTION NORTH 0
//static DIRECTION NORTH_MASK 0xffULL
//static DIRECTION NORTH_WEST 1
//static DIRECTION NORTH_WEST_MASK 0xff00ULL
//static DIRECTION WEST 2
//static DIRECTION WEST_MASK 0xff0000ULL
//static DIRECTION SOUTH_WEST 3
//static DIRECTION SOUTH_WEST_MASK 0xff000000ULL
//static DIRECTION SOUTH 4
//static DIRECTION SOUTH_MASK 0xff00000000ULL
//static DIRECTION SOUTH_EAST 5
//static DIRECTION SOUTH_EAST_MASK 0xff0000000000ULL
//static DIRECTION EAST 6
//static DIRECTION EAST_MASK 0xff000000000000ULL
//static DIRECTION NORTH_EAST 7
//static DIRECTION NORTH_EAST_MASK 0xff00000000000000ULL

int getDirectionSize() {
    return DIRECTION_SIZE;
}


DIRECTION getNorth() {
    return 0;
}

DIRECTION getNorthWest() {
    return 1;
}

DIRECTION getWest() {
    return 2;
}

DIRECTION getSouthWest() {
    return 3;
}

DIRECTION getSouth() {
    return 4;
}

DIRECTION getSouthEast() {
    return 5;
}

DIRECTION getEast() {
    return 6;
}

DIRECTION getNorthEast() {
    return 7;
}


DIRECTION_MASK getNorthMask() {
    return 0xffULL;
}

DIRECTION_MASK getNorthWestMask() {
    return 0xff00ULL;
}

DIRECTION_MASK getWestMask() {
    return 0xff0000ULL;
}

DIRECTION_MASK getSouthWestMask() {
    return 0xff000000ULL;
}

DIRECTION_MASK getSouthMask() {
    return 0xff00000000ULL;
}

DIRECTION_MASK getSouthEastMask() {
    return 0xff0000000000ULL;
}

DIRECTION_MASK getEastMask() {
    return 0xff000000000000ULL;
}

DIRECTION_MASK getNorthEastMask() {
    return 0xff00000000000000ULL;
}

int addToStackObject(STACK_OBJECT *stackObject, DIRECTION direction, int numberOfKills) {
//    printf("      addToStackObject\n");
//    printf(" (direction* DIRECTION_SIZE): %d\n", ((direction * DIRECTION_SIZE)));
//    printf(" (shift: %ld\n", (((numberOfKills << (direction * DIRECTION_SIZE)))));

    STACK_OBJECT temp = (((unsigned long long int) numberOfKills)
            << (unsigned long long int) (direction * DIRECTION_SIZE));

//    printf(" (shift: %ld\n", temp);

    (*stackObject) |= temp; // todo , add AND  with mask ?

//    printf("      addToStackObject over\n");
    return 0;
}

int getNumberOfKillsFromDirection(STACK_OBJECT stackObject, DIRECTION direction, DIRECTION_MASK directionMask) {
//    printf("      getNumberOfKillsFromDirection\n");
//    printf(" SO: %d\n", (int) stackObject);
//    printf(" mask: %llu\n", directionMask);
//    printf(" mask& : %llu\n", (directionMask & stackObject));
//    printf(" direction * DIRECTION_SIZE: %d\n", (int) (direction * DIRECTION_SIZE));
//    printf(" answer : %llu\n", ((directionMask & stackObject) >> (direction * DIRECTION_SIZE)));

    return ((directionMask & stackObject) >> (direction * DIRECTION_SIZE));
}

int unmakeMove(BOARD_STRUCT *boardStruct) {
    // 0 means no kills in that dir
    // index should point to first free entry

    // todo consider allowing 4 bits maximum, might make more portable

    SIDE_TO_MOVE addToPlayer = boardStruct->sideToMove;

    BOARD board = boardStruct->board;

    STACK_OBJECT stackObject = popObject(boardStruct);
    MOVE stackMove = popMove(boardStruct);

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getNorth(), getNorthMask()); i++) {
        board[stackMove - 8 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getNorthWest(), getNorthWest()); i++) {
        board[stackMove - 9 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getWest(), getWestMask()); i++) {
        board[stackMove - 1 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getSouthWest(), getSouthWestMask()); i++) {
        board[stackMove + 7 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getSouth(), getSouthMask()); i++) {
        board[stackMove + 8 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getSouthEast(), getSouthEastMask()); i++) {
        board[stackMove + 9 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getEast(), getEastMask()); i++) {
        board[stackMove + 1 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getNorthEast(), getNorthEastMask()); i++) {
        board[stackMove - 7 * i] = addToPlayer;
    }

    // 64 bit
    /*
     00000000
     00000000
     00000000
     00000000
     00000000
     00000000
     00000000
     00000000
     */

    board[stackMove] = EMPTY;
    switchPlayerStruct(boardStruct);

    return 0;
}