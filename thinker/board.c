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
#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

#define LAST_MOVE (-1)

void resetBoardToStarter(BOARD board) {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
    board[27] = WHITE;
    board[28] = BLACK;
    board[35] = BLACK;
    board[36] = WHITE;
}

void resetBoardToZero(BOARD board) {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
}


void freeBoardStruct(BOARD_STRUCT* boardStruct){
//    free(boardStruct->stack->stackArray);
//    free(boardStruct->stack);
    free(boardStruct->board);
}


void initialiseBoardStructToStarter(BOARD_STRUCT* boardStruct){
    boardStruct->board = malloc(64 * sizeof(int));
    resetBoardToStarter(boardStruct->board);
    boardStruct->sideToMove = STARTING_PLAYER;
}

void initialiseBoardStructToZero(BOARD_STRUCT* boardStruct){
    boardStruct->board = malloc(64 * sizeof(int));
    resetBoardToZero(boardStruct->board);
    boardStruct->sideToMove = STARTING_PLAYER;
}

void printBoard(BOARD board) {
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");

    for (int i = 0; i < 8; i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < 8; j++) {
            int p = board[8 * i + j];
            if (p) {
                printf("%d ", p);
            } else {
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

    if (board[position] != MY_PLAYER) {
        printf("i don't have a player on this square\n");
        exit(1);
    }

//    printf("position is %d\n", position);

//    for-Schleifer um nach rechts zu prüfen
    for (int i = position + 1; i % 8 != 7; i++) {
        //TODO: nicht machen in Spalte 7
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position + 1] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move R:%d\n", speicher[index - 1]);
            break;
        }
    }

    // for-Schleifer um nach links zu prüfen
    for (int i = position - 1; i % 8 != 0; i--) {
        //TODO: nicht machen in Spalte 0
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position - 1] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move L:%d\n", speicher[index - 1]);
            break;
        }
    }

    // for-Schleifer um nach unten zu prüfen
    for (int i = position + 8; i < 64; i = i + 8) {
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position + 8] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move U:%d\n", speicher[index - 1]);
            break;
        }
    }

    // for-Schleifer um nach oben zu prüfen
    for (int i = position - 8; i > -1; i = i - 8) {
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position - 8] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move O:%d\n", speicher[index - 1]);
            break;
        }
    }


    // for-Schleifer um nach rechts oben zu prüfen
    for (int i = position - 7; i > -1 && i % 8 != 7; i = i - 7) {
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position - 7] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move RO:%d\n", speicher[index - 1]);
            break;
        }
    }

    // for-Schleifer um nach links oben zu prüfen
    for (int i = position - 9; i > -1 && i % 8 != 0; i = i - 9) {
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position - 9] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move OL:%d\n", speicher[index - 1]);
            break;
        }
    }

    // for-Schleifer um nach rechts unten zu prüfen
    for (int i = position + 9; i < 64 && i % 8 != 7; i = i + 9) {
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position + 9] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move UR:%d\n", speicher[index - 1]);
            break;
        }
    }
    // for-Schleifer um nach links unten zu prüfen
    for (int i = position + 7; i < 64 && i % 8 != 0; i = i + 7) {
        if (board[i] == TARGET_PLAYER) {
            continue;
        }
        if (board[i] == MY_PLAYER) {
            break;
        }
        if (board[i] == EMPTY && board[position + 7] == TARGET_PLAYER) {
            // legal move!!!
            speicher[index++] = i;
            printf("found move LU:%d\n", speicher[index - 1]);
            break;
        }
    }
    speicher[index] = LAST_MOVE;
    return speicher;
}

MOVES getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE TARGET_PLAYER) {
    MOVES allMoves= malloc(64 * sizeof(int)); // todo, clean up memory
    MOVES speicher= malloc(64 * sizeof(int));
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

    free(speicher);

    allMoves[index] = LAST_MOVE;
    return allMoves;
}


int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER) {
    MOVES legalMoves = getLegalMovesAllPositions(board, TARGET_PLAYER);
    int total = 0;

    for (int i = 0; i < 64; i++) {
        if (legalMoves[i] == LAST_MOVE) {
            return total;
        }
        total++;
    }
    printf("did not find a LAST_MOVE... are you sure you did not make a mistake\n");
    exit(1);
}

