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

int testgetMovetimeandFieldsize()
{
    testgetMovetimeandFieldsize1();
    testgetMovetimeandFieldsize2();
    testgetMovetimeandFieldsize3();
    return 0;
}

int testgetMovetimeandFieldsize1()
{
    int fail = 0;
    char *board1 = "TOTAL 2\n"
                   "+ 0 IAMLOUIS 0\n"
                   "+ ENDPLAYERS\n"
                   "+ MOVE 3000\n"
                   "+ FIELD 8,8\n"
                   "+ 8 * * * * * * * *\n"
                   "+ 7 * * * * * * * *\n"
                   "+ 6 * * * * * * * *\n"
                   "+ 5 * * * B W * * *\n"
                   "+ 4 * * * W B * * *\n"
                   "+ 3 * * * * * * * *\n"
                   "+ 2 * * * * * * * *\n"
                   "+ 1 * * * * * * * *\n"
                   "+ ENDFIELD\n";

    char *moveTime = malloc(4 * sizeof(char));
    char *fieldSize = malloc(3 * sizeof(char));
    int test8 = getMovetimeandFieldsize(board1, moveTime, fieldSize);

    if (test8 != 3000)
    {
        fail = 1;
    }

    if (strcmp(fieldSize, "8,8") != 0)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim dealWithboardOverCommandhannah().\n");
        exit(1);
    }
    printf("alles klar beim dealWithboardOverCommandhannah().\n");
    return 0;
}

int testgetMovetimeandFieldsize2()
{
    int fail = 0;
    char *board2 = "TOTAL 2\n"
                   "+ 0 IAMLOUIS 0\n"
                   "+ ENDPLAYERS\n"
                   "+ MOVE 4353\n"
                   "+ FIELD 1,6\n"
                   "+ 8 * * * * * * * *\n"
                   "+ 7 * * * * * * * *\n"
                   "+ 6 * * * * * * * *\n"
                   "+ 5 * * * B W * * *\n"
                   "+ 4 * * * W B * * *\n"
                   "+ 3 * * * * * * * *\n"
                   "+ 2 * * * * * * * *\n"
                   "+ 1 * * * * * * * *\n"
                   "+ ENDFIELD\n";

    char *moveTime = malloc(4 * sizeof(char));
    char *fieldSize = malloc(3 * sizeof(char));
    int test9 = getMovetimeandFieldsize(board2, moveTime, fieldSize);

    if (test9 != 4353)
    {
        fail = 1;
    }

    if (strcmp(fieldSize, "1,6") != 0)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim dealWithboardOverCommandhannah().\n");
        exit(1);
    }
    printf("alles klar beim dealWithboardOverCommandhannah().\n");
    return 0;
}

int testgetMovetimeandFieldsize3()
{
    int fail = 0;
    char *board3 = "TOTAL 2\n"
                   "+ 0 IAMLOUIS 0\n"
                   "+ ENDPLAYERS\n"
                   "+ MOVE 10000\n"
                   "+ FIELD 100,100\n"
                   "+ 8 * * * * * * * *\n"
                   "+ 7 * * * * * * * *\n"
                   "+ 6 * * * * * * * *\n"
                   "+ 5 * * * B W * * *\n"
                   "+ 4 * * * W B * * *\n"
                   "+ 3 * * * * * * * *\n"
                   "+ 2 * * * * * * * *\n"
                   "+ 1 * * * * * * * *\n"
                   "+ ENDFIELD\n";

    char *moveTime = malloc(4 * sizeof(char));
    char *fieldSize = malloc(3 * sizeof(char));
    int test10 = getMovetimeandFieldsize(board3, moveTime, fieldSize);

    if (test10 != 10000)
    {
        fail = 1;
    }

    if (strcmp(fieldSize, "100,100") != 0)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim dealWithboardOverCommandhannah().\n");
        exit(1);
    }
    printf("alles klar beim dealWithboardOverCommandhannah().\n");
    return 0;
}

int testcharInNummer()
{
    testcharInNummer1();
    testcharInNummer2();
    testcharInNummer3();
    testcharInNummer4();
    testcharInNummer5();
    testcharInNummer6();
    testcharInNummer7();
    testcharInNummer8();
    return 0;
}

int testcharInNummer1()
{
    int fail = 0;

    struct fieldSizeNummer1and2 fieldsize = charInNummer("8,8");

    if (fieldsize.Nummer1 != 8)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 8)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");
    return 0;
}

int testcharInNummer2()
{
    int fail = 0;

    struct fieldSizeNummer1and2 fieldsize = charInNummer("9,9");

    if (fieldsize.Nummer1 != 9)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 9)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");
    return 0;
}

int testcharInNummer3()
{
    int fail = 0;

    struct fieldSizeNummer1and2 fieldsize = charInNummer("2,5");

    if (fieldsize.Nummer1 != 2)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 5)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");
    return 0;
}

int testcharInNummer4()
{
    int fail = 0;
    struct fieldSizeNummer1and2 fieldsize = charInNummer("12,12");

    if (fieldsize.Nummer1 != 12)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 12)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");

    return 0;
}

int testcharInNummer5()
{
    int fail = 0;
    struct fieldSizeNummer1and2 fieldsize = charInNummer("HalloWelt");

    if (fieldsize.Nummer1 != 0)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 0)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");

    return 0;
}

int testcharInNummer6()
{
    int fail = 0;
    struct fieldSizeNummer1and2 fieldsize = charInNummer("122,132");

    if (fieldsize.Nummer1 != 122)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 132)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");

    return 0;
}

int testcharInNummer7()
{
    int fail = 0;
    struct fieldSizeNummer1and2 fieldsize = charInNummer("7");

    if (fieldsize.Nummer1 != 0)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 0)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");

    return 0;
}

int testcharInNummer8()
{
    int fail = 0;
    struct fieldSizeNummer1and2 fieldsize = charInNummer("14,-1");

    if (fieldsize.Nummer1 != 0)
    {
        fail = 1;
    }

    if (fieldsize.Nummer2 != 0)
    {
        fail = 1;
    }

    if (fail)
    {
        printf("Problem beim testcharInNummer().\n");
        exit(1);
    }
    printf("alles klar beim testcharInNummer().\n");

    return 0;
}
