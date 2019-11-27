//
// Created by louis on 11/20/19.
//

#ifndef SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
#define SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0



// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)




typedef struct moveTimeAndBoard {
    int movetime;
    int *board;
} moveTimeAndBoard;

void parseBoardMessage(BOARD_STRUCT* board, moveTimeAndBoard *moveTimeAndBoard, char *message);

void exampleUseCaseOfMessageParsing();

void printBoardLouis(BOARD_STRUCT* board);

void printBoardLouisSide(BOARD_STRUCT* b, SIDE_TO_MOVE sideToMove);

#endif //SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
