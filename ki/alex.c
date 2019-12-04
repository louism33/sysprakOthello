//
// Created by louis on 11/25/19.
//

#include "alex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>


/*
 * Uses monte carlo tree search
 */




enum NodeType {
    ROOT = 0,
    BRANCH = 1,
    LEAF = 2,
};

typedef struct Node Node;
struct Node { // todo add name, add depth (for unmake)
    enum NodeType nodeType;
    int playoutCount;
    int winCount;
    Node *parentNode;
    Node **childrenNodes; // indexed by move index
    int numberOfChildren;
    int numberOfExpandedChildren;
};

void setupNode(Node *node) {
    node->nodeType = LEAF;
    node->winCount = 0;
    node->playoutCount = 0;
    node->numberOfChildren = 0; // careful
    node->numberOfExpandedChildren = 0;
//    node->childrenNodes = malloc(totalMoves * sizeof(Node));
}

void addTotalMoveInfo(Node *node, int totalMoves) {
    node->numberOfChildren = totalMoves;
    node->childrenNodes = malloc(totalMoves * sizeof(Node));
}

void expandNode(Node *child, Node *parent, int moveIndex) {
    child->nodeType = LEAF;
    child->playoutCount = 0;
    child->numberOfExpandedChildren = 0;
    child->numberOfChildren = 0;
    child->winCount = 0;
    child->parentNode = parent;

    parent->nodeType = parent->nodeType == ROOT ? ROOT : BRANCH;
    parent->childrenNodes[moveIndex] = child;
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
    printf("** numXkids: %d\n", node->numberOfExpandedChildren);
    printf("**\n");
}

struct Node *selection(Node *node, BOARD_STRUCT* boardStruct) {
    int r = rand() % node->numberOfChildren;
//    printf("rand kid: %d\n", r);

    Node *child = node->childrenNodes[r];

    child = malloc(sizeof(Node));

    setupNode((child));

//    printf("is kid null ?\n");
//    printf("is kid null %d ?\n", child->nodeType);

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE)); // todo, free
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

    makeMove(boardStruct, moves[r]);

    if (child->nodeType == LEAF) {
        return child;
    }


    return selection(child, boardStruct);

//    printNode(child);

//    return child;
}

struct Node *expansion(struct Node *node) {


}


struct Node *playout(struct Node *node) {
//    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);
//    isG
}

// selection expansion simulation backprop
int getBestMove(BOARD_STRUCT *boardStruct, int moveTime) {
    srand(time(NULL)); // todo move out ?

    BOARD board = boardStruct->board;
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        return getPassMove();
    }

    if (totalMoves == 1) {
        return moves[0];
    }

    Node *root = malloc(sizeof(Node)); // todo consider giving each node an id, made by the moves to get to it?

    setupNode(root);
    root->nodeType = ROOT;
//    root->numberOfChildren = totalMoves;
    addTotalMoveInfo(root, totalMoves);

    printNode(root);
    printBoardSide(boardStruct);


    Node *toExpand = selection(root, boardStruct);


    printf("//////////////////\n");
    printf("//////////////////\n");
    printf("//////////////////\n");

    printNode(toExpand);
    printBoardSide(boardStruct);

    MOVE move = moves[0];

    free(moves); // todo, recursive

    return move;
}

