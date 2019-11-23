//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_THINKER_H
#define ALEXTHEFRIENDLYAI_THINKER_H

#define MOVE int
#define MOVES int*
#define BOARD int*
#define SIDE_TO_MOVE int

extern void thinkerMasterMethod();
void think();

void thinkerMasterMethod();


MOVE doThink(BOARD board, int moveTime);

//int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE player);

MOVES getLegalMoves(BOARD board, SIDE_TO_MOVE player);

#endif //ALEXTHEFRIENDLYAI_THINKER_H
