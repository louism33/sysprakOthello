#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "board.h"

#define ZEILE 8
#define SPALTE 8

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
#define SWITCH_PLAYER_CONSTANT (BLACK + WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

#define LAST_MOVE (-1)

MOVE getLastMove()
{
    return LAST_MOVE;
}

SIDE_TO_MOVE getStartingPlayer()
{
    return STARTING_PLAYER;
}

SIDE_TO_MOVE getBlack()
{
    return BLACK;
}

SIDE_TO_MOVE getWhite()
{
    return WHITE;
}

SIDE_TO_MOVE getEmpty()
{
    return EMPTY;
}

SIDE_TO_MOVE switchPlayer(SIDE_TO_MOVE sideToMove)
{
    return SWITCH_PLAYER_CONSTANT - sideToMove;
}

void resetBoardToStarter(BOARD board)
{
    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
    }
    // todo, if the coordinates are not 8x8, this would be wrong, so make sure not to call this in gameloop
    board[STARTING_WHITE_POSITION_1] = WHITE;
    board[STARTING_WHITE_POSITION_2] = WHITE;
    board[STARTING_BLACK_POSITION_1] = BLACK;
    board[STARTING_BLACK_POSITION_2] = BLACK;
}

void resetBoardToZero(BOARD board)
{
    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
    }
}

void freeBoardStruct(BOARD_STRUCT *boardStruct)
{
    //    free(boardStruct->stack->stackArray);
    //    free(boardStruct->stack);
    free(boardStruct->board);
}

void initialiseBoardStructToStarter(BOARD_STRUCT *boardStruct)
{
    boardStruct->board = malloc(64 * sizeof(int));
    resetBoardToStarter(boardStruct->board);
    boardStruct->sideToMove = STARTING_PLAYER;
}

void initialiseBoardStructToZero(BOARD_STRUCT *boardStruct)
{
    boardStruct->board = malloc(64 * sizeof(int));
    resetBoardToZero(boardStruct->board);
    boardStruct->sideToMove = STARTING_PLAYER;
}

void printBoard(BOARD board)
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

void addColourToSquare(BOARD board, SIDE_TO_MOVE sideToMove, MOVE move)
{
    if (move < 0 || move > 63)
    {
        printf("Die Koordinaten liegen außerhalb des gültigen Bereichs. Bitte geben Sie sie erneut ein.\n");
        exit(1);
    }
    else if (board[move] != 0)
    {
        printf("Die Koordinaten sind bereits belegt!\n");
        exit(1);
    }
    else
    {
        if (sideToMove == BLACK)
        {
            board[move] = BLACK;
        }
        else
        {
            board[move] = WHITE;
        }
    }
}

int *getLegalMovesOnePosition(BOARD board, int *speicher, int position, SIDE_TO_MOVE TARGET_PLAYER)
{
    int index = 0;
    int MY_PLAYER = 3 - TARGET_PLAYER;
    int zeile = (8 - position / 8);
    int spalte = position % 8;

    if (board[position] != MY_PLAYER)
    {
        printf("i don't have a player on this square\n");
        exit(1);
    }

    printf("position is %d\n", position);

    //for-Schleifer um nach rechts zu prüfen
    if (spalte != 6 && spalte != 7)
    {
        //  printf("-----in rechts for Schleife.\n");
        if (board[position + 1] == TARGET_PLAYER)
        {
            int i = position + 2;
            while (1)
            {
                if (i % 8 == 0)
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER)
                {
                    i++;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach links zu prüfen
    printf("aaaaaa\n");
    if (spalte != 0 && spalte != 1)
    {
        //  printf("-----in link for Schleife.\n");
        if (board[position - 1] == TARGET_PLAYER)
        {
            int i = position - 2;
            while (1)
            {
                if (i % 8 == 7)
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER)
                {
                    i--;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach unten zu prüfen

    if (zeile != 1 && zeile != 2)
    {
        //  printf("-----in unten for Schleife.\n");
        if (board[position + 8] == TARGET_PLAYER)
        {
            int i = position + 16;
            while (1)
            {
                if (i >= 64)
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER)
                {
                    i += 8;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }
    // printf("bbbbb\n");
    // for-Schleifer um nach oben zu prüfen
    if (zeile != 8 && zeile != 7)
    {
        //  printf("-----in oben for Schleife.\n");
        if (board[position - 8] == TARGET_PLAYER)
        {
            int i = position - 16;
            while (1)
            {
                if (i < 0) //zeile
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER)
                {
                    i -= 8;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach rechts oben zu prüfen
    if (spalte != 6 && spalte != 7 && zeile != 8 && zeile != 7)
    {
        //  printf("-----in link oben for Schleife.\n");
        if (board[position - 7] == TARGET_PLAYER)
        {
            int i = position - 14;
            while (1)
            {
                if (i % 8 == 0) //spalte
                {
                    break;
                }
                if (i < 0) //zeile
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER)
                {
                    i -= 7;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }

    // for-Schleifer um nach links oben zu prüfen
    if (spalte != 0 && spalte != 1 && zeile != 8 && zeile != 7)
    {
        //  printf("-----in link oben for Schleife.\n");
        if (board[position - 9] == TARGET_PLAYER)
        {
            int i = position - 18;
            while (1)
            {
                if (i % 8 == 7) //zeile
                {
                    break;
                }
                if (i < 0) //spalte
                {
                    break;
                }

                if (board[i] == TARGET_PLAYER)
                {
                    i -= 9;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }
    // printf("dddddd\n");
    // for-Schleifer um nach rechts unten zu prüfen
    if (spalte != 6 && spalte != 7 && zeile != 1 && zeile != 2)
    {
        //  printf("-----in link unten for Schleife.\n");
        if (board[position + 9] == TARGET_PLAYER)
        {
            int i = position + 18;
            while (1)
            {
                if (i >= 64)
                { //zeile
                    break;
                }
                if (i % 8 == 0) //spalte
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER)
                {
                    i += 9;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }
    printf("eeeee\n");
    //  for-Schleifer um nach links unten zu prüfen
    if (spalte != 0 && spalte != 1 && zeile != 1 && zeile != 2)
    {
        // printf("-----in link unten for Schleife.\n");
        if (board[position + 7] == TARGET_PLAYER)
        {
            int i = position + 14;
            while (1)
            {
                if (i >= 64)
                {
                    break;
                }
                if (i % 8 == 7)
                {
                    break;
                }
                if (board[i] == TARGET_PLAYER)
                {
                    i += 7;
                    continue;
                }
                if (board[i] == EMPTY)
                {
                    speicher[index++] = i;
                    printf("found move L:%d\n", speicher[index - 1]);
                    break;
                }
                if (board[i] == MY_PLAYER)
                {
                    break;
                }
            }
        }
    }

    speicher[index] = LAST_MOVE;
    printf("ende oneposition\n");
    return speicher;
}

// todo, optional, currently complexity of O(n^3), can be made to have complexity of O(n)
int *removeDuplicates(MOVES speicher, int index)
{
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = i + 1; j < index;)
        {
            if (speicher[i] == speicher[j])
            {
                for (int k = j; k < index - 1; k++)
                {
                    speicher[k] = speicher[k + 1];
                }
                index--;
            }
            else
            {
                j++;
            }
        }
    }
    speicher[index] = LAST_MOVE;
    return speicher;
}
//todo board can be more than 8x8 !!!!

MOVES getLegalMovesAllPositions(BOARD board, SIDE_TO_MOVE TARGET_PLAYER, MOVES allMoves)
{
    //MOVES allMoves= malloc(64 * sizeof(int)); // todo, clean up memory
    MOVES speicher = malloc(64 * sizeof(int));
    SIDE_TO_MOVE me = 3 - TARGET_PLAYER;
    int index = 0;
    for (int pos = 0; pos < 64; pos++)
    {
        //printf("iii\n");
        if (board[pos] == me)
        {
            MOVES legalMovesFromHere = getLegalMovesOnePosition(board, speicher, pos, TARGET_PLAYER);
            int j = 0;
            while (1)
            {
                if (legalMovesFromHere[j] == LAST_MOVE)
                {
                    break;
                }
                allMoves[index++] = legalMovesFromHere[j++];
            }
        }
    }
    printf("index von allMove(): %d\n", index);
    removeDuplicates(allMoves, index);
    free(speicher);
    printf("ende allmove()\n");
    return allMoves;
}

int getTotalNumberOfLegalMoves(BOARD board, SIDE_TO_MOVE TARGET_PLAYER)
{
    MOVES allMoves = malloc(64 * sizeof(int));
    MOVES finalspeicher = getLegalMovesAllPositions(board, TARGET_PLAYER, allMoves);
    int total = 0;

    for (int i = 0; i < 64; i++)
    {
        if (finalspeicher[i] == LAST_MOVE)
        {
            printf("total fertig\n");
            return total;
        }
        total++;
    }
    printf("did not find a LAST_MOVE... are you sure you did not make a mistake\n");
    exit(1);
}
