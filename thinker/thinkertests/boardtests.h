//
// Created by louis on 11/23/19.
//

#ifndef SYSPRAKOTHELLO_BOARDTESTS_H
#define SYSPRAKOTHELLO_BOARDTESTS_H

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0



// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)




int basicTests();
int fullTestSuite();

#endif //SYSPRAKOTHELLO_BOARDTESTS_H
