//
// Created by louis on 11/25/19.
//

#include "alex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
/*
 * Uses monte carlo tree search
 */

#define AIWIN (1)
#define AIDRAW (0)
#define AILOSS (-1)


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

void printNodeBoardStruct(Node *node, BOARD_STRUCT *boardStruct) {
    printf("/////////////////////////////////\n");
    printf("NODE:\n");
    printNode(node);
    printf("BOARD:\n");
    printBoardSide(boardStruct);
    printf("////////////////////////////\n");
}


struct Node *selection(Node *node, BOARD_STRUCT *boardStruct) {

    if (node->nodeType == ROOT && node->playoutCount == 0) {
        return node;
    }

    int r = rand() % node->numberOfChildren;

    Node *child = node->childrenNodes[r];

    child = malloc(sizeof(Node));

    setupNode((child));

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE)); // todo, free
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

    makeMove(boardStruct, moves[r]);

    if (child->nodeType == LEAF) {
        assert(child->numberOfChildren == 0);
        return child;
    }

    free(moves);

    return selection(child, boardStruct);
}

// todo return wld?
Node *expansion(Node *node, BOARD_STRUCT *boardStruct) {
    assert(node->nodeType == LEAF || (node->nodeType == ROOT && node->playoutCount == 0));
    if (isGameOver(boardStruct)) {
        // todo, return win loss draw
    }

    // todo only continue if actually has children

    setupNode(node);

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

    addTotalMoveInfo(node, totalMoves);

    // todo, expand all kids if highscore?
    int r = rand() % node->numberOfChildren;
    printf("rand kid: %d\n", r);

    makeMove(boardStruct, moves[r]);
    Node *child = node->childrenNodes[r];

    child = malloc(sizeof(Node));

    free(moves);

    return child;

}


int simulation(Node *node, BOARD_STRUCT *boardStruct) {

    SIDE_TO_MOVE originalSideToMove = boardStruct->sideToMove;
    int pass = 0;
//    while (!isGameOver(boardStruct)) {
    while (pass != 2) {

//        printBoardSide(boardStruct);
//        usleep(500000);

        MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
        int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

        if (!totalMoves) {
            pass++;
            passMove(boardStruct);
        } else {
            pass = 0;
            int r = rand() % totalMoves;
//            printf("++ rand: %d, rand move: %d\n", r, moves[r]);

            makeMove(boardStruct, moves[r]);
            free(moves);
        }
    }

    printBoardSide(boardStruct);
    int w = getWinner(boardStruct);
    printf("   WINNER IS %d\n", w);
//    printBoardSide(boardStruct);
//    printf("   WINNER IS %d\n", w);

    if (w == originalSideToMove) {
        printf("   I win!!!\n");
        return AIWIN;
    }

    if (w == getDraw()) {
        printf("   it was a draw!\n");
        return AIDRAW;
    }

    printf("   it was a loss!\n");
    return AILOSS;
//    return getWinner(boardStruct);

}

// todo instead of unmake consider cloning, 60 unmakes vs arraycopy??
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

//    printNode(root);
//    printBoardSide(boardStruct);


    Node *toExpand = selection(root, boardStruct);


    printf("//////////////////\n");
    printf("//////////////////\n");
    printf("////////////////// to expand\n");


    printNode(toExpand);
    printBoardSide(boardStruct);

    printf("//////////////////\n");
    printf("//////////////////\n");
    printf("//////////////////\n");


    Node *expandedChild = expansion(toExpand, boardStruct);

    printf("  --->>>> RUNNING SIMULATION FOR\n");
    printNodeBoardStruct(expandedChild, boardStruct);

    simulation(expandedChild, boardStruct);


    MOVE move = moves[0];

    free(moves); // todo, recursive

    return move;
}

