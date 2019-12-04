//
// Created by louis on 11/25/19.
//

#ifndef SYSPRAKOTHELLO_ALEX_H
#define SYSPRAKOTHELLO_ALEX_H

#include "../thinker/board.h"

enum NodeType {
    ROOT = 0,
    LEAF = 0
};

typedef struct Node {
    enum NodeType nodeType;
    int playoutCount;
    int winCount;
    struct Node* parentNode;
    struct Node* childrenNodes; // indexed by move index
} Node;


int getBestMove(BOARD_STRUCT *boardStruct, int moveTime);

#endif //SYSPRAKOTHELLO_ALEX_H
