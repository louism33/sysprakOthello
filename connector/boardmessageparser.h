//
// Created by louis on 11/20/19.
//

#ifndef SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
#define SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H

#define MOVE int
#define BOARD int*


// todo, add a global moveTimeAndBoard here?

typedef struct moveTimeAndBoard {
    int movetime;
    int *board;
} moveTimeAndBoard;

void parseBoardMessage(int* board, moveTimeAndBoard *moveTimeAndBoard, char *message);

void exampleUseCaseOfMessageParsing();

void printBoardLouis(BOARD board);

#endif //SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
