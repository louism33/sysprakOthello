#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../thinker/board.h"
#include "../performConnection.h"

int testConvertMove() {
    int fail = 0;

    char *test1 = malloc(10 * sizeof(char));
    convertMove(45, test1);
    if (strcmp(test1, "F3") != 0) {
        fail = 1;
    }
    free(test1);

    char *test2 = malloc(10 * sizeof(char));
    convertMove(34, test2);
    if (strcmp(test2, "C4") != 0) {
        fail = 1;
    }
    free(test2);

    char *test3 = malloc(10 * sizeof(char));
    convertMove(63, test3);
    if (strcmp(test3, "H1") != 0) {
        fail = 1;
    }
    free(test3);

    char *test4 = malloc(10 * sizeof(char));
    convertMove(0, test4);
    if (strcmp(test4, "A8") != 0) {
        fail = 1;
    }
    free(test4);

    char *test5 = malloc(10 * sizeof(char));
    convertMove(56, test5);
    if (strcmp(test5, "A1") != 0) {
        fail = 1;
    }
    free(test5);

    char *test6 = malloc(10 * sizeof(char));
    convertMove(12, test6);
    if (strcmp(test6, "E7") != 0) {
        fail = 1;
    }
    free(test6);

    char *test7 = malloc(10 * sizeof(char));
    convertMove(27, test7);
    if (strcmp(test7, "D5") != 0) {
        fail = 1;
    }
    free(test7);

    if (fail) {
        printf("Problem beim convertMove().\n");
        exit(1);
    }
    printf("alles klar beim convertMove()\n");
    return 0;
}


int testgetMoveTimeAndFieldSize1() {
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

    char *moveTime = malloc(10 * sizeof(char));
    char *fieldSize = malloc(10 * sizeof(char));
    int test8 = getMoveTimeAndFieldSize(board1, moveTime, fieldSize);

    if (test8 != 3000) {
        fail = 1;
    }

    if (strcmp(fieldSize, "8,8") != 0) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim getMoveTimeAndFieldSize 1.\n");
    }

    free(moveTime);
    free(fieldSize);
    return fail;
}

int testgetMoveTimeAndFieldSize2() {
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

    char *moveTime = malloc(10 * sizeof(char));
    char *fieldSize = malloc(10 * sizeof(char));
    int test9 = getMoveTimeAndFieldSize(board2, moveTime, fieldSize);

    if (test9 != 4353) {
        fail = 1;
    }

    if (strcmp(fieldSize, "1,6") != 0) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim getMoveTimeAndFieldSize 2.\n");
    }
    free(moveTime);
    free(fieldSize);
    return fail;
}

int testgetMoveTimeAndFieldSize3() {
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

    char *moveTime = malloc(10 * sizeof(char));
    char *fieldSize = malloc(10 * sizeof(char));
    int test10 = getMoveTimeAndFieldSize(board3, moveTime, fieldSize);

    if (test10 != 10000) {
        fail = 1;
    }

    if (strcmp(fieldSize, "100,100") != 0) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim getMoveTimeAndFieldSize 3.\n");
        exit(1);
    }
    free(moveTime);
    free(fieldSize);
    return fail;
}

int testCharInrow() {
    int fail = 0;

    struct FieldSizeColumnAndRow fieldsize = charInNummer("8,8");

    if (fieldsize.row != 8) {
        fail = 1;
    }

    if (fieldsize.col != 8) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 1.\n");
    }
    return fail;
}

int testCharIncol() {
    int fail = 0;

    struct FieldSizeColumnAndRow fieldsize = charInNummer("9,9");

    if (fieldsize.row != 9) {
        fail = 1;
    }

    if (fieldsize.col != 9) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 2.\n");
    }
    return fail;
}

int testCharInNummer3() {
    int fail = 0;

    struct FieldSizeColumnAndRow fieldsize = charInNummer("2,5");

    if (fieldsize.row != 2) {
        fail = 1;
    }

    if (fieldsize.col != 5) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 3.\n");
    }
    return fail;
}

int testCharInNummer4() {
    int fail = 0;
    struct FieldSizeColumnAndRow fieldsize = charInNummer("12,12");

    if (fieldsize.row != 12) {
        fail = 1;
    }

    if (fieldsize.col != 12) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 4.\n");
    }

    return fail;
}

int testCharInNummer5() {
    int fail = 0;
    struct FieldSizeColumnAndRow fieldsize = charInNummer("HalloWelt");

    if (fieldsize.row != 0) {
        fail = 1;
    }

    if (fieldsize.col != 0) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 5.\n");
    }

    return fail;
}

int testCharInNummer6() {
    int fail = 0;
    struct FieldSizeColumnAndRow fieldsize = charInNummer("122,132");

    if (fieldsize.row != 122) {
        fail = 1;
    }

    if (fieldsize.col != 132) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 6.\n");
    }

    return fail;
}

int testCharInNummer7() {
    int fail = 0;
    struct FieldSizeColumnAndRow fieldsize = charInNummer("7");

    if (fieldsize.row != 0) {
        fail = 1;
    }

    if (fieldsize.col != 0) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 7.\n");
    }

    return fail;
}

int testCharInNummer8() {
    int fail = 0;
    struct FieldSizeColumnAndRow fieldsize = charInNummer("14,-1");

    if (fieldsize.row != 0) {
        fail = 1;
    }

    if (fieldsize.col != 0) {
        fail = 1;
    }

    if (fail) {
        printf("Problem beim charInNummer 8.\n");
    }

    return fail;
}

int testGetMovetimeAndFieldSize() {
    int fail = 0;
    fail += testgetMoveTimeAndFieldSize1();
    fail += testgetMoveTimeAndFieldSize2();
    fail += testgetMoveTimeAndFieldSize3();
    return fail;
}

int testCharInNummer() {
    int fail = 0;
    fail += testCharInrow();
    fail += testCharIncol();
    fail += testCharInNummer3();
    fail += testCharInNummer4();
    fail += testCharInNummer5();
    fail += testCharInNummer6();
    fail += testCharInNummer7();
    fail += testCharInNummer8();
    return fail;
}