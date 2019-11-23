#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define ZEILE 8
#define SPALTE 8
#define EMPTY 0
#define WHITE 1
#define BLACK 2
#define RECHTSRAND i % 8 <= 7
#define LINKSRAND i % 8 >= 0
#define OBENRAND i >= position % 8
#define UNTENRAND i <= 56 + position % 8
#define LAST_MOVE (-1)

int board[63];
int i, j;
int zahl = 0;



void InitBoard()
{
    for (int i = 0; i < 63; i++)
    {
        board[i] = 0;
        //board[27] = WHITE;
        //board[28] = BLACK;
        //board[35] = BLACK;
        //board[36] = WHITE;
        
        board[14] = WHITE;

     board[10] = WHITE;

        board[46] = WHITE;


         board[17] = BLACK;

     board[21] = BLACK;

        board[53] = BLACK;

    }
}

void printBoard()
{
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");

    for (int i = 0; i < 8; i++)
    {
        printf("%d | ", i + 1);
        for (int j = 0; j < 8; j++)
        {
            int p = board[8 * i + j];
            if (p)
            {
                printf("%d ", p);
            }
            else
            {
                printf("  ");
            }
        }
        printf("| %d", i + 1);
        printf("\n");
    }

    printf("  +-----------------+ \n");
    printf("    A B C D E F G H \n");
}

void makeMove(int black)
{
    char c;
    int i; // Zeile
    printf("\n");
    while (1)
    {
        printBoard();
        scanf("%d", &i);

        if (i < 0 || i > 63)
        {
            printf("Die Koordinaten liegen außerhalb des gültigen Bereichs. Bitte geben Sie sie erneut ein.\n");
            continue;
        }
        else if (board[i] != 0)
        {
            printf("Die Koordinaten sind bereits belegt!\n");
            continue;
        }
        else
        {
            if (black)
            {
                board[i] = BLACK;
            }
            else
            {
                board[i] = WHITE;
            }
            black = 1 - black;
        }
    }
}



// move ist ein int zwischen 0 und 63
// 0 -> A1 ..... 63 -> H8


int *getLegalMovesOnePosition(int *board, int position, int TARGET_PLAYER)
{
    int *speicher;
    speicher = (int *)malloc(64 * sizeof(int));
    int index = 0;
    int MY_PLAYER = 3 - TARGET_PLAYER;

    if (board[position] != MY_PLAYER){
        printf("i don't have a player on this square\n");
        exit(1);
    }

    //printf("position is %d\n", position);

    // for-Schleifer um nach rechts zu prüfen
    for (int i = position + 1; i % 8 <= 7; i++)
    {
        //TODO: nicht machen in Spalte 7
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position + 1] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }

    // for-Schleifer um nach links zu prüfen
    for (int i = position - 1; i % 8 >= 0; i--)
    {
        //TODO: nicht machen in Spalte 0
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position - 1] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }
 
    // for-Schleifer um nach unten zu prüfen
    for (int i = position + 8; i < 64; i = i + 8)
    {
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position + 8] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }

    // for-Schleifer um nach oben zu prüfen
    for (int i = position - 8; i>-1; i = i - 8)
    {
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position - 8] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }

 
    // index = index + 1;
    // for-Schleifer um nach rechts oben zu prüfen
    for (int i = position - 7; i>-1 && i % 8 <= 7; i = i - 7)
    {
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position - 7] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }

    //index = index + 1;
    // for-Schleifer um nach links oben zu prüfen
    for (int i = position - 9; i>-1 && i % 8 >= 0; i = i - 9)
    {
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position - 9] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }

    //index = index + 1;
    // for-Schleifer um nach rechts unten zu prüfen
    for (int i = position + 9; i<64 && i % 8 <= 7; i = i + 9)
    {
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position + 9] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }

    // index = index + 1;
    // for-Schleifer um nach links unten zu prüfen
    for (int i = position + 7; i<64 && i % 8 >= 0; i = i + 7)
    {
        if (board[i] == TARGET_PLAYER)
        {
            continue;
        }
        if (board[i] == MY_PLAYER)
        {
            break;
        }
        if (board[i] == EMPTY && board[position + 7] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index++] = i;
            zahl++;
            printf("found move:%d\n", speicher[index-1]);
            break;
        }
    }
       



    speicher[index] = LAST_MOVE;
    return speicher;
    
}

int *getLegalMovesAllPositions(int *board, int TARGET_PLAYER)
{   
    int *allMoves = malloc(64 * sizeof(int));
    int me = 3 - TARGET_PLAYER;
    int index = 0;
    for(int pos = 0; pos < 64; pos++){
        if(board[pos] == me){
            int* legalMovesFromHere = getLegalMovesOnePosition(board,pos,TARGET_PLAYER);
            int j = 0;
            while(1){
                if(legalMovesFromHere[j]== LAST_MOVE){
                    break;
                }
                allMoves[index++] = legalMovesFromHere[j++]; 
            }
        }
    }

 

    allMoves[index] = LAST_MOVE;
    return allMoves;
}


  int getTotalNumberOfLegalMovesHM(int *board, int TARGET_PLAYER){

    int * legalMoves = getLegalMovesAllPositions(board, TARGET_PLAYER);
    int total = 0;

    for (int i = 0 ; i < 64; i++){
        if (legalMoves[i] == LAST_MOVE){
            return total;
        }
        total++;
    }
    printf("did not find a LAST_MOVE... are you sure you did not nake a mistake\n");
    exit(1);
   // return total;
} 


// int main()
// {
//     InitBoard();
//     //makeMove(1); // ilegale Züge werden ausgeschlossen.
//     //getLegalMoves(board, 36, BLACK);

//     printBoard();

//     int total = getTotalNumberOfLegalMovesHM(board, WHITE);
//     printf("TOTAL ISSSS..... %d\n", total);

//     return 0;
// }
