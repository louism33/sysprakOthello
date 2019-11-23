#include <stdio.h>
#include <stdlib.h>
#define ZEILE 8
#define SPALTE 8
char board[ZEILE][SPALTE];
int i, j;

void InitBoard()
{
    for (int i = 0; i < ZEILE; i++)
    {
        for (int j = 0; j < SPALTE; j++)
        {   
            board[i][j] = '.';
            board[3][3] = '#';
            board[3][4] = '0';
            board[4][4] = '#';
            board[4][3] = '0';
        }
    }
}

void printBoard()
{
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");

    for (int i = 0; i < ZEILE; i++)
    {
        printf("%d | ", i + 1);
        for (int j = 0; j < SPALTE; j++)
        {
            printf("%c ", board[i][j]);
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
    int i = 0; // Zeile
    printf("\n");
    while (1)
    {
        printBoard();
        scanf("%c%d", &c, &i);
        int j = (int)c - 65; // Spalte

        if (i < 0 || i > ZEILE || j < 0 || j > SPALTE)
        {
            printf("Die Koordinaten liegen außerhalb des gültigen Bereichs. Bitte geben Sie sie erneut ein.\n");
            continue;
        }
        else if (board[i - 1][j] != '.')
        {
            printf("Die Koordinaten sind bereits belegt!\n");
            continue;
        }
        else
        {
            if (black)
            {
                board[i - 1][j] = '0';
            }
            else
            {
                board[i - 1][j] = '#';
            }
            black = 1 - black;
        }
    }
}

int main()
{
    InitBoard();
    makeMove(1); // ilegale Züge werden ausgeschlossen.
    return 0;
}

// move ist ein int zwischen 0 und 63
// 0 -> A1 ..... 63 -> H8

int* getLegalMoves(char** board){
    return NULL;
}