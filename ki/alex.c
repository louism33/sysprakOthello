//
// Created by louis on 11/25/19.
//

#include "alex.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
/*
 * Uses monte carlo tree search
 */

#define GAME_NOT_OVER (69)

enum NodeType {
    ROOT = 0,
    BRANCH = 1,
    LEAF = 2,
};

typedef struct Node Node;
struct Node {
    // add unique ID? (moves made)
    enum NodeType nodeType;
    int playoutCount; // we add two each time because we want to work with ints
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
    SIDE_TO_MOVE gameOverWinner;
    SIDE_TO_MOVE sideToMove;
    SIDE_TO_MOVE hasJustMoved;
};

void setupNode(Node *node) {

//    if (node->ready) {
//    printf("node already ready \n");
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
    node->hasJustMoved = getEmpty();
    node->gameOverWinner = GAME_NOT_OVER;
}


void setupNodeParent(Node *node, Node *parent) {

//    if (node->ready) {
//    printf("node already ready \n");
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
    node->hasJustMoved = switchPlayer(parent->hasJustMoved);
    node->gameOverWinner = GAME_NOT_OVER;
}


void setupNodeParentMove(Node *node, Node *parent, MOVE move) {
//    if (node->ready) {
//    printf("node already ready \n");
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
    node->hasJustMoved = switchPlayer(parent->hasJustMoved);
    node->gameOverWinner = GAME_NOT_OVER;
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
    printf("**    side   : %d, %s\n", node->sideToMove, node->sideToMove == getBlack() ? "BLACK" : "WHITE");
    printf("**  hasjust  : %d, %s\n", node->hasJustMoved, node->hasJustMoved == getBlack() ? "BLACK" : "WHITE");
    printf("** gameover? : %s\n", node->gameOver ? "YES" : "NO");
    if (node->gameOver) {
        printf("** WINNER : %s\n", node->gameOverWinner == getWhite() ? "WHITE" : "BLACK");
        printf("** this is : %s\n", node->gameOverWinner == node->hasJustMoved ? "GOOD for me" : "BAD for me");
    }
    printf("** movesReady: %d\n", node->movesReady);
    printf("**    ready  : %d\n", node->ready);
    printf("**\n");
}

void printNodeLittle(Node *node) {
    printf("*** type: %s, my&: %p, parent: %p, move: %d, passNode: %d, w/p: %d/%d, hasJustMoved: %s, g/o? %s, %s\n",
           node->nodeType == ROOT ? "R" : node->nodeType == BRANCH ? "B" : "L", node, node->parentNode,
           node->moveFromParent, node->passNode,
           node->winCount, node->playoutCount, node->hasJustMoved == getBlack() ? "B" : "W",
           node->gameOver ? "Y" : "N",
           node->gameOver ? node->gameOverWinner == getWhite() ? "Winner WHITE" : "Winner BLACK" : "");
}

void addTotalMoveInfo(Node *node, int totalMoves) {
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
}

void addTotalMoveInfoAllocAllChildren(Node *node, int totalMoves, MOVES moves) { // todo careful of passes
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
        setupNodeParentMove(node->childrenNodes[i], node, moves[i]);
    }

    node->movesReady = 1;
}

void expandNodeMove(Node *child, Node *parent, int moveIndex, MOVE move) {
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

#define ROOT_TWO (1.414)

double getUCT(Node *node) {
    assert(node->nodeType != ROOT);
    if (!node->playoutCount || !node->parentNode->playoutCount) {
        return 1;
    }
    int ni = node->playoutCount;
    return (((double) node->winCount / ni) +
            (double) ROOT_TWO * sqrt((log(node->parentNode->playoutCount)) / ni));
}

Node *selection(Node *node, BOARD_STRUCT *boardStruct) {
    if (node->nodeType == ROOT && node->playoutCount == 0) {
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

    if (node->passNode) {
        switchPlayerStruct(boardStruct);
        return selection(node->childrenNodes[0], boardStruct);
    }

    int r;
    double bestUCT = -1;
    for (int i = 0; i < node->numberOfChildren; i++) {
        double thisUCT = getUCT((node->childrenNodes[i]));
        if (thisUCT > bestUCT) {
            bestUCT = thisUCT;
            r = i;
        }
    }

    if (node->childrenNodes[r]->moveFromParent != getPassMove()) {
        assert(node->childrenNodes[r]->moveFromParent != getPassMove());
        assert(node->childrenNodes[r]->moveFromParent >= 0);
        assert(node->childrenNodes[r]->moveFromParent < getBoardSize());
        assert(!node->childrenNodes[r]->parentNode->passNode);

        makeMoveAI(boardStruct, node->childrenNodes[r]->moveFromParent);
    } else {
        assert(node->childrenNodes[r]->parentNode->passNode);

        switchPlayerStruct(boardStruct);
    }

    return selection(node->childrenNodes[r], boardStruct);
}

Node *expansion(Node *node, BOARD_STRUCT *boardStruct) {
    assert(node->ready);

    if (node->gameOver) {
        assert(isGameOver(boardStruct));
//        int w = getWinner(boardStruct);
        int w = node->gameOverWinner;

        if (node->hasJustMoved == w) {
            assert(node->gameOverWinner == node->hasJustMoved);
        } else if (w == getDraw()) {
            assert(node->gameOverWinner == getDraw());
        } else {
            assert(node->gameOverWinner == switchPlayer(node->hasJustMoved));
        }
        return node;
    }

    // todo, not always necessary to do this generation
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
            int w = getWinner(boardStruct);
            if (node->hasJustMoved == w) {
                node->gameOverWinner = node->hasJustMoved;
            } else if (w == getDraw()) {
                node->gameOverWinner = getDraw();
            } else {
                node->gameOverWinner = switchPlayer(node->hasJustMoved);
            }
            return node;
        } else {
            assert(totalMoves == 0);
            addTotalMoveInfoAllocAllChildren(node, 1, moves);
            switchPlayerStruct(boardStruct);
            Node *child = node->childrenNodes[0];
            expandNodeMove(child, node, 0, getPassMove());
            free(moves);
            return child;
        }

    }
    addTotalMoveInfoAllocAllChildren(node, totalMoves, moves);

    int r = -1;
    double bestUCT = -1;
    for (int i = 0; i < node->numberOfChildren; i++) {
        double thisUCT = getUCT((node->childrenNodes[i]));
        if (thisUCT > bestUCT) {
            bestUCT = thisUCT;
            r = i;
        }
    }

    if (r == -1) {
        printf("no uct child selected?\n");
        exit(1);
    }

    assert(totalMoves > 0);

    MOVE move = moves[r];
    assert(moves[r] != getLastMove());
    assert(moves[r] != getPassMove());
    makeMoveAI(boardStruct, move);

    Node *child = node->childrenNodes[r];

    assert(child);

    expandNodeMove(child, node, r, move);

    free(moves);
    return child;
}


int simulation(Node *node, BOARD_STRUCT *boardStruct) {
    SIDE_TO_MOVE originalSideToMove = boardStruct->sideToMove;

    if (node->gameOver) {
        return node->gameOverWinner;
    }

    int passs = 0;
    for (int i = 0; i < 100; i++) {
        if (i > 80) {
            printf("80 moves in one game?????;");
            printBoardSide(boardStruct);
        }
        if (passs == 2) {
            break;
        }

        MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
        int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

        if (totalMoves) {
            int r = rand() % totalMoves;
            passs = 0;
            makeMoveAI(boardStruct, moves[r]);
        } else {
            passs++;
            switchPlayerStruct(boardStruct);
        }

        free(moves);
    }

    return getWinner(boardStruct);
}

int switchOutcome(int outcome) {
    return -outcome;
}

int backprop(Node *finalNode, int outcome) {
    Node *temp = finalNode;
    if (!temp->parentNode) {
        assert(temp->nodeType == ROOT);
    }

    do {
        if (!temp->parentNode) {
            assert(temp->nodeType == ROOT);
        }
        temp->playoutCount += 2;

        if (outcome == temp->hasJustMoved) {
            temp->winCount += 2;
        } else if (outcome == getDraw()) {
            temp->winCount++;
        }
        temp = temp->parentNode;
    } while (temp);

    return 0;
}

void freeKids(Node *node) {
    for (int i = 0; i < node->numberOfChildren; i++) {
        if (node->childrenNodes) {
            if (node->childrenNodes[i]) {
                freeKids(node->childrenNodes[i]);
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

    BOARD board = boardStruct->board;
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        free(moves);
        printf("Alex returns pass move\n");
        return getPassMove();
    }

    if (totalMoves == 1) {
        MOVE move = moves[0];
        free(moves);
        printf("Alex returns only move: %d\n", move);
        return move;
    }

    BOARD_STRUCT *copy = malloc(sizeof(BOARD_STRUCT));

    initialiseBoardStructToZero(copy);
    copyBoardStruct(copy, boardStruct, getBoardSize());

    MOVE move = moves[0];

    Node *root = malloc(sizeof(Node));
    setupNode(root);
    root->nodeType = ROOT;
    root->parentNode = NULL;
    root->sideToMove = boardStruct->sideToMove;
    root->hasJustMoved = switchPlayer(boardStruct->sideToMove);

    free(moves);

    int simulationsDone = 0;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    double original_time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

    while ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 - original_time_in_mill < moveTime) {
        copyBoardStruct(boardStruct, copy, getBoardSize());

        Node *fromSelection = selection(root, boardStruct); // pick a node with no children

        Node *expandedChild = expansion(fromSelection, boardStruct); // reserve memory for children and pick one

        if (expandedChild == fromSelection) {
            assert(isGameOver(boardStruct));
        }

        int outcome = simulation(expandedChild, boardStruct); // run a game, return result

        backprop(expandedChild, outcome);

        simulationsDone++;
        gettimeofday(&tv, NULL);
    }

    printNodeLittle(root);

    int totalWinsRoot = root->winCount;
    int totalWinsChildren = 0;

    int totalPlayoutsFromRoot = root->playoutCount;
    int totalPlayoutsFromChildren = 0;
    int mostPlayoutsFromChild = 0;
    double weakestChildScore = 100;
    MOVE weakestChild = 0;
    MOVE weakestChildMove = getLastMove();

    int mostPlayedKidNumber = 0;
    MOVE mostPlayedKid = getPassMove();

    for (int i = 0; i < root->numberOfChildren; i++) {
        if (root->childrenNodes[i]) {
            totalPlayoutsFromChildren += root->childrenNodes[i]->playoutCount;
            mostPlayoutsFromChild =
                    root->childrenNodes[i]->playoutCount > mostPlayoutsFromChild ? root->childrenNodes[i]->playoutCount
                                                                                 : mostPlayoutsFromChild;

//            printNode(root->childrenNodes[i]);
            printNodeLittle(root->childrenNodes[i]);

            totalWinsChildren += root->childrenNodes[i]->winCount;

            if (root->childrenNodes[i]->playoutCount) {
                double ratio = (double) root->childrenNodes[i]->winCount / root->childrenNodes[i]->playoutCount;
                if (ratio <= weakestChildScore) {
                    weakestChildScore = ratio;
                    weakestChild = i;
                    weakestChildMove = root->childrenNodes[i]->moveFromParent;
                }
            }

            if (mostPlayedKidNumber < root->childrenNodes[i]->playoutCount) {
                mostPlayedKidNumber = root->childrenNodes[i]->playoutCount;
                mostPlayedKid = root->childrenNodes[i]->moveFromParent;
            }
        }
    }

    assert(root->playoutCount - totalWinsRoot == totalWinsChildren);

    copyBoardStruct(boardStruct, copy, getBoardSize());

    assert(totalPlayoutsFromRoot == totalPlayoutsFromChildren);

    freeKids(root);
    freeBoardStruct(copy);

//    printf("Alex returns move: %d\n", mostPlayedKid);

    return mostPlayedKid;
}
