//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>

#include "thinkertests/boardtests.h"
#include "board.h"

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

MOVE doThink(BOARD board, int moveTime) {
    printf("received doThink command from connector, time to move %d\n", moveTime);

    return 0; // todo, implement to return any move (later we make it good) that can legally be played on the board
}


void thinkerMasterMethod(BOARD thinkerBoard) {
    printf("Hi I am very good at thinking\n");

    basicTests();

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