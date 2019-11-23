//
// Created by louis on 11/13/19.
//
#include "../shm/shm.h"
#include "thinker.h"
#include <stdio.h>

#include "thinkertests/boardtests.h"
#include "../printBoard2.h"

#define MOVE int
#define BOARD int*
#define SIDE_TO_MOVE int

//int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE player){
	//  printf("debug3\n");
    // return getTotalNumberOfLegalMovesHM(board, player);
// }


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