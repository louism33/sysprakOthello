//
// Created by louis on 11/20/19.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "boardmessageparser.h"


#define MOVE int
#define SIDE_TO_MOVE int
#define BOARD int*
#define MOVES int*

#define BLACK 2
#define WHITE 1

#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

#define STARTING_PLAYER BLACK
#define SWITCH_PLAYER_CONSTANT 3

/*
+ TOTAL 2
+ 0 IAMLOUIS 0
+ ENDPLAYERS
+ MOVE 3000
+ FIELD 8,8
+ 8 * * * * * * * *
+ 7 * * * * * B B B
+ 6 * * * * * W * *
+ 5 * * W W W B * *
+ 4 * B B B B * * *
+ 3 * * W * * * * *
+ 2 * * * * * * * *
+ 1 * * * * * * * *
+ ENDFIELD
 */

// todo this class is bad at memory

int messageParserReady = 0;
int couldNotParseRegex = 1;

char sourceCopy[64]; // larger than needed
char *regexString = "\\+ MOVE ([0-9]+)";
size_t maxGroups = 2;
regex_t regexCompiled;

void setupMessageParser() { // we do this to avoid wasting memory and compute on regex patterns
    if (messageParserReady) {
        printf("message parser already set up\n");
        return;
    }

    printf("Setting up message parser for first time\n");

    couldNotParseRegex = regcomp(&regexCompiled, regexString, REG_EXTENDED);

    messageParserReady = 1;
}

void tearDownMessageParser() {
    regfree(&regexCompiled);
}


void printBoardLouis(BOARD board) {
    printBoardLouisSide(board, 0);
}

void printBoardLouisSide(BOARD board, SIDE_TO_MOVE sideToMove) {

    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            printf("\n");
        }
//        printf("%d ", board[i]);
        if (board[i] == WHITE) {
            printf("W ");
        } else if (board[i] == BLACK) {
            printf("B ");
        } else {
            printf(". ");
        }
    }
    printf("\n");
    if (sideToMove) {
        printf("%d to move\n", sideToMove);
        if (sideToMove == BLACK) {
            printf("Black to move\n");
        } else {
            printf("White to move\n");
        }
    } else {
        printf("I don't know whose turn it is\n");
    }
    printf("-----------\n");
}

void exampleUseCaseOfMessageParsing() {
//    setupMessageParser();

    char *exampleBoardMessage = "+ TOTAL 2\n"
                                "+ 0 IAMLOUIS 0\n"
                                "+ ENDPLAYERS\n"
                                "+ MOVE 3000\n"
                                "+ FIELD 8,8\n"
                                "+ 8 * * * * * * * *\n"
                                "+ 7 * * * * * B B B\n"
                                "+ 6 * * * * * W * *\n"
                                "+ 5 * * W W W B * *\n"
                                "+ 4 * B B B B * * *\n"
                                "+ 3 * * W * * * * *\n"
                                "+ 2 * * * * * * * *\n"
                                "+ 1 * * * * * * * *\n"
                                "+ ENDFIELD";


    BOARD board = malloc(64 * sizeof(int)); // blank board

    printBoardLouis(board);

    moveTimeAndBoard *moveTimeAndBoard = malloc(sizeof(moveTimeAndBoard));

    parseBoardMessage(board, moveTimeAndBoard, exampleBoardMessage);

    printBoardLouis(board);

//    tearDownMessageParser();
}


void parseBoardMessage(BOARD board, moveTimeAndBoard *moveTimeAndBoard, char *message) {
    setupMessageParser(); // we do this to avoid wasting memory and compute on regex patterns
    regmatch_t groupArray[maxGroups];

    if (couldNotParseRegex) {
        printf("Could not compile regular expression.\n");
        moveTimeAndBoard->movetime = 3000; //hack just in case we cannot parse something, we at least use some kind of value for movetime
    } else if (regexec(&regexCompiled, message, maxGroups, groupArray, 0) == 0ul) {
        strcpy(sourceCopy, message);
        sourceCopy[groupArray[1].rm_eo] = 0;
        char *found = sourceCopy + groupArray[1].rm_so;
        moveTimeAndBoard->movetime = atoi(found);
    }

    char c;
    int boardIndex = 0;
    for (int i = (int) strlen(message) - 170; i < (int) strlen(message); i++) {
        c = message[i];
        switch (c) {
            case 'B':
                board[boardIndex] = 2;
                boardIndex++;
                continue;
            case 'W':
                board[boardIndex] = 1;
                boardIndex++;
                continue;
            case '*':
                board[boardIndex] = 0;
                boardIndex++;
                continue;
            case 'E': // + ENDFIELD is the end of the message
                break;
        }

    }

    moveTimeAndBoard->board = board; // todo, decide if board should be from argument or from here
}
