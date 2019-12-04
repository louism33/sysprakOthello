//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>
#include <stdlib.h>

#include "thinkertests/boardtests.h"
#include "board.h"
#include "../ki/alex.h"

MOVE doThink(BOARD_STRUCT *boardStruct, int moveTime) {
    printf("received doThink command from connector, time to move %d\n", moveTime);

    MOVES allMoves = malloc(getBoardSize() * sizeof(int));
    getLegalMovesAllPositions(boardStruct->board, switchPlayer(boardStruct->sideToMove),
                              allMoves);


    MOVE bestMove = getBestMove(boardStruct, moveTime);

//    if (allMoves[0] == getLastMove()) {
//        printf("   +++++++++++++++ COULD NOT FIND  A MOVE FROM THIS POSITION !!!!\n");
//    }
    if (bestMove == getLastMove()) {
        printf("   +++++++++++++++ COULD NOT FIND  A MOVE FROM THIS POSITION !!!!\n");
    }

//	printf("dothinker move: %d\n", allMoves[0]);
    printf("dothinker move: %d\n", bestMove);

    return allMoves[0];
}

void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard) {
    printf("Hi I am very good at thinking\n");

    //createProcesses();

    /*
    was wir brauchen für die thinkerMasterMethod
    - eine printBoard() Funktion
    -signal Handler mit getSignal(), sendSignal() etc.

    enthält makeTurn()
    sendTurn()
    unnamed Pipe erstllen -- bevor fork()!
    Seiten schließen
    makeTurn()
    makeMove()
    isLegalMove()
    canPlay()
    */
}

/*think() Methode: wartet auf Signal SIGURS1 und ließt anschließend alle benötigten Infos
 aus dem SM und berechnet Spielzug*/
void think() {
    /* readShm()
    makeMove1()
    makeMove2()
    printBoard()
    writePipe()*/
}