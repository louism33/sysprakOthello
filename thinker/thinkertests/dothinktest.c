#include <stdlib.h>
#include <stdio.h>
#include "../board.h"
#include "../thinker.h"
#include "../../connector/connector.h"
#include "../../connector/boardmessageparser.h"
#include <string.h>
 infoVonServer *info;


int dothinktest() {
    printf("sizeof board:%ld\n",sizeof(BOARD_STRUCT));
    BOARD_STRUCT *b=malloc(sizeof(BOARD_STRUCT));
    BOARD_STRUCT *c=malloc(sizeof(BOARD_STRUCT));

   info->infoBoard=b;
   initialiseBoardStructToStarter(c);
   initialiseBoardStructToZero(b);//必须要这一行 否则不能运行
   printf("vor memcpy,\n");
   printBoard(b->board);
    b->board[19] = getWhite();
    b->board[20] = getBlack();
   memcpy( b->board, c->board, sizeof(int) * 8 * 8); 
   //wenn Server eine Board von uns schickt.
   b->sideToMove =c->sideToMove;
    //SIDE_TO_MOVE player = getStartingPlayer();//black
    //SIDE_TO_MOVE targetPlayer = switchPlayer(player);
   printf("b->board\n");
   printBoard(b->board);
    int move=doThink(b,3000);
    //printBoard(b->board);
   // int correctNumberOfMoves = 0;

    if (move != 26 ) {
       // printBoardLouisSide(b, player);
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
