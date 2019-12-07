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
struct Node {
    // add unique ID? (moves made)
    enum NodeType nodeType;
    int playoutCount;
    int ready;
    int movesReady;
    int winCount;
    Node *parentNode;
    Node **childrenNodes; // indexed by move index
    int numberOfChildren;
    int numberOfExpandedChildren;
};

void setupNode(Node *node) {

//    if (node->ready) {
//        return;
//    }
    node->nodeType = LEAF;
    node->winCount = 0;
    node->playoutCount = 0;
    node->numberOfChildren = 0;
    node->numberOfExpandedChildren = 0;
    node->ready = 1;
    node->movesReady = 0;
}

void freeNode(Node *node) {
    if (node->childrenNodes) {
        free(node->childrenNodes);
    }
    free(node);
}

void freeRootAndChildren(Node *root) {
    if (root->childrenNodes) {
        for (int i = 0; i < root->numberOfChildren; i++) {
            freeRootAndChildren(root->childrenNodes[i]);
        }
    }
    freeNode(root);
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
    printf("**parentNode: %p\n", node->parentNode);
    printf("**childNode : %p\n", node->childrenNodes);
    printf("** playouts : %d\n", node->playoutCount);
    printf("**   wins   : %d\n", node->winCount);
    printf("** numkids  : %d\n", node->numberOfChildren);
    printf("** numXkids : %d\n", node->numberOfExpandedChildren);
    printf("**movesReady: %d\n", node->movesReady);
    printf("**   ready  : %d\n", node->ready);
    printf("**\n");
}


void addTotalMoveInfo(Node *node, int totalMoves) {
    printf("     addTotalMoveInfo '%p', totalmoves: %d\n", node, totalMoves);
    // todo careful of endgame?
    // if there are no moves, there is still a pass move
    if (node->movesReady) {
        printf("%p is already ready\n", node);
        return;
    }
    if (!totalMoves) {
        totalMoves = 1;
    }
    node->numberOfChildren = totalMoves;
    node->childrenNodes = calloc(totalMoves, sizeof(Node));
    node->movesReady = 1;
    printf("addTotalMoveInfo over '%p'\n", node);
}

void addTotalMoveInfoAllocAllChildren(Node *node, int totalMoves) {
    printf("     addTotalMoveInfoAllocAllChildren '%p', totalmoves: %d\n", node, totalMoves);
    // todo careful of endgame?
    // if there are no moves, there is still a pass move
    if (node->movesReady) {
        printf("%p is already ready\n", node);
        return;
    }
    if (!totalMoves) {
        totalMoves = 1;
    }
    node->numberOfChildren = totalMoves;
    node->childrenNodes = calloc(totalMoves, sizeof(Node));

    for (int i = 0; i < totalMoves; i++) {
        node->childrenNodes[i] = calloc(1, sizeof(Node));
        printf(" callocing child %p, index %d\n", node->childrenNodes[i], i);
        setupNode(node->childrenNodes[i]);
    }

    node->movesReady = 1;
    printf("addTotalMoveInfoAllocAllChildren over '%p'\n", node);
}

void expandNode(Node *child, Node *parent, int moveIndex) {
    printf("expand node child: %p, parent: %p, moveIndex: %d\n", child, parent, moveIndex);
    setupNode(child);
    child->parentNode = parent;

    parent->nodeType = parent->nodeType == ROOT ? ROOT : BRANCH;
    parent->childrenNodes[moveIndex] = child;
    parent->numberOfExpandedChildren++;

    if (parent->numberOfExpandedChildren > parent->numberOfChildren) {
        printf("too many children, parent has %d expanded, but only %d children\n", parent->numberOfExpandedChildren,
               parent->numberOfChildren);
        printf("PARENT: %p\n", parent);
        printNode(parent);
//        printf("CHILD:\n");
//        printNode(child);
        exit(1);
    }
}

void printNodeBoardStruct(Node *node, BOARD_STRUCT *boardStruct) {
    printf("/////////////////////////////////\n");
    printf("NODE:\n");
    printNode(node);
    printf("BOARD:\n");
    printBoardSide(boardStruct);
    printf("////////////////////////////\n");
}

Node *selection(Node *node, BOARD_STRUCT *boardStruct) {
    printf("selection with %p\n", node);
    if (node->nodeType == ROOT && node->playoutCount == 0) {
        printf("selection: picking root %p\n", node);
        assert(node->ready);
        return node;
    }
    if (node->nodeType == ROOT) {
        assert(node->playoutCount > 0);
    }

    if (node->playoutCount == 0 || node->nodeType == LEAF) {
        return node;
    }

//    printNode(node);
    assert(node->playoutCount > 0);

    int r = 0;

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);
    if (totalMoves) {
        makeMove(boardStruct, moves[r]);
    } else {
        switchPlayerStruct(boardStruct);
    }

    printf("recursive selection with %p\n", node->childrenNodes[r]);
    free(moves);
    return selection(node->childrenNodes[r], boardStruct);
}


// todo return wld?
Node *expansion(Node *node, BOARD_STRUCT *boardStruct) {
    printf("expansion node %p\n", node);
    assert(node->ready);

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

    printf("expansion  add total %d\n", totalMoves);
//    addTotalMoveInfo(node, totalMoves);
    addTotalMoveInfoAllocAllChildren(node, totalMoves);
//    int r = rand() % node->numberOfChildren;
    int r = 0;

    makeMove(boardStruct, moves[r]);

    Node *child = node->childrenNodes[r];
    if (!child) {
        child = calloc(1, sizeof(Node));
        printf("calloc'd child %p\n", child);
    }

    expandNode(child, node, r);

    free(moves);
//    assert(child->nodeType != ROOT);
    return child;
}


int simulation(BOARD_STRUCT *boardStruct) {
    int passs = 0;
    for (int i = 0; i < 60; i++) {
        if (passs == 2) {
            break;
        }

        MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
        int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

        if (totalMoves) {
            passs = 0;
            makeMove(boardStruct, moves[0]);
        } else {
            passs++;
            switchPlayerStruct(boardStruct);
        }

        free(moves);
    }

    SIDE_TO_MOVE originalSideToMove = boardStruct->sideToMove;

    int w = getWinner(boardStruct);

    if (w == originalSideToMove) {
        return AIWIN;
    }

    if (w == getDraw()) {
        return AIDRAW;
    }

    return AILOSS;
}

int switchOutcome(int outcome) {
    return -outcome;
}

int backprop(Node *finalNode, int outcome) {
    Node *temp = finalNode;

    do {
        temp->playoutCount += 2;

        if (outcome == AIWIN) {
            temp->winCount += 2;
        } else if (outcome == AIDRAW) {
            temp->winCount++;
        }
        temp = temp->parentNode;
        outcome = switchOutcome(outcome);
    } while (temp);


    return 0;
}

void freeKids(Node *node) {
    for (int i = 0; i < node->numberOfChildren; i++) {
//        free(node->childrenNodes[i]);

        if (node->childrenNodes) {
            if (node->childrenNodes[i]) {
                freeKids(node->childrenNodes[i]);
//                if (node->childrenNodes[i]->childrenNodes) {
//                    if (node->childrenNodes[i]->childrenNodes[i]) {
//                        free(node->childrenNodes[i]->childrenNodes[i]);
//                    }
//                    free(node->childrenNodes[i]->childrenNodes);
//                }
//                free(node->childrenNodes[i]);
            }

        } else {
            free(node);
        }
    }

    free(node->childrenNodes); // careful?
    free(node);
}

// selection expansion simulation backprop
int getBestMove(BOARD_STRUCT *boardStruct, int moveTime) {
    srand(time(NULL)); // todo move out ?

//    BOARD_STRUCT *copy = malloc(sizeof(BOARD_STRUCT));

//    initialiseBoardStructToZero(copy);
//    copyBoardStruct(copy, boardStruct, getBoardSize());

    BOARD board = boardStruct->board;
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        free(moves);
        return getPassMove();
    }

    if (totalMoves == 1) {
        free(moves);
        return moves[0];
    }
    MOVE move = moves[0];

    Node *root = malloc(sizeof(Node)); // todo consider giving each node an id, made by the moves to get to it?
    setupNode(root);
    root->nodeType = ROOT;
    root->parentNode = NULL;

    free(moves);

    int magic = 0;
    while (magic < 50) {
        printf("/////////// magic: %d\n", magic);

        resetBoardToStarter(board);
        resetStackStuff(boardStruct);

        Node *toExpand = selection(root, boardStruct); // pick a node with no children

        printf("root: %p, toExpand %p\n", root, toExpand);
        if (root == toExpand) {
            printf("expanding root\n");
        }

        printf("trying expansion %p\n", toExpand);
        Node *expandedChild = expansion(toExpand, boardStruct); // reserve memory for children and pick one
        if (expandedChild == toExpand) {
            printf("expansion gave same node :(((\n");
        }
        printf("expansion done %p\n", expandedChild);


        printf("trying simulation\n");
        int outcome = simulation(boardStruct); // run a game, return result
        printf("simulation done %d\n", outcome);


        printf("trying backprop\n");
        backprop(expandedChild, outcome);
        printf("backprop done\n");

        magic++;
    }

    printNode(root);

    freeKids(root);

    return move;
}

