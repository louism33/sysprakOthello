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

typedef struct Node Node; //consider giving moves
//todo consider ready flag
struct Node { // todo add name, add depth (for unmake)
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
//    node->childrenNodes = malloc(totalMoves * sizeof(Node));
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
    printf("** playouts: %d\n", node->playoutCount);
    printf("**   wins  : %d\n", node->winCount);
    printf("** numkids : %d\n", node->numberOfChildren);
    printf("** numXkids: %d\n", node->numberOfExpandedChildren);
    printf("**\n");
}


void addTotalMoveInfo(Node *node, int totalMoves) {
    printf("     addTotalMoveInfo '%p', totalmoves: %d\n", node, totalMoves);
    // todo careful of endgame?
    // if there are no moves, there is still a pass move
    if (node->movesReady) {
        return;
    }
    if (!totalMoves) {
        totalMoves = 1;
    }
    node->numberOfChildren = totalMoves;
    node->childrenNodes = calloc(totalMoves, sizeof(Node));
    Node *c = node->childrenNodes[0];
    node->movesReady = 1;
    printf("addTotalMoveInfo over '%p'\n", node);
}

void expandNode(Node *child, Node *parent, int moveIndex) {
    printf("expand node\n");
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

int xxx = 0;

Node *selection(Node *node, BOARD_STRUCT *boardStruct) {

    if (1) {
        return node;
    }

    if (node->nodeType == ROOT && node->playoutCount == 0) {
        printf("picking root\n");

        assert(node->ready);
        return node;
    }

    if (1) {

        printf("abc\n");

        Node *child = node->childrenNodes[0];
        printf("abcd\n");

        if (xxx == 0) {
            child = malloc(sizeof(Node));
            printf("abcde\n");

            expandNode(child, node, 0);
            printf("abcf\n");
        }
        xxx++;
        return child;
    }

    int passNode = 0;

    if (node->nodeType == LEAF && node->playoutCount == 0) {
        printf("   node->nodeType == LEAF && node->playoutCount == 0\n");
        return node;
    }

    if (!node->ready) {
//        printf(" node not ready\n");
        setupNode(node);
        MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
        int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);
        addTotalMoveInfo(node, totalMoves);
        passNode = !totalMoves;
        free(moves);
//        printf(" node not ready after\n");
        return node;
    }

    assert(node->ready);
    assert(node->numberOfChildren);

//    printf("  moveindex\n");
    int moveIndex = rand() % node->numberOfChildren;

    Node *child = node->childrenNodes[moveIndex];
//    printf("  a\n");
    int childUnready = 0;

    child = malloc(sizeof(Node));

    expandNode(child, node, moveIndex);
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE)); // todo, consider saving moves
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

    if (passNode) {
        passMove(boardStruct);
    } else {
        MOVE m = moves[moveIndex];
        makeMove(boardStruct, moves[moveIndex]);
    }
    if (child->nodeType == LEAF) {
        assert(child->numberOfChildren == 0);
        free(moves);
        return child;
    }

    free(moves);

    printf("    recursive %d\n", child->nodeType);
    return selection(child, boardStruct);
}

// todo return wld?
Node *expansion(Node *node, BOARD_STRUCT *boardStruct) { //todo, append all possible children?
//    assert(node->nodeType == LEAF || (node->nodeType == ROOT && node->playoutCount == 0));
    assert(node->ready);

    printf("expansion node %p\n", node);

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

//    printBoardSide(boardStruct);

    printf("expansion  add total %d\n", totalMoves);
    addTotalMoveInfo(node, totalMoves);
//    int r = rand() % node->numberOfChildren;
    int r = 0;
//    printf("rand kid: %d\n", r);

    makeMove(boardStruct, moves[r]);


    Node *child = node->childrenNodes[r];
    if (!child) {
        child = calloc(1, sizeof(Node));
    }
//    printf("x %p\n", child);


    expandNode(child, node, r);
    printf("xxs\n");

    free(moves);
//    assert(child->nodeType != ROOT);
    return child;
}


int simulation(BOARD_STRUCT *boardStruct) {
//    if (1) {
//        return AIDRAW;
//    }
    int passs = 0;
    for (int i = 0; i < 60; i++) {
        if (passs == 2) {
            break;
        }
//        printBoardSide(boardStruct);

        MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
        int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);
//        printf("move: %d\n", moves[0]);
//        printMoves(moves);

        if (totalMoves) {
            passs = 0;
            makeMove(boardStruct, moves[0]);
        } else {
            passs++;
            switchPlayerStruct(boardStruct);
        }

        free(moves);

    }

    if (1)
        return AIDRAW;

    SIDE_TO_MOVE originalSideToMove = boardStruct->sideToMove;

//    printf("          ->>>>><<original side to move is %d\n", originalSideToMove);

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

//    printBoardSide(boardStruct);
    int w = getWinner(boardStruct);
//    printf("   WINNER IS %d\n", w);
//    printBoardSide(boardStruct);
//    printf("   WINNER IS %d\n", w);

    if (w == originalSideToMove) {
//        printf("   I win!!!\n");
        return AIWIN;
    }

    if (w == getDraw()) {
//        printf("   it was a draw!\n");
        return AIDRAW;
    }

//    printf("   it was a loss!\n");
    return AILOSS;
//    return getWinner(boardStruct);
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

void freeKids(Node* node){

    free(node->childrenNodes[0]->childrenNodes);
    for (int i = 0; i < node->numberOfChildren; i++) {
        free(node->childrenNodes[i]);
    }
    free(node->childrenNodes);

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

//    addTotalMoveInfo(root, totalMoves);
    free(moves);

    int magic = 0;
    while (magic < 2) {
        printf("/// magic: %d\n", magic);

        resetBoardToStarter(board);
        resetStackStuff(boardStruct);

        Node *toExpand = selection(root, boardStruct); // pick a node with no children      ROOT

        printf("root: %p, toExpand %p\n", root, toExpand);
        if (root == toExpand) {
            printf("expanding root\n");
        }

        printf("trying expansion %p\n", toExpand);
        Node *expandedChild = expansion(toExpand, boardStruct);
        // reserve memory for children and pick one     ROOT->child[0]
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

//    free(expandedChild->childrenNodes);

    freeKids(root);


    return move;

}

