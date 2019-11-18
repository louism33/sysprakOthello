//
// Created by louis on 11/13/19.
//
#include "shm/shm.h"
#include "thinker.h"
#include <stdio.h>


void thinkerMasterMethod(){
    printf("Hi I am very good at thinking\n");

    createProcesses();
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