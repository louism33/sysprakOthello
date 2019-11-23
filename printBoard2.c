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

int board[63];
int i, j;
int zahl = 0;

void InitBoard()
{
    for (int i = 0; i < 63; i++)
    {
        board[i] = 0;
        board[27] = WHITE;
        board[28] = BLACK;
        board[35] = BLACK;
        board[36] = WHITE;
        board[29] = BLACK;
        board[44] = BLACK;
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

  int getTotalNumberOfLegalMoves()
{   
    //int length = sizeof(speicher) / sizeof(int);
    printf("Total number of legal moves: %d\n",zahl);
    return 0;
} 

// move ist ein int zwischen 0 und 63
// 0 -> A1 ..... 63 -> H8

int *getLegalMoves(int *board, int position, int TARGET_PLAYER)
{
    int *speicher;
    speicher = (int *)malloc(64 * sizeof(int));
    int index = 0;
    int MY_PLAYER = 3 - TARGET_PLAYER;

    // for-Schleifer um nach rechts zu prüfen
    for (int i = position + 1; RECHTSRAND; i++)
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
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach links zu prüfen
    for (int i = position - 1; LINKSRAND; i--)
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
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach unten zu prüfen
    for (int i = position + 8; UNTENRAND; i = i + 8)
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
        if (board[i] == EMPTY && board[position + 8] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach oben zu prüfen
    for (int i = position - 8; OBENRAND; i = i - 8)
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
        if (board[i] == EMPTY && board[position - 8] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach rechts oben zu prüfen
    for (int i = position - 7; RECHTSRAND && OBENRAND; i = i - 7)
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
        if (board[i] == EMPTY && board[position - 7] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach links oben zu prüfen
    for (int i = position - 9; LINKSRAND && OBENRAND; i = i - 9)
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
        if (board[i] == EMPTY && board[position - 9] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach rechts unten zu prüfen
    for (int i = position + 9; RECHTSRAND && UNTENRAND; i = i + 9)
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
        if (board[i] == EMPTY && board[position + 9] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }

    index = index + 1;
    // for-Schleifer um nach links unten zu prüfen
    for (int i = position + 7; LINKSRAND && UNTENRAND; i = i + 7)
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
        if (board[i] == EMPTY && board[position + 7] == TARGET_PLAYER)
        {
            // legal move!!!
            speicher[index] = i;
            zahl++;
            printf("%d\n", speicher[index]);
            break;
        }
    }
    return speicher;
    free(speicher);
}

int main()
{
    InitBoard();
    //makeMove(1); // ilegale Züge werden ausgeschlossen.
    getLegalMoves(board, 36, BLACK);
    getTotalNumberOfLegalMoves();
    return 0;
}
