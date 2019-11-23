//
// Created by louis on 11/13/19.
//

#include "thinker.h"
#include <stdio.h>

#include "thinkertests/boardtests.h"

#define MOVE int
#define BOARD int*
#define SIDE_TO_MOVE int

int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE player){
    return 0;
}


MOVES getLegalMoves(BOARD board, SIDE_TO_MOVE player){
    return NULL;
}


MOVE doThink(BOARD board , int moveTime){
    printf("received doThink command from connector, time to move %d\n", moveTime);

    return 0; // todo, implement to return any move (later we make it good) that can legally be played on the board
}




void thinkerMasterMethod(){
    printf("Hi I am very good at thinking\n");
    basicTests();

}
