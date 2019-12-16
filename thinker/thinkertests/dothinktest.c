#include <stdlib.h>
#include <stdio.h>
#include "../board.h"
#include "../thinker.h"
#include "../../connector/connector.h"
#include "../../connector/boardmessageparser.h"




int dothinktest() {
//     infoVonServer *info;
//      BOARD_STRUCT *infoBoard;
//    // info->infoBoard=b;
//    info->infoBoard=infoBoard;

//     for (int i = 0; i < 20; i++) {
//         info->infoBoard->board[i] = getWhite();
//     }
//     for (int i = 20; i < 63; i++) {
//         info->infoBoard->board[i] = getBlack();
//     }

//     SIDE_TO_MOVE player = getStartingPlayer();//black
//     SIDE_TO_MOVE targetPlayer = switchPlayer(player);
   
//     int move=doThink(info->infoBoard,3000);
//     printBoard(info->infoBoard->board);
//    // int correctNumberOfMoves = 0;

    if (move != 0 ) {
        printBoardLouisSide(info->infoBoard, player);
        fprintf(stderr, "FAILED A BOARD TEST! Expected  moves from this position, but received");
        printf("move: %d",move);
                
       // freeBoardStruct(b);
        exit(1);
    }

   // freeBoardStruct(b);
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
