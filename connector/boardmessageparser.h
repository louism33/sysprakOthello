//
// Created by louis on 11/20/19.
//

#ifndef SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
#define SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H

typedef struct moveTimeAndBoard {
    int movetime;
    int *board;
} moveTimeAndBoard;

moveTimeAndBoard *parseBoardMessage(int* board, char *message);


#endif //SYSPRAKOTHELLO_BOARDMESSAGEPARSER_H
