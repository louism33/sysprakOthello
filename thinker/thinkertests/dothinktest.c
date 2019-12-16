#include <stdlib.h>
#include <stdio.h>
#include "../board.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"


int dothinktest() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = getWhite();
    board[20] = getBlack();

    SIDE_TO_MOVE player = getStartingPlayer();//black
    SIDE_TO_MOVE targetPlayer = switchPlayer(player);
   
    int move=doThink(b,3000);
    printBoard(b->board);
   // int correctNumberOfMoves = 0;

    if (move != 18 ) {
        printBoardLouisSide(b, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected  moves from this position, but received");
        printf("move: %d",move);
                
        freeBoardStruct(b);
        exit(1);
    }

    freeBoardStruct(b);
    return 0; // success
}

int basic(){
    dothinktest();
    return 0;
}
int denkentest()
{
    return basic();
}
