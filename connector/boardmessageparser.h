//
// Created by louis on 11/20/19.
//

#ifndef SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
#define SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H

typedef struct moveTimeAndBoard
{
    int movetime;
    int *board;
} moveTimeAndBoard;

void parseBoardMessage(BOARD_STRUCT *board, moveTimeAndBoard *moveTimeAndBoard, char *message);

void exampleUseCaseOfMessageParsing();

void printBoardLouis(BOARD_STRUCT *board);

void printBoardLouisSide(BOARD_STRUCT *b, SIDE_TO_MOVE sideToMove);

#endif //SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
