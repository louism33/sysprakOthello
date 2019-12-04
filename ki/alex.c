//
// Created by louis on 11/25/19.
//

#include "alex.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

/*
 * Uses monte carlo tree search
 */


enum NodeType {
    ROOT = 0,
    BRANCH = 1,
    LEAF = 2,
};

typedef struct Node Node;
struct Node {
    enum NodeType nodeType;
    int playoutCount;
    int winCount;
    Node *parentNode;
    Node *childrenNodes; // indexed by move index
    int numberOfChildren;
    int numberOfExpandedChildren;
};

void expandNode(Node *child, Node *parent, int moveIndex) {
    child->nodeType = LEAF;
    child->playoutCount = 0;
    child->numberOfExpandedChildren = 0;
    child->numberOfChildren = 0;
    child->winCount = 0;
    child->parentNode = parent;

    parent->nodeType = parent->nodeType == ROOT ? ROOT : BRANCH;
    parent->childrenNodes[moveIndex] = *child;
    parent->numberOfExpandedChildren++;

    if (parent->numberOfExpandedChildren > parent->numberOfChildren) {
        printf("too many children\n");
        exit(1);
    }
}

void printNode(Node *node) {
    printf("*****\n");
    if (node->nodeType == ROOT) {
        printf("-> type ROOT\n");
    } else if (node->nodeType == BRANCH) {
        printf("-> type BRANCH\n");
    } else {
        printf("-> type LEAF\n");
    }
    printf("** playouts: %d\n", node->playoutCount);
    printf("**   wins  : %d\n", node->winCount);
    printf("** numkids : %d\n", node->numberOfChildren);
}

struct Node *selection(struct Node *node) {

}

// selection expansion simulation backprop
int getBestMove(BOARD_STRUCT *boardStruct, int moveTime) {
    BOARD board = boardStruct->board;
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        return getPassMove();
    }

    if (totalMoves == 1) {
        return moves[0];
    }

    Node *root = malloc(sizeof(Node));

    root->nodeType = ROOT;
    root->winCount = 0;
    root->playoutCount = 0;
    root->numberOfChildren = totalMoves;
    root->numberOfExpandedChildren = 0;



    MOVE move = moves[0];

    free(moves);

    return move;
}

