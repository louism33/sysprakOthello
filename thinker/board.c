#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "board.h"
#include <stdbool.h>
#include <assert.h>

#define DIRECTION_SIZE 8
#define ZEILE 8

#define SPALTE 8
// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define GAMEOVER 1
#define GAMENOTOVER 0

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
#define PASS_MOVE (-42)
#define DRAW (0)

#define STANDARD_COLUMN_NUMBER (8)
#define STANDARD_ROW_NUMBER (8)

static int boardSize = 0;
static int columnSize = 0;
static int rowSize = 0;

MOVE getPassMove() {
    return PASS_MOVE;
}

int getDraw() {
    return DRAW;
}

inline int getBoardSize() {
    return boardSize;
}


inline int getRowSize() {
    return rowSize;
}

inline int getColumnSize() {
    return columnSize;
}

void setRowSize(int rows) {
    rowSize = rows;
}

MOVE getGameOver() {
    return GAMEOVER;
}

MOVE getGameNotOver() {
    return GAMENOTOVER;
}

void setColumnSize(int columns) {
    columnSize = columns;
}

int getStandardBoardSize() {
    return STANDARD_COLUMN_NUMBER * STANDARD_ROW_NUMBER;
}

static int *columnOfPos;
static int *rowOfPos;
static int columnArrayReady = 0;
static int rowArrayReady = 0;

static int setupColumnArray(int boardSize) {
    if (!columnArrayReady) {
        columnArrayReady = 1;
    } else {
        free(columnOfPos);
    }
    columnOfPos = malloc(boardSize * sizeof(int));
    assert(boardSize > 0);
    for (int i = 0; i < boardSize; i++) {
        int col = i % getColumnSize();
        columnOfPos[i] = col < 0 ? col + getColumnSize() : col;
    }
    return 0;
}

static int setupRowArray(int boardSize) {
    assert(boardSize > 0);
    if (!rowArrayReady) {
        rowArrayReady = 1;
    } else {
        free(rowOfPos);
    }
    rowOfPos = malloc(boardSize * sizeof(int));
    for (int i = 0; i < boardSize; i++) {
        rowOfPos[i] = i / getColumnSize();
    }
    return 0;
}

void setBoardSize(int rows, int columns) {
    int oldBoardSize = getBoardSize();
    boardSize = rows * columns;
    if (boardSize != oldBoardSize) {
//        printf("SETTING UP ARRAYS\n");
        setupColumnArray(boardSize);
        setupRowArray(boardSize);
    }
}

int setBoardToStandardSize() {
    setRowSize(STANDARD_ROW_NUMBER);
    setColumnSize(STANDARD_COLUMN_NUMBER);
    setBoardSize(rowSize, columnSize);
    return boardSize;
}

int setBoardToCustomSize(int rows, int columns) {
    setRowSize(rows);
    setColumnSize(columns);
    setBoardSize(rowSize, columnSize);
    return boardSize;
}


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
    for (int i = 0; i < getStandardBoardSize(); i++) {
        board[i] = 0;
    }
    board[STARTING_WHITE_POSITION_1] = WHITE;
    board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = BLACK;
    board[STARTING_BLACK_POSITION_2] = BLACK;
}

void resetStackStuff(BOARD_STRUCT *boardStruct) {
    for (int i = 0; i < getStandardBoardSize(); i++) {
        boardStruct->moveStack[i] = 0;
    }
    boardStruct->stackIndexMove = 0;
    boardStruct->stackIndexObject = 0;
}

void resetBoardToZero(BOARD board) {
    for (int i = 0; i < getStandardBoardSize(); i++) {
        board[i] = 0;
    }
}

void resetBoardToZeroCustom(BOARD board, int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        board[i] = 0;
    }
}

void freeBoardStruct(BOARD_STRUCT *boardStruct) {
    free(boardStruct->moveStack);
    free(boardStruct->stack);
    free(boardStruct->board);
    free(boardStruct);
}

void freeStatics() {
    free(columnOfPos);
    free(rowOfPos);
}

void initialiseBoardStructMemory(BOARD_STRUCT *boardStruct, int boardSize) {
    boardStruct->board = malloc(boardSize * sizeof(int));
    boardStruct->stack = malloc(boardSize * sizeof(STACK_OBJECT));
    boardStruct->moveStack = malloc(boardSize * sizeof(MOVE));
    boardStruct->sideToMove = STARTING_PLAYER;
    boardStruct->stackIndexMove = 0;
    boardStruct->stackIndexObject = 0;
}

void initialiseBoardStructToStarter(BOARD_STRUCT *boardStruct) {
    initialiseBoardStructMemory(boardStruct, getStandardBoardSize());
    setBoardToStandardSize();
    resetBoardToStarter(boardStruct->board);
}

void initialiseBoardStructToZero(BOARD_STRUCT *boardStruct) {
    setBoardToStandardSize();
    initialiseBoardStructMemory(boardStruct, boardSize);
    resetBoardToZero(boardStruct->board);
}

void initialiseBoardStructToZeroCustom(BOARD_STRUCT *boardStruct, int rows, int columns) {
    setBoardToCustomSize(rows, columns);
    initialiseBoardStructMemory(boardStruct, boardSize);
    resetBoardToZeroCustom(boardStruct->board, boardSize);
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

    for (int i = 0; i < getColumnSize(); i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < getRowSize(); j++) {
            int p = board[getRowSize() * i + j];
            if (p == BLACK) {
                printf("B ");
            } else if (p == WHITE) {
                printf("W ");
            } else {
                printf("  ");
            }
        }
        printf("| %d", i + 1);
        printf("\n");
    }

    printf("  +-----------------+ \n");
    printf("    A B C D E F G H \n");

    // too print pretty moves as too?
}

char *getPrettyMove(int move, char *antwort) {
    antwort[0] = 'A' + (move % getColumnSize());     //spalte
    antwort[1] = '0' + (getRowSize() - move / getRowSize()); //zeile
    antwort[2] = '\0';
    return antwort;
}

void printMoves(MOVES moves) {
    char *moveMem = malloc(3 * sizeof(char));
    int index = 0;
    while (1) {
        MOVE move = moves[index++];
        if (move == LAST_MOVE) {
            break;
        }
        getPrettyMove(move, moveMem);
//        printf("%s\n", moveMem);
        printf("%d: %s\n", move, moveMem);
    }
    free(moveMem);
}

void addColourToSquare(BOARD board, SIDE_TO_MOVE sideToMove, MOVE move) {
    if (move < 0 || move > getBoardSize()) {
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


static inline int getColumn(int i) {
    assert(i >= 0);
    assert(i < getBoardSize());
    return columnOfPos[i];
}

static inline int getRow(int i) {
    assert(i >= 0);
    assert(i < getBoardSize());
    return rowOfPos[i];
}


#define MOVE_FOUND (-13)

int getLegalMovesOnePositionFriend(BOARD board, MOVES allMoves, int totalMovesIndex, int position,
                                   SIDE_TO_MOVE TARGET_PLAYER) {
    int index = totalMovesIndex;
    int MY_PLAYER = switchPlayer(TARGET_PLAYER);

    int row = getRow(position);
    int col = getColumn(position);

    if (board[position] != MY_PLAYER) {
        printf("i don't have a player on this square\n");
        exit(1);
    }

    int firstRow = 0;
    int secondRow = 1;
    int preFinalRow = getRowSize() - 2;
    int finalRow = getRowSize() - 1;

    int firstCol = 0;
    int secondCol = 1;
    int preFinalCol = getColumnSize() - 2;
    int finalCol = getColumnSize() - 1;

    int smallDiagonal = getColumnSize() - 1;
    int bigDiagonal = getColumnSize() + 1;

    //for-Schleifer um nach rechts zu prüfen
    if (col != preFinalCol && col != finalCol) {
        if (board[position + 1] == TARGET_PLAYER) {
            int i = position + 2;
            int coltemp = col + 2;//getColumn(i);

//            printf("aaa col %d, %d \n", col, coltemp);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == getColumnSize()) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i++;
                    coltemp++;
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach links zu prüfen
    if (col != firstCol && col != secondCol) {
        if (board[position - 1] == TARGET_PLAYER) {
            int i = position - 2;
            int coltemp = col - 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == -1) {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i--;
                    coltemp--;
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach unten zu prüfen
    if (row != preFinalRow && row != finalRow) {
        if (board[position + getRowSize()] == TARGET_PLAYER) {
            int i = position + 2 * getRowSize();
            while (i >= 0 && i < getBoardSize()) {
                if (i >= getBoardSize()) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += getRowSize();
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach oben zu prüfen
    if (row != firstRow && row != secondRow) {
        if (board[position - getColumnSize()] == TARGET_PLAYER) {
            int i = position - 2 * getColumnSize();
            while (i >= 0 && i < getBoardSize()) {
                if (board[i] == TARGET_PLAYER) {
                    i -= getColumnSize();
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach rechts oben zu prüfen
    if (col != preFinalCol && col != finalCol && row != firstRow && row != secondRow) {
        if (board[position - smallDiagonal] == TARGET_PLAYER) {
            int i = position - 2 * smallDiagonal;
            int coltemp = col + 2; //getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == getColumnSize()) //col
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i -= smallDiagonal;
                    coltemp++;
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }


    // for-Schleifer um nach links oben zu prüfen
    if (col != firstCol && col != secondCol && row != firstRow && row != secondRow) {
        if (board[position - bigDiagonal] == TARGET_PLAYER) {
            int i = position - 2 * bigDiagonal;
            int coltemp = col - 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == -1) //row
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i -= bigDiagonal;
                    coltemp--;
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach rechts unten zu prüfen
    if (col != preFinalCol && col != finalCol && row != finalRow && row != preFinalRow) {
        if (board[position + bigDiagonal] == TARGET_PLAYER) {
            int i = position + 2 * bigDiagonal;
            int coltemp = col + 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == getColumnSize()) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += bigDiagonal;
                    coltemp++;
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    //  for-Schleifer um nach links unten zu prüfen
    if (col != firstCol && col != secondCol && row != finalRow && row != preFinalRow) {
        if (board[position + smallDiagonal] == TARGET_PLAYER) {
            int i = position + 2 * smallDiagonal;
            int coltemp = col - 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == -1) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += smallDiagonal;
                    coltemp--;
                    continue;
                }
                if (board[i] == EMPTY) {
                    allMoves[i] = MOVE_FOUND;
                    break;
                }
                if (board[i] == MY_PLAYER) {
                    break;
                }
            }
        }
    }

    return index;
}

int removeDuplicates(MOVES speicher) {
    int index = 0;
    for (int i = 0; i < getBoardSize(); i++) {
        if (speicher[i] == MOVE_FOUND) {
            speicher[index++] = i;
        }
    }
    speicher[index] = LAST_MOVE;
    return index;
}

int getLegalMovesAllPositionsFriend(BOARD board, SIDE_TO_MOVE targetPlayer, MOVES allMoves) {
    memset(allMoves, 0, getBoardSize() * sizeof(MOVE));
    SIDE_TO_MOVE me = switchPlayer(targetPlayer);
    int index = 0;
    for (int pos = 0; pos < getBoardSize(); pos++) {
        if (board[pos] == me) {
            index = getLegalMovesOnePositionFriend(board, allMoves, index, pos, targetPlayer);
        }
    }
    return removeDuplicates(allMoves);
}


int getLegalMovesOnePositionEmpty(BOARD board, MOVES allMoves, int index, int position,
                                  SIDE_TO_MOVE TARGET_PLAYER) {
    int MY_PLAYER = switchPlayer(TARGET_PLAYER);

    int row = getRow(position);
    int col = getColumn(position);

    if (board[position] != EMPTY) {
        printf("i don't have a empty on this square\n");
        exit(1);
    }

    int firstRow = 0;
    int secondRow = 1;
    int preFinalRow = getRowSize() - 2;
    int finalRow = getRowSize() - 1;

    int firstCol = 0;
    int secondCol = 1;
    int preFinalCol = getColumnSize() - 2;
    int finalCol = getColumnSize() - 1;

    int smallDiagonal = getColumnSize() - 1;
    int bigDiagonal = getColumnSize() + 1;

    //for-Schleifer um nach rechts zu prüfen
    if (col != preFinalCol && col != finalCol) {
        if (board[position + 1] == TARGET_PLAYER) {
            int i = position + 2;
            int coltemp = col + 2;

            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == getColumnSize()) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i++;
                    coltemp++;
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach links zu prüfen
    if (col != firstCol && col != secondCol) {
        if (board[position - 1] == TARGET_PLAYER) {
            int i = position - 2;
            int coltemp = col - 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == -1) {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i--;
                    coltemp--;
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach unten zu prüfen
    if (row != preFinalRow && row != finalRow) {
        if (board[position + getRowSize()] == TARGET_PLAYER) {
            int i = position + 2 * getRowSize();
            while (i >= 0 && i < getBoardSize()) {
                if (i >= getBoardSize()) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += getRowSize();
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach oben zu prüfen
    if (row != firstRow && row != secondRow) {
        if (board[position - getColumnSize()] == TARGET_PLAYER) {
            int i = position - 2 * getColumnSize();
            while (i >= 0 && i < getBoardSize()) {
                if (board[i] == TARGET_PLAYER) {
                    i -= getColumnSize();
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach rechts oben zu prüfen
    if (col != preFinalCol && col != finalCol && row != firstRow && row != secondRow) {
        if (board[position - smallDiagonal] == TARGET_PLAYER) {
            int i = position - 2 * smallDiagonal;
            int coltemp = col + 2; //getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == getColumnSize()) //col
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i -= smallDiagonal;
                    coltemp++;
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }


    // for-Schleifer um nach links oben zu prüfen
    if (col != firstCol && col != secondCol && row != firstRow && row != secondRow) {
        if (board[position - bigDiagonal] == TARGET_PLAYER) {
            int i = position - 2 * bigDiagonal;
            int coltemp = col - 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == -1) //row
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER) {
                    i -= bigDiagonal;
                    coltemp--;
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach rechts unten zu prüfen
    if (col != preFinalCol && col != finalCol && row != finalRow && row != preFinalRow) {
        if (board[position + bigDiagonal] == TARGET_PLAYER) {
            int i = position + 2 * bigDiagonal;
            int coltemp = col + 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == getColumnSize()) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += bigDiagonal;
                    coltemp++;
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    //  for-Schleifer um nach links unten zu prüfen
    if (col != firstCol && col != secondCol && row != finalRow && row != preFinalRow) {
        if (board[position + smallDiagonal] == TARGET_PLAYER) {
            int i = position + 2 * smallDiagonal;
            int coltemp = col - 2;//getColumn(i);
            while (i >= 0 && i < getBoardSize()) {
                if (coltemp == -1) {
                    break;
                }
                if (board[i] == TARGET_PLAYER) {
                    i += smallDiagonal;
                    coltemp--;
                    continue;
                }
                if (board[i] == MY_PLAYER) {
                    allMoves[index] = position;
                    return 1;
                }
                if (board[i] == EMPTY) {
                    break;
                }
            }
        }
    }

    return 0;
}


int getLegalMovesAllPositionsEmpty(BOARD board, SIDE_TO_MOVE targetPlayer, MOVES allMoves) {
    SIDE_TO_MOVE me = switchPlayer(targetPlayer);
    int index = 0;
    for (int pos = 0; pos < getBoardSize(); pos++) {
        if (board[pos] == EMPTY) {
            index += getLegalMovesOnePositionEmpty(board, allMoves, index, pos, targetPlayer);
        }
    }
    allMoves[index] = LAST_MOVE;
    return index;
}

int getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE targetPlayer, MOVES allMoves) {
    // this was an attempt to optimise both ways of searching
//    int ret = 0;
//    if (getBoardSize() == 64 && board[18] != 0 && board[45] != 0) {
//        ret = getLegalMovesAllPositionsFriend(board, targetPlayer, allMoves);
//    } else {
//        ret = getLegalMovesAllPositionsEmpty(board, targetPlayer, allMoves); // this one is much faster
//    }
//    return ret;

//        return getLegalMovesAllPositionsFriend(board, targetPlayer, allMoves);
    return getLegalMovesAllPositionsEmpty(board, targetPlayer, allMoves); // this one is much faster
}


// please don't call this if performance matters
int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER) {
    MOVES allMoves = malloc(getBoardSize() * sizeof(int));
    int total = getLegalMovesAllPositions(board, TARGET_PLAYER, allMoves);
    free(allMoves);
    return total;
}

int countMoves(MOVES allMoves) {
    int total = 0;

    for (int i = 0; i < getBoardSize(); i++) {
        if (allMoves[i] == LAST_MOVE) {
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
    return 0;
}

int copyBoard(BOARD destinationBoard, BOARD sourceBoard, int n) { //todo optimise
    for (int i = 0; i < n; i++) {
        destinationBoard[i] = sourceBoard[i];
    }
//    memcpy(destinationBoard, sourceBoard, n * sizeof(int));
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

int pushObject(BOARD_STRUCT *boardStruct, STACK_OBJECT stackObject) {
    boardStruct->stack[boardStruct->stackIndexObject++] = stackObject;
    boardStruct->stack[boardStruct->stackIndexObject] = 0;
    return 0;
}

STACK_OBJECT popObject(BOARD_STRUCT *boardStruct) {
    STACK_OBJECT ret = boardStruct->stack[--boardStruct->stackIndexObject];
    boardStruct->stack[boardStruct->stackIndexObject] = 0;
    return ret;
}

int pushMove(BOARD_STRUCT *boardStruct, MOVE moveStackObject) {
    boardStruct->moveStack[boardStruct->stackIndexMove++] = moveStackObject;
    boardStruct->moveStack[boardStruct->stackIndexMove] = 0; // overwrite anything that might be hanging around from elsewhere
    return 0;
}

STACK_OBJECT popMove(BOARD_STRUCT *boardStruct) {
    MOVE ret = boardStruct->moveStack[--boardStruct->stackIndexMove];
    boardStruct->moveStack[boardStruct->stackIndexMove] = 0; // overwrite
    return ret;
}

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
    STACK_OBJECT temp = (((unsigned long long int) numberOfKills)
            << (unsigned long long int) (direction * DIRECTION_SIZE));

    (*stackObject) |= temp;

    return 0;
}

int getNumberOfKillsFromDirection(STACK_OBJECT stackObject, DIRECTION direction, DIRECTION_MASK directionMask) {
    return ((directionMask & stackObject) >> (direction * DIRECTION_SIZE));
}

int unmakeMove(BOARD_STRUCT *boardStruct) {
    // 0 means no kills in that dir
    // index should point to first free entry

    SIDE_TO_MOVE addToPlayer = boardStruct->sideToMove;

    BOARD board = boardStruct->board;

    STACK_OBJECT stackObject = popObject(boardStruct);
    MOVE stackMove = popMove(boardStruct);

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getNorth(), getNorthMask()); i++) {
        board[stackMove - 8 * i] = addToPlayer;
    }

    for (int i = 1; i <= getNumberOfKillsFromDirection(stackObject, getNorthWest(), getNorthWestMask()); i++) {
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

    board[stackMove] = EMPTY;
    switchPlayerStruct(boardStruct);

    return 0;
}

void passMove(BOARD_STRUCT *boardStruct) {
    switchPlayerStruct(boardStruct);
}

int makeMoveSide(BOARD_STRUCT *boardStruct, int pos, SIDE_TO_MOVE TARGET_PLAYER) {
    BOARD board = boardStruct->board;

    if (pos == LAST_MOVE) {
        printf("  ERROR last move  ------------> POS %d\n", pos);
        exit(1);
    }

    if (board[pos] != EMPTY) {
        printf(" ERROR   ------------> POS %d, is not empty board[pos] %d\n", pos, board[pos]);
        printBoardSide(boardStruct);
        exit(1);
    }
    pushMove(boardStruct, pos);

    SIDE_TO_MOVE ME = switchPlayer(TARGET_PLAYER);

    STACK_OBJECT stackObject = 0;
    int numberOfKills = 0;
    int column = getColumn(pos);
    int row = getRow(pos);

    int firstRow = 0;
    int secondRow = 1;
    int preFinalRow = getRowSize() - 2;
    int finalRow = getRowSize() - 1;

    int firstCol = 0;
    int secondCol = 1;
    int preFinalCol = getColumnSize() - 2;
    int finalCol = getColumnSize() - 1;

    int smallDiagonal = getRowSize() - 1;
    int bigDiagonal = getRowSize() + 1;

    //Prüfung nach links
    if (column != firstCol && column != secondCol) {
        if (board[pos - 1] == TARGET_PLAYER) {
            for (int i = 2; i < getColumnSize() && pos - i >= 0; i++) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    numberOfKills = 0;

                    for (int j = 1; j < i; j++) {
                        numberOfKills++;
                        board[pos - i + j] = ME;
                    }
                    addToStackObject(&stackObject, getWest(), numberOfKills);
                    break;
                }
            }
        }

    }

    //Prüfung nach rechts
    if (column != preFinalCol && column != finalCol) {
        if (board[pos + 1] == TARGET_PLAYER) {
            for (int i = 2; i < getColumnSize() && pos + i < getBoardSize(); i++) {
                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    numberOfKills = 0;
                    for (int j = 1; j < i; j++) {
                        numberOfKills++;
                        board[pos + i - j] = ME;
                    }
                    addToStackObject(&stackObject, getEast(), numberOfKills);
                    break;
                }
            }
        }

    }

    //Prüfung nach oben
    if (row != firstRow && row != secondRow) {
        if (board[pos - getColumnSize()] == TARGET_PLAYER) {
            for (int i = 2 * getColumnSize(); pos - i >= 0; i += getColumnSize()) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    numberOfKills = 0;
                    for (int j = getColumnSize(); j < i; j += getColumnSize()) {
                        numberOfKills++;
                        board[pos - i + j] = ME;
                    }
                    addToStackObject(&stackObject, getNorth(), numberOfKills);
                    break;
                }
            }
        }
    }

    //Prüfung nach unten
    if (row != preFinalRow && row != finalRow) {
        if (board[pos + getColumnSize()] == TARGET_PLAYER) {
            for (int i = 2 * getColumnSize(); pos + i < getBoardSize(); i += getColumnSize()) {
                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    numberOfKills = 0;
                    for (int j = getColumnSize(); j < i; j += getColumnSize()) {
                        numberOfKills++;
                        board[pos + i - j] = ME;
                    }

                    addToStackObject(&stackObject, getSouth(), numberOfKills);
                    break;
                }
            }
        }

    }

    //Prüfung nach rechts oben
    if (row != firstRow && row != secondRow && column != preFinalCol && column != finalCol) {
        if (board[pos - smallDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * smallDiagonal; i < boardSize - 2 * smallDiagonal && pos - i >= 0; i += smallDiagonal) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    numberOfKills = 0;
                    for (int j = smallDiagonal; j < i; j += smallDiagonal) {
                        numberOfKills++;
                        board[pos - i + j] = ME;
                    }
                    addToStackObject(&stackObject, getNorthEast(), numberOfKills);
                    break;
                }
            }
        }

    }


    //Prüfung nach links oben
    if (row != firstRow && row != secondRow && column != firstCol && column != secondCol) {
        if (board[pos - bigDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * bigDiagonal;
                 i < getBoardSize() &&
                 pos - i >= 0; i += bigDiagonal) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    numberOfKills = 0;
                    for (int j = bigDiagonal; j < i; j += bigDiagonal) {
                        numberOfKills++;
                        board[pos - i + j] = ME;
                    }
                    addToStackObject(&stackObject, getNorthWest(), numberOfKills);
                    break;
                }
            }
        }

    }

    //Prüfung nach links unten
    if (row != preFinalRow && row != finalRow && column != firstCol && column != secondCol) {
        if (board[pos + smallDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * smallDiagonal;
                 i < getBoardSize() - 2 * smallDiagonal && pos + i < getBoardSize(); i += smallDiagonal) {

                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    numberOfKills = 0;
                    for (int j = smallDiagonal; j < i; j += smallDiagonal) {
                        numberOfKills++;
                        board[pos + i - j] = ME;
                    }
                    addToStackObject(&stackObject, getSouthWest(), numberOfKills);
                    break;
                }
            }
        }

    }

    //Prüfung nach rechts unten
    if (row != preFinalRow && row != finalRow && column != preFinalCol && column != finalCol) {
        if (board[pos + bigDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * bigDiagonal; i < getBoardSize() && pos + i <
                                                                getBoardSize(); i += bigDiagonal) {
                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    numberOfKills = 0;
                    for (int j = bigDiagonal; j < i; j += bigDiagonal) {
                        numberOfKills++;
                        board[pos + i - j] = ME;
                    }

                    addToStackObject(&stackObject, getSouthEast(), numberOfKills);
                    break;
                }
            }
        }
    }

    pushObject(boardStruct, stackObject);

    board[pos] = ME;
    switchPlayerStruct(boardStruct);
    return 0;
}


int makeMove(BOARD_STRUCT *boardStruct, int legalPosition) {
    if (legalPosition == getPassMove()) {
        switchPlayerStruct(boardStruct);
        return 0;
    }
    return makeMoveSide(boardStruct, legalPosition, switchPlayer(boardStruct->sideToMove));
}

// this method is the same as regular, but does not store information on the stack, because we do not need to unmake
int makeMoveSideAI(BOARD_STRUCT *boardStruct, int pos, SIDE_TO_MOVE TARGET_PLAYER) {
    BOARD board = boardStruct->board;

    assert(pos != LAST_MOVE);
    assert(board[pos] == EMPTY);

    SIDE_TO_MOVE ME = switchPlayer(TARGET_PLAYER);

    int column = getColumn(pos);
    int row = getRow(pos);

    int firstRow = 0;
    int secondRow = 1;
    int preFinalRow = getRowSize() - 2;
    int finalRow = getRowSize() - 1;

    int firstCol = 0;
    int secondCol = 1;
    int preFinalCol = getColumnSize() - 2;
    int finalCol = getColumnSize() - 1;

    int smallDiagonal = getRowSize() - 1;
    int bigDiagonal = getRowSize() + 1;

    //Prüfung nach links
    if (column != firstCol && column != secondCol) {
        if (board[pos - 1] == TARGET_PLAYER) {
            for (int i = 2; i < getColumnSize() && pos - i >= 0; i++) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    for (int j = 1; j < i; j++) {
                        board[pos - i + j] = ME;
                    }
                    break;
                }
            }
        }
    }

    //Prüfung nach rechts
    if (column != preFinalCol && column != finalCol) {
        if (board[pos + 1] == TARGET_PLAYER) {
            for (int i = 2; i < getColumnSize() && pos + i < getBoardSize(); i++) {
                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    for (int j = 1; j < i; j++) {
                        board[pos + i - j] = ME;
                    }
                    break;
                }
            }
        }
    }

    //Prüfung nach oben
    if (row != firstRow && row != secondRow) {
        if (board[pos - getColumnSize()] == TARGET_PLAYER) {
            for (int i = 2 * getColumnSize(); pos - i >= 0; i += getColumnSize()) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    for (int j = getColumnSize(); j < i; j += getColumnSize()) {
                        board[pos - i + j] = ME;
                    }
                    break;
                }
            }
        }
    }

    //Prüfung nach unten
    if (row != preFinalRow && row != finalRow) {
        if (board[pos + getColumnSize()] == TARGET_PLAYER) {
            for (int i = 2 * getColumnSize(); pos + i < getBoardSize(); i += getColumnSize()) {
                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    for (int j = getColumnSize(); j < i; j += getColumnSize()) {
                        board[pos + i - j] = ME;
                    }

                    break;
                }
            }
        }
    }

    //Prüfung nach rechts oben
    if (row != firstRow && row != secondRow && column != preFinalCol && column != finalCol) {
        if (board[pos - smallDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * smallDiagonal; i < boardSize - 2 * smallDiagonal && pos - i >= 0; i += smallDiagonal) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    for (int j = smallDiagonal; j < i; j += smallDiagonal) {
                        board[pos - i + j] = ME;
                    }
                    break;
                }
            }
        }
    }


    //Prüfung nach links oben
    if (row != firstRow && row != secondRow && column != firstCol && column != secondCol) {
        if (board[pos - bigDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * bigDiagonal;
                 i < getBoardSize() &&
                 pos - i >= 0; i += bigDiagonal) {
                if (board[pos - i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos - i] == EMPTY) {
                    break;
                }

                if (board[pos - i] == ME) {
                    for (int j = bigDiagonal; j < i; j += bigDiagonal) {
                        board[pos - i + j] = ME;
                    }
                    break;
                }
            }
        }
    }

    //Prüfung nach links unten
    if (row != preFinalRow && row != finalRow && column != firstCol && column != secondCol) {
        if (board[pos + smallDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * smallDiagonal;
                 i < getBoardSize() - 2 * smallDiagonal && pos + i < getBoardSize(); i += smallDiagonal) {

                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    for (int j = smallDiagonal; j < i; j += smallDiagonal) {
                        board[pos + i - j] = ME;
                    }
                    break;
                }
            }
        }
    }

    //Prüfung nach rechts unten
    if (row != preFinalRow && row != finalRow && column != preFinalCol && column != finalCol) {
        if (board[pos + bigDiagonal] == TARGET_PLAYER) {
            for (int i = 2 * bigDiagonal; i < getBoardSize() && pos + i <
                                                                getBoardSize(); i += bigDiagonal) {
                if (board[pos + i] == TARGET_PLAYER) {
                    continue;
                }

                if (board[pos + i] == EMPTY) {
                    break;
                }

                if (board[pos + i] == ME) {
                    for (int j = bigDiagonal; j < i; j += bigDiagonal) {
                        board[pos + i - j] = ME;
                    }

                    break;
                }
            }
        }
    }

    board[pos] = ME;
    switchPlayerStruct(boardStruct);
    return 0;
}


int makeMoveAI(BOARD_STRUCT *boardStruct, int legalPosition) {
    if (legalPosition == getPassMove()) {
        switchPlayerStruct(boardStruct);
        return 0;
    }
    return makeMoveSideAI(boardStruct, legalPosition, switchPlayer(boardStruct->sideToMove));
}


int getWinner(BOARD_STRUCT *boardStruct) { // todo, new method combining getWinner and isGameOver
    BOARD board = boardStruct->board;
    int anzahlBlack = 0;
    int anzahlWhite = 0;
    for (int i = 0; i < getBoardSize(); i++) {
        if (board[i] == getBlack())
            anzahlBlack++;
        else if (board[i] == getWhite()) {
            anzahlWhite++;
        }
    }

    if (anzahlBlack > anzahlWhite) {
        return getBlack();
    } else if (anzahlBlack < anzahlWhite++) {
        return getWhite();
    } else {
        return DRAW;
    }
}

int isGameOver(BOARD_STRUCT *boardStruct) {
    int anzahlBlack = 0;
    int anzahlWhite = 0;
    BOARD board = boardStruct->board;

    for (int i = 0; i < getBoardSize(); i++) {
        if (board[i] == getBlack()) {
            anzahlBlack++;
        } else if (board[i] == getWhite()) {
            anzahlWhite++;
        }
    }
    if (anzahlBlack == 0 || anzahlWhite == 0) {
        return GAMEOVER;
    }

    if (anzahlBlack + anzahlWhite == getBoardSize()) {
        return GAMEOVER;
    }

    if (getTotalNumberOfLegalMoves(board, BLACK) == 0 && getTotalNumberOfLegalMoves(board, WHITE) == 0) {
        return GAMEOVER; //true
    }
    return GAMENOTOVER;
}



