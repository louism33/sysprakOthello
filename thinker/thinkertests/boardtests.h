//
// Created by louis on 11/23/19.
//

#ifndef SYSPRAKOTHELLO_BOARDTESTS_H
#define SYSPRAKOTHELLO_BOARDTESTS_H

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35


int basicTests();
int fullTestSuite();

#endif //SYSPRAKOTHELLO_BOARDTESTS_H
