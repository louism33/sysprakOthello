//
// Created by louis on 11/20/19.
//
#include "../thinker/board.h"

#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "boardmessageparser.h"

int messageParserReady = 0;
int couldNotParseRegex = 1;

void printBoardLouis(BOARD_STRUCT  *board) {
    printBoardLouisSide(board, board->sideToMove);
}

void printBoardLouisSide(BOARD_STRUCT*  b, SIDE_TO_MOVE sideToMove) {
    int *board = b->board;

    for (int i = 0; i < getBoardSize(); i++) {
        if (i % getColumnSize() == 0) {
            printf("\n");
        }
        if (board[i] == getWhite()) {
            printf("W ");
        } else if (board[i] == getBlack()) {
            printf("B ");
        } else {
            printf(". ");
        }
    }
    printf("\n");
    if (sideToMove) {
        printf("### %d ist next to move\n", sideToMove);
        if (sideToMove == getBlack()) {
            printf("### Black to move\n");
        } else {
            printf("### White to move\n");
        }
    } else {
        printf("I don't know whose turn it is\n");
    }
    printf("-----------\n");
}

int parseBoardMessage(BOARD_STRUCT*  board, moveTimeAndBoard *moveTimeAndBoard, char *message) {
    int *boardBoard = board->board;

    char c;
    int boardIndex = 0;
    for (int i = (int) strlen(message) - 170; i < (int) strlen(message); i++) {
        c = message[i];
        switch (c) {
            case 'B':
                boardBoard[boardIndex] = 2;
                boardIndex++;
                continue;
            case 'W':
                boardBoard[boardIndex] = 1;
                boardIndex++;
                continue;
            case '*':
                boardBoard[boardIndex] = 0;
                boardIndex++;
                continue;
            case 'E': // + ENDFIELD is the end of the message
                break;
        }
    }

    moveTimeAndBoard->board = boardBoard; // todo, decide if board should be from argument or from here
    return 0;
}
