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
    MOVE moveFromParent;
    int passNode;
    int gameOver;
    SIDE_TO_MOVE sideToMove;
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
    node->passNode = 0;
    node->gameOver = 0;
    node->moveFromParent = getLastMove();
    node->childrenNodes = NULL;
    node->sideToMove = getEmpty();
}


void setupNodeParent(Node *node, Node *parent) {

//    if (node->ready) {
//        return;
//    }
    node->parentNode = parent;
    node->nodeType = LEAF;
    node->winCount = 0;
    node->playoutCount = 0;
    node->numberOfChildren = 0;
    node->numberOfExpandedChildren = 0;
    node->ready = 1;
    node->movesReady = 0;
    node->childrenNodes = NULL;
    node->sideToMove = switchPlayer(parent->sideToMove);
}


void setupNodeParentMove(Node *node, Node *parent, MOVE move) {

//    if (node->ready) {
//        return;
//    }
    node->parentNode = parent;
    node->nodeType = LEAF;
    node->winCount = 0;
    node->playoutCount = 0;
    node->numberOfChildren = 0;
    node->numberOfExpandedChildren = 0;
    node->ready = 1;
    node->movesReady = 0;
    node->childrenNodes = NULL;
    node->moveFromParent = move;
    node->sideToMove = switchPlayer(parent->sideToMove);
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
    printf("**     my&   : %p\n", node);
    printf("** parentNode: %p\n", node->parentNode);
    printf("** childNode : %p\n", node->childrenNodes);
    if (node->childrenNodes) {
        printf("** firstChild: %p\n", node->childrenNodes[0]);
    }
    printf("**  passNode : %d\n", node->passNode);
    printf("** parentMove: %d\n", node->moveFromParent);
    printf("**  playouts : %d\n", node->playoutCount);
    printf("**    wins   : %d\n", node->winCount);
    printf("**  numkids  : %d\n", node->numberOfChildren);
    printf("**  numXkids : %d\n", node->numberOfExpandedChildren);
    printf("** movesReady: %d\n", node->movesReady);
    printf("**    ready  : %d\n", node->ready);
    printf("**\n");
}


void addTotalMoveInfo(Node *node, int totalMoves) {
//    printf("     addTotalMoveInfo '%p', totalmoves: %d\n", node, totalMoves);
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
//    printf("addTotalMoveInfo over '%p'\n", node);
}

void addTotalMoveInfoAllocAllChildren(Node *node, int totalMoves, MOVES moves) { // todo careful of passes
//    printf("     addTotalMoveInfoAllocAllChildren '%p', totalmoves: %d\n", node, totalMoves);
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
//        printf(" callocing child %p, index %d\n", node->childrenNodes[i], i);
        setupNodeParentMove(node->childrenNodes[i], node, moves[i]);
    }

    node->movesReady = 1;
//    printf("addTotalMoveInfoAllocAllChildren over '%p'\n", node);
}

void expandNodeMove(Node *child, Node *parent, int moveIndex, MOVE move) {
//    printf("expand node child: %p, parent: %p, moveIndex: %d\n", child, parent, moveIndex);
    setupNodeParentMove(child, parent, move);
    child->parentNode = parent;
    child->moveFromParent = move;

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
//    printf("selection with %p\n", node);
    if (node->nodeType == ROOT && node->playoutCount == 0) {
//        printf("selection: picking root %p\n", node);
        assert(node->ready);
        return node;
    }
    if (node->nodeType == ROOT) {
        assert(node->playoutCount > 0);
    }

    if (node->playoutCount == 0 || node->nodeType == LEAF) {
        return node;
    }

    assert(node->playoutCount > 0);

    int r = node->passNode ? 0 : rand() % node->numberOfChildren;

//    printf("selection: r is %d\n", r);

    if (node->childrenNodes[r]->moveFromParent != getPassMove()) {
//        printf("yy\n");
        assert(node->childrenNodes[r]->moveFromParent != getPassMove());
        assert(node->childrenNodes[r]->moveFromParent >= 0);
        assert(node->childrenNodes[r]->moveFromParent < getBoardSize());
        assert(!node->childrenNodes[r]->parentNode->passNode);

        makeMove(boardStruct, node->childrenNodes[r]->moveFromParent);
    } else {
//        printf("XX\n");
        assert(node->childrenNodes[r]->parentNode->passNode);

        switchPlayerStruct(boardStruct);
    }


//    printf("recursive selection with %p\n", node->childrenNodes[r]);
    return selection(node->childrenNodes[r], boardStruct);
}


// todo return wld?
Node *expansion(Node *node, BOARD_STRUCT *boardStruct) {
//    printf("expansion node %p\n", node);
    assert(node->ready);

    if (node->gameOver) {
        printf("game already over at this node %p\n", node);

        assert(isGameOver(boardStruct));
        return node;
    }

    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        node->passNode = 1;

        switchPlayerStruct(boardStruct);
        int totalMovesFlip = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove),
                                                       moves);
        switchPlayerStruct(boardStruct);
        if (totalMovesFlip == 0) { // gameover
            node->gameOver = 1;
            assert(isGameOver(boardStruct));
            free(moves);
            return node;
        }
    }

//    printf("expansion  add total %d\n", totalMoves);
//    addTotalMoveInfo(node, totalMoves);
    addTotalMoveInfoAllocAllChildren(node, totalMoves, moves);
    int r = rand() % node->numberOfChildren;
    MOVE move = totalMoves == 0 ? getPassMove() : moves[r];
    if (totalMoves) {
        assert(moves[r] != getLastMove());
        assert(moves[r] != getPassMove());
        makeMove(boardStruct, move);
    } else {
        switchPlayerStruct(boardStruct);
    }

    Node *child = node->childrenNodes[r];

    if (!child) {
        child = calloc(1, sizeof(Node));
        printf("calloc'd child %p\n", child);
        exit(1); // should never happen, replace with assert
    }

    expandNodeMove(child, node, r, move);

    free(moves);
//    assert(child->nodeType != ROOT);
    return child;
}


int simulation(BOARD_STRUCT *boardStruct) {
    SIDE_TO_MOVE originalSideToMove = boardStruct->sideToMove;
    printf("original board to simulation \n");
    printBoardSide(boardStruct);

    int passs = 0;
    for (int i = 0; i < 100; i++) {
        if (passs == 2) {
//            printf("Double pass, game over\n");
//            printBoardSide(boardStruct);
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

    int w = getWinner(boardStruct);

    printf("Winner is: %d, same as original(%d)? %d\n", w, originalSideToMove, (w == originalSideToMove));
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
//    printf("final node: %p\n", finalNode);
//    printNode(finalNode);
//    printf("final node\n\n\n\n");

    Node *temp = finalNode;
    if (!temp->parentNode) {
        assert(temp->nodeType == ROOT);
    }

    do {
        if (!temp->parentNode) {
            assert(temp->nodeType == ROOT);
        }
        temp->playoutCount += 2;

        if (outcome == AIWIN) {
            temp->winCount += 2;
        } else if (outcome == AIDRAW) {
            temp->winCount++;
        }
        temp = temp->parentNode;

        if (!temp) {
//            printf(" outcome at root is: %d\n", outcome);
//            printNode(temp);
//            printf(" outcome at root is: %d\n\n\n\n", outcome);
        }
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

//    printBoardSide(boardStruct);

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

    BOARD_STRUCT *copy = malloc(sizeof(BOARD_STRUCT));

    initialiseBoardStructToZero(copy);
    copyBoardStruct(copy, boardStruct, getBoardSize());


    MOVE move = moves[0];

    Node *root = malloc(sizeof(Node)); // todo consider giving each node an id, made by the moves to get to it?
    setupNode(root);
    root->nodeType = ROOT;
    root->parentNode = NULL;
    root->sideToMove = boardStruct->sideToMove;

    free(moves);

    printNode(root);
    printf("\n\n\n");

//    printBoardSide(boardStruct);

    int magic = 0;
    while (magic < 10) {
//        printf("/////////// magic: %d\n", magic);

        copyBoardStruct(boardStruct, copy, getBoardSize());
        resetStackStuff(boardStruct);

        Node *fromSelection = selection(root, boardStruct); // pick a node with no children

//        printf("*************************** from selection board:\n");
//        printf("*************************** from selection node:\n");
//        printBoardSide(boardStruct);
//        printNode(fromSelection);
//        printf("*************************** from\n");
//        printf("root: %p, fromSelection %p\n", root, fromSelection);
//        if (root == fromSelection) {
//            printf("expanding root\n");
//        }

//        printf("trying expansion %p\n", fromSelection);
        Node *expandedChild = expansion(fromSelection, boardStruct); // reserve memory for children and pick one

        if (expandedChild == fromSelection) {
//            printf("            expansion gave same node GAMEOVER NODE\n");
//            printBoardSide(boardStruct);
        }
        printf("expansion done %p\n", expandedChild);


//        printf("trying simulation\n");
        int outcome;
        if (expandedChild == fromSelection) {
            assert(isGameOver(boardStruct));
//            printf("winner is %d\n", getWinner(boardStruct));
            outcome = (getWinner(boardStruct));
            printf("game over node, winner is: %d, move from parent %d\n", outcome, expandedChild->moveFromParent);
//            printf("outcome is %d\n", outcome);
        } else {
            outcome = simulation(boardStruct); // run a game, return result
        }

//        outcome = simulation(boardStruct); // run a game, return result

//        printf("simulation done %d\n", outcome);


//        printf("trying backprop %p\n", expandedChild);
//        if (expandedChild == fromSelection) {
//            backprop(fromSelection, outcome);
//        } else {
//            backprop(expandedChild, outcome);
//        }

        backprop(expandedChild, outcome);

//        printf("backprop done\n");

        magic++;
    }

    printNode(root);

    int totalPlayoutsFromRoot = root->playoutCount;
    int totalPlayoutsFromChildren = 0;
    int mostPlayoutsFromChild = 0;
    double weakestChildScore = 100;
    MOVE weakestChild = 0;
    MOVE weakestChildMove = getLastMove();

    for (int i = 0; i < root->numberOfChildren; i++) {
        if (root->childrenNodes[i]) {
            totalPlayoutsFromChildren += root->childrenNodes[i]->playoutCount;
            mostPlayoutsFromChild =
                    root->childrenNodes[i]->playoutCount > mostPlayoutsFromChild ? root->childrenNodes[i]->playoutCount
                                                                                 : mostPlayoutsFromChild;
            printNode(root->childrenNodes[i]);

            if (root->childrenNodes[i]->playoutCount) {
                double ratio = (double) root->childrenNodes[i]->winCount / root->childrenNodes[i]->playoutCount;
                printf("ratio: %lf, weakest: %lf and weakest child move: %d\n", ratio, weakestChildScore,
                       weakestChildMove);
                if (ratio <= weakestChildScore) {
                    weakestChildScore = ratio;
                    weakestChild = i;
                    weakestChildMove = root->childrenNodes[i]->moveFromParent;
                    printf("new weakest child %d\n", weakestChildMove);
                }
            }
        }
    }

    copyBoardStruct(boardStruct, copy, getBoardSize());

    printf("weakest child %d, score %lf, move: %d\n", weakestChild, weakestChildScore, weakestChildMove);

    assert(totalPlayoutsFromRoot == totalPlayoutsFromChildren);

    freeKids(root);

    freeBoardStruct(copy);

    return weakestChildMove;
}

