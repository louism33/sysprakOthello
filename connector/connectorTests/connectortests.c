#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../thinker/board.h"
#include "../performConnection.h"

int testConvertMove()
{
    int fail = 0;

    char *test1 = malloc(10 * sizeof(char));
    convertMove(45, test1);
    if (strcmp(test1, "F3") != 0)
    {
        fail = 1;
    }
    free(test1);

    char *test2 = malloc(10 * sizeof(char));
    convertMove(34, test2);
    if (strcmp(test2, "C4") != 0)
    {
        fail = 1;
    }
    free(test2);

    char *test3 = malloc(10 * sizeof(char));
    convertMove(63, test3);
    if (strcmp(test3, "H1") != 0)
    {
        fail = 1;
    }
    free(test3);

    char *test4 = malloc(10 * sizeof(char));
    convertMove(0, test4);
    if (strcmp(test4, "A8") != 0)
    {
        fail = 1;
    }
    free(test4);

    char *test5 = malloc(10 * sizeof(char));
    convertMove(56, test5);
    if (strcmp(test5, "A1") != 0)
    {
        fail = 1;
    }
    free(test5);

    char *test6 = malloc(10 * sizeof(char));
    convertMove(12, test6);
    if (strcmp(test6, "E7") != 0)
    {
        fail = 1;
    }
    free(test6);

    char *test7 = malloc(10 * sizeof(char));
    convertMove(27, test7);
    if (strcmp(test7, "D5") != 0)
    {
        fail = 1;
    }
    free(test7);

    if (fail)
    {
        printf("Problem beim convertMove().\n");
        exit(1);
    }
    printf("alles klar beim convertMove()\n");
    return 0;
}