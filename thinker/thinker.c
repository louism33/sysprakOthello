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

MOVE doThink(BOARD_STRUCT *board, int moveTime)
{
	printf("in do think:\n");
	printBoard(board->board);
	printf("received doThink command from connector, time to move %d\n", moveTime);

	MOVES allMoves = malloc(64 * sizeof(int));
	getLegalMovesAllPositions(board->board, switchPlayer(board->sideToMove),
							  allMoves);

	printf("dothinker move: %d\n", allMoves[0]);
	return allMoves[0]; // todo, implement to return any move (later we make it good) that can legally be played on the board
}


void thinkerMasterMethod(BOARD_STRUCT *thinkerBoard)
{
	printf("Hi I am very good at thinking\n");
}

