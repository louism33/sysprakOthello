#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "board.h"
#include <stdbool.h>

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
//            printf("found move R:%d\n", speicher[index - 1]);
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
//            printf("found move L:%d\n", speicher[index - 1]);
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
//            printf("found move U:%d\n", speicher[index - 1]);
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
//            printf("found move O:%d\n", speicher[index - 1]);
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
//            printf("found move RO:%d\n", speicher[index - 1]);
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
//            printf("found move OL:%d\n", speicher[index - 1]);
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
//            printf("found move UR:%d\n", speicher[index - 1]);
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
//            printf("found move LU:%d\n", speicher[index - 1]);
            break;
        }
    }
    speicher[index] = LAST_MOVE;
    return speicher;
}

MOVES getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE TARGET_PLAYER,MOVES allMoves) {
    //MOVES allMoves= malloc(64 * sizeof(int)); // todo, clean up memory
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
    MOVES allMoves= malloc(64 * sizeof(int));
    getLegalMovesAllPositions(board, TARGET_PLAYER, allMoves);
    int total = 0;

    for (int i = 0; i < 64; i++) {
        if (allMoves[i] == LAST_MOVE) {
            return total;
        }
        total++;
    }
    printf("did not find a LAST_MOVE... are you sure you did not make a mistake\n");
    exit(1);
}

int makeMove(BOARD board, int pos, SIDE_TO_MOVE TARGET_PLAYER) {
    SIDE_TO_MOVE ME = 3- TARGET_PLAYER;
    if(board[pos] != EMPTY) {
        return 1;
    }
    //Prüfung nach links
    if(pos%8 != 0 && pos%8 != 1)
    {
        if(board[pos-1] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 2; i<8; i++) {
                if(board[pos-i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos-i] == EMPTY) {
                    break;
                }

                if(board[pos-i] == ME) {
                    for(int j=1; j<i; j++) {
                        board[pos-i+j] = ME;
                    }

                }
            } 
        }
        
    }

    //Prüfung nach rechts
    if(pos%8 != 6 && pos%8 != 7)
    {
        if(board[pos+1] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 2; i<8; i++) {
                if(board[pos+i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos+i] == EMPTY) {
                    break;
                }

                if(board[pos+i] == ME) {
                    for(int j=1; j<i; j++) {
                        board[pos+i-j] = ME;
                    }

                }
            } 
        }
        
    }

    //Prüfung nach oben
    if(pos/8 != 0 && pos/8 != 1)
    {
        if(board[pos-8] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 16; i<57; i+=8) {
                if(board[pos-i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos-i] == EMPTY) {
                    break;
                }

                if(board[pos-i] == ME) {
                    for(int j=8; j<i; j+=8) {
                        board[pos-i+j] = ME;
                    }

                }
            } 
        }
        
    }

     //Prüfung nach unten
    if(pos/8 != 6 && pos/8 != 7)
    {
        if(board[pos+8] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 16; i<57; i+=8) {
                if(board[pos+i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos+i] == EMPTY) {
                    break;
                }

                if(board[pos+i] == ME) {
                    for(int j=8; j<i; j+=8) {
                        board[pos+i-j] = ME;
                    }

                }
            } 
        }
        
    }

    //Prüfung nach rechts oben
    if(pos/8 != 0 && pos/8 != 1 && pos%8 != 6 && pos%8 != 7)
    {
        if(board[pos-7] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 14; i<50; i+=7) {
                if(board[pos-i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos-i] == EMPTY) {
                    break;
                }

                if(board[pos-i] == ME) {
                    for(int j=7; j<i; j+=7) {
                        board[pos-i+j] = ME;
                    }

                }
            } 
        }
        
    }


    //Prüfung nach links oben
    if(pos/8 != 0 && pos/8 != 1 && pos%8 != 0 && pos%8 != 1)
    {
        if(board[pos-9] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 18; i<64; i+=9) {
                if(board[pos-i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos-i] == EMPTY) {
                    break;
                }

                if(board[pos-i] == ME) {
                    for(int j=9; j<i; j+=9) {
                        board[pos-i+j] = ME;
                    }

                }
            } 
        }
        
    }

    //Prüfung nach links unten
    if(pos/8 != 0 && pos/8 != 1 && pos%8 != 6 && pos%8 != 7)
    {
        if(board[pos+7] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 14; i<50; i+=7) {
                if(board[pos+i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos+i] == EMPTY) {
                    break;
                }

                if(board[pos+i] == ME) {
                    for(int j=7; j<i; j+=7) {
                        board[pos+i-j] = ME;
                    }

                }
            } 
        }
        
    }

    //Prüfung nach rechts unten
    if(pos/8 != 6 && pos/8 != 7 && pos%8 != 6 && pos%8 != 7)
    {
        if(board[pos+9] == TARGET_PLAYER) { //TODO am rand 
            for(int i = 18; i<64; i+=8) {
                if(board[pos+i] == TARGET_PLAYER) {
                    continue;
                }

                if(board[pos+i] == EMPTY) {
                    break;
                }

                if(board[pos+i] == ME) {
                    for(int j=9; j<i; j+=9) {
                        board[pos+i-j] = ME;
                    }

                }
            } 
        }
        
    }

    board[pos] = ME;

    return 0;
}

int testEasyLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;

   // printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRightBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = BLACK;
    board[36] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,18,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[27] = WHITE;
    boardTest[36] = WHITE;
    boardTest[18] = WHITE;

   // printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyLeftBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[35] = BLACK;
    board[42] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,28,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[28] = WHITE;
    boardTest[35] = WHITE;
    boardTest[42] = WHITE;

   // printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyTopLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = WHITE;
    board[36] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,45,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[27] = WHITE;
    boardTest[36] = WHITE;
    boardTest[45] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyTopRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[28] = WHITE;
    board[35] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //   printBoardLouisSide(board, player);
    printBoard(board);
    makeMove(board,42,targetPlayer);
    printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[28] = WHITE;
    boardTest[35] = WHITE;
    boardTest[42] = WHITE;

    printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = BLACK;
    board[19] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,17,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[17] = WHITE;
    boardTest[18] = WHITE;
    boardTest[19] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[29] = WHITE;
    board[37] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,45,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = BLACK;
    board[29] = WHITE;
    
    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,13,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[13] = WHITE;
    boardTest[21] = WHITE;
    boardTest[29] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRightLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[21] = BLACK;
    board[22] = WHITE;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;


    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRightLeftTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[21] = BLACK;
    board[22] = WHITE;
    board[12] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;
    boardTest[12] = BLACK;


    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy2Left() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[17] = WHITE;
    board[18] = BLACK;
    board[19] = BLACK;
    

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[17] = WHITE;
    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy2Right() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = BLACK;
    board[20] = BLACK;
    board[21] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,18,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[20] = BLACK;
    board[21] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,22,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy3Top() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = WHITE;
    board[29] = BLACK;
    board[37] = BLACK;
    board[45] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,53,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[21] = WHITE;
    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;
    boardTest[53] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[20] = BLACK;
    board[21] = BLACK;
    board[22] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,23,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;
    boardTest[23] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyMAX() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[32] = WHITE;
    board[33] = WHITE;
    board[34] = BLACK;
    board[35] = BLACK;
    board[36] = BLACK;
    board[37] = BLACK;
    board[38] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,39,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[32] = WHITE;
    boardTest[33] = WHITE;
    boardTest[34] = WHITE;
    boardTest[35] = WHITE;
    boardTest[36] = WHITE;
    boardTest[37] = WHITE;
    boardTest[38] = WHITE;
    boardTest[39] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyMAXTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[5] = WHITE;
    board[13] = WHITE;
    board[21] = BLACK;
    board[29] = BLACK;
    board[37] = BLACK;
    board[45] = BLACK;
    board[53] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,61,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[5] = WHITE;
    boardTest[13] = WHITE;
    boardTest[21] = WHITE;
    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;
    boardTest[53] = WHITE;
    boardTest[61] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}


int testEasyMAXRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[33] = BLACK;
    board[34] = BLACK;
    board[35] = BLACK;
    board[36] = BLACK;
    board[37] = BLACK;
    board[38] = BLACK;
    board[39] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,32,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[32] = WHITE;
    boardTest[33] = WHITE;
    boardTest[34] = WHITE;
    boardTest[35] = WHITE;
    boardTest[36] = WHITE;
    boardTest[37] = WHITE;
    boardTest[38] = WHITE;
    boardTest[39] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success

}

int testEasyMAXBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[13] = BLACK;
    board[21] = BLACK;
    board[29] = BLACK;
    board[37] = BLACK;
    board[45] = BLACK;
    board[53] = BLACK;
    board[61] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,5,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[13] = WHITE;
    boardTest[21] = WHITE;
    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;
    boardTest[53] = WHITE;
    boardTest[61] = WHITE;
    boardTest[5] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int crazyTest() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[12] = WHITE;
    board[20] = BLACK;
    board[36] = BLACK;
    board[27] = BLACK;
    board[21] = BLACK;
    board[14] = WHITE;
    board[29] = BLACK;
    board[26] = WHITE;
    board[44] = WHITE;
    board[30] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    printBoard(board);
    makeMove(board,28,targetPlayer);
    printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[12] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[14] = WHITE;
    boardTest[36] = WHITE;
    boardTest[27] = WHITE;
    boardTest[29] = WHITE;
    boardTest[26] = WHITE;
    boardTest[44] = WHITE;
    boardTest[30] = WHITE;
    boardTest[28] = WHITE;

    printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int main(){
    /*testEasyLeft();
    testEasy2Left();
    testEasy3();
    testEasy4();
    testEasyMAX();
    testEasyRight();
    testEasy2Right();
    testEasyMAXRight();
    testEasyRightLeft();
    testEasyTop();
    testEasy3Top();
    testEasyMAXTop();
    testEasyRightLeftTop();
    testEasyBottom();
    testEasyMAXBottom();*/
    crazyTest();
    testEasyTopRight();
    testEasyTopLeft();
    testEasyLeftBottom();
    testEasyRightBottom();

    
    return 0;
}


