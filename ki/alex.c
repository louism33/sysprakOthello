//
// Created by louis on 11/25/19.
//

#include "alex.h"
#include <assert.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
/*
 * Uses monte carlo tree search
 */

#define GAME_NOT_OVER (69)
#define NUMBER_OF_THREADS (2)

enum NodeType {
    ROOT = 0,
    BRANCH = 1,
    LEAF = 2,
};

typedef struct Node Node;
struct Node {
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

typedef struct Context {
    BOARD_STRUCT *boardStruct;
    Node *root;
    int moveTime;
} Context;

typedef struct Contexts {
    Context **contexts;
    int totalThreads;
} Contexts;

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


void setupRootNode(Node *node, BOARD_STRUCT *boardStruct) {
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

    node->nodeType = ROOT;
    node->parentNode = NULL;
    node->sideToMove = boardStruct->sideToMove;
    node->hasJustMoved = switchPlayer(boardStruct->sideToMove);
}


void setupNodeParentMove(Node *node, Node *parent, MOVE move) {
    assert(!node->ready);

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

void addTotalMoveInfoAllocAllChildren(Node *node, int totalMoves, MOVES moves) {
    // if there are no moves, there is still a pass move

    assert(node->ready);

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
    child->parentNode = parent;
    child->moveFromParent = move;

    parent->nodeType = parent->nodeType == ROOT ? ROOT : BRANCH;
    parent->childrenNodes[moveIndex] = child;
    parent->numberOfExpandedChildren++;

    assert(parent->numberOfChildren <= parent->numberOfChildren);
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

Node *expansion(Node *node, BOARD_STRUCT_AND_MOVES *boardStructAndMoves) {
    assert(node->ready);
    BOARD_STRUCT *boardStruct = boardStructAndMoves->boardStruct;
    if (node->gameOver) {
        assert(isGameOver(boardStruct));
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

    MOVES moves = boardStructAndMoves->moves;
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

    return child;
}


int simulation(Node *node, BOARD_STRUCT_AND_MOVES *boardStructAndMoves) {
    BOARD_STRUCT *boardStruct = boardStructAndMoves->boardStruct;
    SIDE_TO_MOVE originalSideToMove = boardStruct->sideToMove;

    if (node->gameOver) {
        return node->gameOverWinner;
    }

    int pass = 0;
    for (int i = 0; i < 100; i++) {
        if (pass == 2) {
            break;
        }

        MOVES moves = boardStructAndMoves->moves;
        int totalMoves = getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove), moves);

        if (totalMoves) {
            int r = rand() % totalMoves;
            pass = 0;
            makeMoveAI(boardStruct, moves[r]);
        } else {
            pass++;
            switchPlayerStruct(boardStruct);
        }
    }

    return getWinner(boardStruct);
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

    free(node->childrenNodes);
    free(node);
}

void freeContexts(Contexts *contexts) {
    for (int t = 0; t < contexts->totalThreads; t++) {
        Node *node = contexts->contexts[t]->root;
        freeKids(node);
        free(contexts->contexts[t]);
    }
    free(contexts->contexts);
    free(contexts);
}

MOVE getMostPlayedKidMultiThread(Contexts *contexts) {
    Node *baseRoot = contexts->contexts[0]->root;
    int totalWinsChildren = 0;
    int totalPlayoutsFromChildren = 0;
    int mostPlayedKidNumber = 0;
    MOVE mostPlayedKid = getPassMove();

    // add other thread numbers into root thread
    for (int t = 1; t < contexts->totalThreads; t++) {
        Node *thisRoot = contexts->contexts[t]->root;
        baseRoot->playoutCount += thisRoot->playoutCount;
        baseRoot->winCount += thisRoot->winCount;

        for (int i = 0; i < thisRoot->numberOfChildren; i++) {
            if (thisRoot->childrenNodes[i]) {

                assert(baseRoot->childrenNodes[i]->moveFromParent == thisRoot->childrenNodes[i]->moveFromParent);

                baseRoot->childrenNodes[i]->playoutCount += thisRoot->childrenNodes[i]->playoutCount;
                baseRoot->childrenNodes[i]->winCount += thisRoot->childrenNodes[i]->winCount;
            }
        }
    }

    for (int i = 0; i < baseRoot->numberOfChildren; i++) {

        if (baseRoot->childrenNodes[i]) {
            totalPlayoutsFromChildren += baseRoot->childrenNodes[i]->playoutCount;
            totalWinsChildren += baseRoot->childrenNodes[i]->winCount;

            if (mostPlayedKidNumber < baseRoot->childrenNodes[i]->playoutCount) {
                mostPlayedKidNumber = baseRoot->childrenNodes[i]->playoutCount;
                mostPlayedKid = baseRoot->childrenNodes[i]->moveFromParent;
            }
        }
    }

    int totalWinsRoot = baseRoot->winCount;
    assert(baseRoot->playoutCount - totalWinsRoot == totalWinsChildren);

//        printNodeLittle(baseRoot);

    int totalPlayoutsFromRoot = baseRoot->playoutCount;
    assert(totalPlayoutsFromRoot == totalPlayoutsFromChildren);
    return mostPlayedKid;
}

void *getBestMoveMultiThreadedHelper(void *vargp) {
    Context *context = (Context *) vargp;
    BOARD_STRUCT *bS = context->boardStruct;
    int moveTime = context->moveTime;
    Node *root = context->root;

    BOARD_STRUCT_AND_MOVES *boardStructAndMoves = malloc(sizeof(BOARD_STRUCT_AND_MOVES));
    BOARD_STRUCT *boardStruct = malloc(sizeof(BOARD_STRUCT));

    boardStructAndMoves->boardStruct = boardStruct;
    boardStructAndMoves->moves = malloc(getBoardSize() * sizeof(MOVE));

    initialiseBoardStructToZero(boardStruct);
    copyBoardStruct(boardStruct, bS, getBoardSize());

    BOARD_STRUCT *copy = malloc(sizeof(BOARD_STRUCT));

    initialiseBoardStructToZero(copy);
    copyBoardStruct(copy, boardStruct, getBoardSize());
    int simulationsDone = 0;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    double original_time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

    while ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 - original_time_in_mill < moveTime) {
        copyBoardStruct(boardStruct, copy, getBoardSize());

        Node *fromSelection = selection(root, boardStruct); // pick a node with no children

        Node *expandedChild = expansion(fromSelection, boardStructAndMoves); // reserve memory for children and pick one

        if (expandedChild == fromSelection) {
            assert(isGameOver(boardStruct));
        }

        int outcome = simulation(expandedChild, boardStructAndMoves); // run a game, return result

        backprop(expandedChild, outcome);

        simulationsDone++;
        gettimeofday(&tv, NULL);
    }

    copyBoardStruct(boardStruct, copy, getBoardSize());

    free(boardStructAndMoves->moves);
    freeBoardStruct(copy);
    freeBoardStruct(boardStruct);
    free(boardStructAndMoves);

    return NULL;
}

// selection expansion simulation backprop
int getBestMoveMultiThreaded(BOARD_STRUCT *boardStruct, int moveTime) {
    srand(time(NULL)); // todo move out ?

    BOARD board = boardStruct->board;
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        free(moves);
//        printf("Alex returns pass move\n");
        return getPassMove();
    }

    moveTime = moveTime - 50;

    if (totalMoves == 1 || moveTime <= 0) {
        MOVE move = moves[0];
        free(moves);
//        printf("Alex returns only move: %d\n", move);
        return move;
    }
    free(moves);

    printf("### Alex will spend %d millis searching for move\n", moveTime);

    int totalThreads = NUMBER_OF_THREADS;
    Contexts *contexts = malloc(sizeof(Contexts));
    contexts->contexts = malloc(totalThreads * sizeof(Context));

    contexts->totalThreads = totalThreads;
    pthread_t thread_id[totalThreads];

    for (int t = 0; t < totalThreads; t++) {
        struct Context *context = malloc(sizeof(Context));
        contexts->contexts[t] = context;

        context->boardStruct = boardStruct;
        context->moveTime = moveTime;

        Node *root = malloc(sizeof(Node));
        setupRootNode(root, boardStruct);

        context->root = root;

        pthread_create(&thread_id[t], NULL, getBestMoveMultiThreadedHelper, context);
    }

    for (int t = 0; t < totalThreads; t++) {
        pthread_join(thread_id[t], NULL);
    }
    MOVE move = getMostPlayedKidMultiThread(contexts);

    freeContexts(contexts);

    return move;
}
