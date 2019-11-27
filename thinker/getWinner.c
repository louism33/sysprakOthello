#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "board.h"
//#include "getWinner.h"

#define BLACK 2
#define WHITE 1

/*  int board[63];

void resetBoardToStarter(int *board) {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
    //srand((unsigned)time(NULL));
    //for(int j =0; j< 64; j++){
        //srand(time(0));
        //board[j]=random()%3;
    //}
    board[27] = WHITE;
    board[28] = BLACK;
    board[35] = BLACK;
    board[36] = WHITE;
    
}

void resetBoardToZero(int *board) {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
}

void printBoard(int *board) {
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");

    for (int i = 0; i < 8; i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < 8; j++) {
            int p = board[8 * i + j];
            if (p) {
                printf("%d ", p);
            } else {
                printf("  ");
            }
        }
        printf("| %d", i + 1);
        printf("\n");
    }

    printf("  +-----------------+ \n");
    printf("    A B C D E F G H \n");
} */

int getWinner(int *board){
    int anzahlBlack = 0;
    int anzahlWhite = 0;
    for(int i = 0;i <64;i++){
        if(board[i] == BLACK) anzahlBlack++;
    }
        for(int j = 0;j<64;j++){
        if(board[j] == WHITE) anzahlWhite++;
    }
    printf("%d %d \n",anzahlBlack,anzahlWhite);

        if(anzahlBlack > anzahlWhite) printf("%d\n",BLACK); //return BLACK;
        else if (anzahlBlack < anzahlWhite++) printf("%d\n",WHITE); //return WHITE;
        else printf("%d\n",0); //return 0;
        return 0;
}

/* int main(){
    //resetBoardToZero(board);
    //resetBoardToStarter(board);
    //printBoard(board);
    getWinner(board);
    return 0;
} */