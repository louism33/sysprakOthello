//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_THINKER_H
#define ALEXTHEFRIENDLYAI_THINKER_H


#define MOVE int
#define SIDE_TO_MOVE int
#define BOARD int*
#define MOVES int*

#define BLACK 2
#define WHITE 1

#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

#define STARTING_PLAYER BLACK
#define SWITCH_PLAYER_CONSTANT 3

void thinkerMasterMethod(BOARD thinkerBoard);

MOVE doThink(BOARD board, int moveTime);

MOVES getLegalMoves(BOARD board, SIDE_TO_MOVE player);

#endif //ALEXTHEFRIENDLYAI_THINKER_H
