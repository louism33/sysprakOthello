#include <stdio.h>
#include <stdlib.h>
#define ZEILE 8
#define SPALTE 8
char board[ZEILE][SPALTE];
int i,j;

void InitBoard(){
    for(int i= 0; i < ZEILE; i++){
        for(int j = 0; j < SPALTE;j++){
            board[i][j] = '.';
        }
    }
}

void print(){
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");

    for(int i= 0; i < ZEILE; i++){
        printf("%d | ",i+1);
        for(int j = 0; j < SPALTE;j++){
        printf("%c ",board[i][j]);
        }
        printf("| %d",i+1);
        printf("\n");
    }

    printf("  +-----------------+ \n");
    printf("    A B C D E F G H \n");
}

void move1(){ //move1(char i, int j)
    int i = 0;
    int j = 0;
    printf("\n");
    scanf("%d,%d",&i,&j);
    printf("\n");
    while (1){
        if (i < 0 || i >= ZEILE || j < 0 || j >= SPALTE){
			printf("Die Koordinaten liegen außerhalb des gültigen Bereichs. Bitte geben Sie sie erneut ein.\n");
            //continue;
		}
		if (board[i-1][j-1] != '.'){
			printf("Die Koordinaten sind bereits belegt!\n");
            //continue;
		}
        else
		board[i-1][j-1] = '0';
        break;
    }
}

void move2(){
    int i = 0;
    int j = 0;
    printf("\n");
    scanf("%d,%d",&i,&j);
    printf("\n");
    while (1){
        if (i < 0 || i >= ZEILE || j < 0 || j >= SPALTE){
			printf("Die Koordinaten liegen außerhalb des gültigen Bereichs. Bitte geben Sie sie erneut ein.\n");
            //continue;
		}
		if (board[i-1][j-1] != '.'){
			printf("Die Koordinaten sind bereits belegt!\n");
            //continue;
		}
        else
		board[i-1][j-1] = '#';
        break;
    }
}


int main(){
    InitBoard();
    print();
    move1();
    print();
    move2();
    print();
    return 0;
}