//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thinkertests/boardtests.h"
#include "board.h"
#include "../ki/alex.h"

MOVE doThink(BOARD_STRUCT *boardStruct, int moveTime) {
    printf(" XXXXXXXXXXXX received doThink command from connector, time to move %d\n", moveTime);

    if (boardStruct->sideToMove == getBlack()) {
        printf("SIDE TO MOVE IS  BLACCCCK\n");
    } else {
        printf("SIDE TO MOVE IS  WHITTTTTTTTTTTE\n");

    }

    MOVE bestMove = getBestMoveMultiThreaded(boardStruct, moveTime);

    if (bestMove == getPassMove()) {
        printf("no move from this position !\n");

    }

    printf("                                            dothinker move: %d\n", bestMove);

    return bestMove;
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