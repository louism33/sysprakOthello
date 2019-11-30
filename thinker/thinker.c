//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>
#include <stdlib.h>

#include "thinkertests/boardtests.h"
#include "board.h"

MOVE doThink(BOARD_STRUCT *board, int moveTime)
{
	printf("received doThink command from connector, time to move %d\n", moveTime);

	printf("ccccc\n");

	MOVES allMoves = malloc(64 * sizeof(int));
	getLegalMovesAllPositions(board->board, switchPlayer(board->sideToMove),
							  allMoves);

	printf("ddddd\n");
    
	printf("dothinker move: %d\n", allMoves[0]);
	return allMoves[0]; // todo, implement to return any move (later we make it good) that can legally be played on the board
}

void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard)
{
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
void think()
{
	/* readShm()
    makeMove1()
    makeMove2()
    printBoard()
    writePipe()*/
}