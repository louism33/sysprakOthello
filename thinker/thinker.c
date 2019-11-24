//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>

#include "thinkertests/boardtests.h"
#include "board.h"
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


MOVE doThink(BOARD_STRUCT  board, int moveTime) {
    printf("received doThink command from connector, time to move %d\n", moveTime);

    return 0; // todo, implement to return any move (later we make it good) that can legally be played on the board
}


void thinkerMasterMethod(BOARD_STRUCT  thinkerBoard) {
    printf("Hi I am very good at thinking\n");

    printBoard(thinkerBoard.board);

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