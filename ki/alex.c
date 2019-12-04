//
// Created by louis on 11/25/19.
//

#include "alex.h"
#include <stdlib.h>

/*
 * Uses monte carlo tree search
 */

// selection expansion simulation backprop
int getBestMove(BOARD_STRUCT* boardStruct, int moveTime){
    BOARD board = boardStruct->board;
    MOVES moves = malloc(getStandardBoardSize() * sizeof(MOVE));
    int totalMoves = getLegalMovesAllPositions(board, switchPlayer(boardStruct->sideToMove), moves);

    if (totalMoves == 0) {
        return getPassMove();
    }

    if (totalMoves == 1) {
        return moves[0];
    }

    MOVE move = moves[0];

    free(moves);

    return move;
}

