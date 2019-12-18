//
// Created by louis on 11/20/19.
//
#include "../thinker/board.h"
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
// todo remove this stupid regex crap
void setupMessageParser()
{ // we do this to avoid wasting memory and compute on regex patterns
    if (messageParserReady)
    {
        printf("message parser already set up\n");
        return;
    }

    printf("Setting up message parser for first time\n");

    couldNotParseRegex = regcomp(&regexCompiled, regexString, REG_EXTENDED);

    messageParserReady = 1;
}

void tearDownMessageParser()
{
    regfree(&regexCompiled);
}

void printBoardLouis(BOARD_STRUCT *board)
{
    printBoardLouisSide(board, 0);
}

void printBoardLouisSide(BOARD_STRUCT *b, SIDE_TO_MOVE sideToMove)
{
    int *board = b->board;

    for (int i = 0; i < getBoardSize(); i++)
    {
        if (i % getColumnSize() == 0)
        {
            printf("\n");
        }
        if (board[i] == getWhite())
        {
            printf("W ");
        }
        else if (board[i] == getBlack())
        {
            printf("B ");
        }
        else
        {
            printf(". ");
            //            printf("%d ", board[i]);
        }
    }
    printf("\n");
    if (sideToMove)
    {
        printf("%d to move\n", sideToMove);
        if (sideToMove == getBlack())
        {
            printf("Black to move\n");
        }
        else
        {
            printf("White to move\n");
        }
    }
    else
    {
        printf("I don't know whose turn it is\n");
    }
    printf("-----------\n");
}

void parseBoardMessage(BOARD_STRUCT *board, moveTimeAndBoard *moveTimeAndBoard, char *message)
{
    int *boardBoard = board->board;
    char *moveTime = malloc(4 * sizeof(char));
    char *fieldSize = malloc(3 * sizeof(char));
    int moveTimeNummer = getMovetimeandFieldsize(message, moveTime, fieldSize);
    printf("xxxxxxxxxxxxxxxbbbbbb %d\n", moveTimeNummer);

    char c;
    int boardIndex = 0;
    for (int i = (int)strlen(message) - 170; i < (int)strlen(message); i++)
    {
        c = message[i];
        switch (c)
        {
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
}
