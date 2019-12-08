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
#include <signal.h>
#include "../pipe/pipe.h"
#include "../main.h"

// int doThink(BOARD_STRUCT *board, int moveTime)
// {
// 	// char *msg = malloc(3 * sizeof(char));
// 	// printf("received doThink command from connector, time to move %d\n", moveTime);

// 	MOVES allMoves = malloc(64 * sizeof(int));
// 	getLegalMovesAllPositions(board->board, switchPlayer(board->sideToMove),
// 							  allMoves);

// 	// msg[0] = allMoves[0];
// 	// msg[1] = '\0';
// 	// printf("msg:%d\n", msg[0]);
// 	// printf("dothinker move: %d\n", allMoves[0]);
// 	// /*Thinker schreibt in die Pipe rein, also schließe die Leseseite*/
// 	// // close(pd[0]);
// 	// // printf("Die Leseseite der Pipe wurde geschlossen\n");
// 	// if ((write(pd[1], msg, sizeof(msg))) != sizeof(msg))
// 	// { // In Schreibseite schreiben
// 	// 	printf("error beim write.\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	printf("***dothink() schreibt msg in pipe.***\n");

// 	free(msg);
// 	return 0; // todo, implement to return any move (later we make it good) that can legally be played on the board
// }

void doThink(BOARD_STRUCT *board, int moveTime)
{
	printf("received doThink command from connector, time to move %d\n", moveTime);

	MOVES allMoves = malloc(64 * sizeof(int));
	getLegalMovesAllPositions(board->board, switchPlayer(board->sideToMove),
							  allMoves);
	close(pd[0]);
	int *move=malloc(3*sizeof(int));
	move[0]=allMoves[0];
	move[1]='\0';
	printf("dothinker move: %d\n", allMoves[0]);
	if (write(pd[1],move, sizeof(move)) < 0)
	{
		printf("error bei Schreiben in pipe.\n");
		exit(1);
	}
	printf("***pipe in dothinker.***\n");
	free(move);
	// todo, implement to return any move (later we make it good) that can legally be played on the board
}

void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard)
{
	printf("Hi I am very good at thinking\n");

	// /*Lese aus dem shm*/
	readShm();
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
