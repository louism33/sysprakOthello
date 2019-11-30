//
// Created by louis on 11/30/19.
//

#include <stdlib.h>

#include <stdio.h>
#include "makemovetests.h"
#include "../board.h"
#include "../thinker.h"
#include "../../connector/boardmessageparser.h"


int testEasyLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[19] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();

    makeMove(b, 20);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();

    // (boardTest);
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyRightBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = getBlack();
    board[36] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    
    makeMove(b, 18);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[27] = getWhite();
    boardTest[36] = getWhite();
    boardTest[18] = getWhite();

    // (boardTest);
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyLeftBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[35] = getBlack();
    board[42] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 28);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[28] = getWhite();
    boardTest[35] = getWhite();
    boardTest[42] = getWhite();

    // (boardTest);
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyTopLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = getWhite();
    board[36] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 45);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[27] = getWhite();
    boardTest[36] = getWhite();
    boardTest[45] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyTopRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[28] = getWhite();
    board[35] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //   
    (board);
    makeMove(b, 42);
    (board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[28] = getWhite();
    boardTest[35] = getWhite();
    boardTest[42] = getWhite();

    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getBlack();
    board[19] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 17);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[17] = getWhite();
    boardTest[18] = getWhite();
    boardTest[19] = getWhite();

    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[29] = getWhite();
    board[37] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 45);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[29] = getWhite();
    boardTest[37] = getWhite();
    boardTest[45] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = getBlack();
    board[29] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 13);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[13] = getWhite();
    boardTest[21] = getWhite();
    boardTest[29] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyRightLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[19] = getBlack();
    board[21] = getBlack();
    board[22] = getWhite();


    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 20);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();
    boardTest[21] = getWhite();
    boardTest[22] = getWhite();

    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyRightLeftTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[19] = getBlack();
    board[21] = getBlack();
    board[22] = getWhite();
    board[12] = getBlack();


    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 20);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();
    boardTest[21] = getWhite();
    boardTest[22] = getWhite();
    boardTest[12] = getBlack();


    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasy2Left() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[17] = getWhite();
    board[18] = getBlack();
    board[19] = getBlack();


    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 20);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[17] = getWhite();
    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasy2Right() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = getBlack();
    board[20] = getBlack();
    board[21] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 18);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();
    boardTest[21] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasy3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[19] = getBlack();
    board[20] = getBlack();
    board[21] = getBlack();


    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 22);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();
    boardTest[21] = getWhite();
    boardTest[22] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasy3Top() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = getWhite();
    board[29] = getBlack();
    board[37] = getBlack();
    board[45] = getBlack();


    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 53);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[21] = getWhite();
    boardTest[29] = getWhite();
    boardTest[37] = getWhite();
    boardTest[45] = getWhite();
    boardTest[53] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasy4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = getWhite();
    board[19] = getBlack();
    board[20] = getBlack();
    board[21] = getBlack();
    board[22] = getBlack();


    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 23);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = getWhite();
    boardTest[19] = getWhite();
    boardTest[20] = getWhite();
    boardTest[21] = getWhite();
    boardTest[22] = getWhite();
    boardTest[23] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyMAX() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[32] = getWhite();
    board[33] = getWhite();
    board[34] = getBlack();
    board[35] = getBlack();
    board[36] = getBlack();
    board[37] = getBlack();
    board[38] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 39);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[32] = getWhite();
    boardTest[33] = getWhite();
    boardTest[34] = getWhite();
    boardTest[35] = getWhite();
    boardTest[36] = getWhite();
    boardTest[37] = getWhite();
    boardTest[38] = getWhite();
    boardTest[39] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int testEasyMAXTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[5] = getWhite();
    board[13] = getWhite();
    board[21] = getBlack();
    board[29] = getBlack();
    board[37] = getBlack();
    board[45] = getBlack();
    board[53] = getBlack();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 61);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[5] = getWhite();
    boardTest[13] = getWhite();
    boardTest[21] = getWhite();
    boardTest[29] = getWhite();
    boardTest[37] = getWhite();
    boardTest[45] = getWhite();
    boardTest[53] = getWhite();
    boardTest[61] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}


int testEasyMAXRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[33] = getBlack();
    board[34] = getBlack();
    board[35] = getBlack();
    board[36] = getBlack();
    board[37] = getBlack();
    board[38] = getBlack();
    board[39] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 32);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[32] = getWhite();
    boardTest[33] = getWhite();
    boardTest[34] = getWhite();
    boardTest[35] = getWhite();
    boardTest[36] = getWhite();
    boardTest[37] = getWhite();
    boardTest[38] = getWhite();
    boardTest[39] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success

}

int testEasyMAXBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[13] = getBlack();
    board[21] = getBlack();
    board[29] = getBlack();
    board[37] = getBlack();
    board[45] = getBlack();
    board[53] = getBlack();
    board[61] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    
    makeMove(b, 5);
    

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[13] = getWhite();
    boardTest[21] = getWhite();
    boardTest[29] = getWhite();
    boardTest[37] = getWhite();
    boardTest[45] = getWhite();
    boardTest[53] = getWhite();
    boardTest[61] = getWhite();
    boardTest[5] = getWhite();

    
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}

int crazyTest() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[12] = getWhite();
    board[20] = getBlack();
    board[36] = getBlack();
    board[27] = getBlack();
    board[21] = getBlack();
    board[14] = getWhite();
    board[29] = getBlack();
    board[26] = getWhite();
    board[44] = getWhite();
    board[30] = getWhite();

    SIDE_TO_MOVE player = getWhite();
    b->sideToMove = getWhite();
    SIDE_TO_MOVE targetPlayer = getBlack();
    //    
    (board);
    makeMove(b, 28);
    (board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[12] = getWhite();
    boardTest[20] = getWhite();
    boardTest[21] = getWhite();
    boardTest[14] = getWhite();
    boardTest[36] = getWhite();
    boardTest[27] = getWhite();
    boardTest[29] = getWhite();
    boardTest[26] = getWhite();
    boardTest[44] = getWhite();
    boardTest[30] = getWhite();
    boardTest[28] = getWhite();

    (boardTest);
    for (int i = 0; i < 64; i++) {
        if (boardTest[i] != board[i]) {
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    
    return 0; // success
}


int runMakeMoveTests() {
    testEasyLeft();
    testEasy2Left();
    testEasy3();
    testEasy4();
    testEasyMAX();
    testEasyRight();
    testEasy2Right();
    testEasyMAXRight();
    testEasyRightLeft();
    testEasyTop();
    testEasy3Top();
    testEasyMAXTop();
    testEasyRightLeftTop();
    testEasyBottom();
    testEasyMAXBottom();
    crazyTest();
    testEasyTopRight();
    testEasyTopLeft();
    testEasyLeftBottom();
    testEasyRightBottom();


    return 0;
}

