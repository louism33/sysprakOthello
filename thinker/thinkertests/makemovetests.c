int testEasyLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;

   // printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRightBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = BLACK;
    board[36] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,18,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[27] = WHITE;
    boardTest[36] = WHITE;
    boardTest[18] = WHITE;

   // printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyLeftBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[35] = BLACK;
    board[42] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,28,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[28] = WHITE;
    boardTest[35] = WHITE;
    boardTest[42] = WHITE;

   // printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyTopLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[27] = WHITE;
    board[36] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,45,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[27] = WHITE;
    boardTest[36] = WHITE;
    boardTest[45] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyTopRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[28] = WHITE;
    board[35] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //   printBoardLouisSide(board, player);
    printBoard(board);
    makeMove(board,42,targetPlayer);
    printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[28] = WHITE;
    boardTest[35] = WHITE;
    boardTest[42] = WHITE;

    printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = BLACK;
    board[19] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,17,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[17] = WHITE;
    boardTest[18] = WHITE;
    boardTest[19] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[29] = WHITE;
    board[37] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,45,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = BLACK;
    board[29] = WHITE;
    
    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,13,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[13] = WHITE;
    boardTest[21] = WHITE;
    boardTest[29] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRightLeft() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[21] = BLACK;
    board[22] = WHITE;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;


    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyRightLeftTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[21] = BLACK;
    board[22] = WHITE;
    board[12] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;
    boardTest[12] = BLACK;


    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy2Left() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[17] = WHITE;
    board[18] = BLACK;
    board[19] = BLACK;
    

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,20,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[17] = WHITE;
    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy2Right() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[19] = BLACK;
    board[20] = BLACK;
    board[21] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,18,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy3() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[20] = BLACK;
    board[21] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,22,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy3Top() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[21] = WHITE;
    board[29] = BLACK;
    board[37] = BLACK;
    board[45] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,53,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[21] = WHITE;
    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;
    boardTest[53] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasy4() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[18] = WHITE;
    board[19] = BLACK;
    board[20] = BLACK;
    board[21] = BLACK;
    board[22] = BLACK;


    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,23,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[18] = WHITE;
    boardTest[19] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[22] = WHITE;
    boardTest[23] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyMAX() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[32] = WHITE;
    board[33] = WHITE;
    board[34] = BLACK;
    board[35] = BLACK;
    board[36] = BLACK;
    board[37] = BLACK;
    board[38] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,39,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[32] = WHITE;
    boardTest[33] = WHITE;
    boardTest[34] = WHITE;
    boardTest[35] = WHITE;
    boardTest[36] = WHITE;
    boardTest[37] = WHITE;
    boardTest[38] = WHITE;
    boardTest[39] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int testEasyMAXTop() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[5] = WHITE;
    board[13] = WHITE;
    board[21] = BLACK;
    board[29] = BLACK;
    board[37] = BLACK;
    board[45] = BLACK;
    board[53] = BLACK;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,61,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[5] = WHITE;
    boardTest[13] = WHITE;
    boardTest[21] = WHITE;
    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;
    boardTest[53] = WHITE;
    boardTest[61] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}


int testEasyMAXRight() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[33] = BLACK;
    board[34] = BLACK;
    board[35] = BLACK;
    board[36] = BLACK;
    board[37] = BLACK;
    board[38] = BLACK;
    board[39] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,32,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[32] = WHITE;
    boardTest[33] = WHITE;
    boardTest[34] = WHITE;
    boardTest[35] = WHITE;
    boardTest[36] = WHITE;
    boardTest[37] = WHITE;
    boardTest[38] = WHITE;
    boardTest[39] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success

}

int testEasyMAXBottom() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[13] = BLACK;
    board[21] = BLACK;
    board[29] = BLACK;
    board[37] = BLACK;
    board[45] = BLACK;
    board[53] = BLACK;
    board[61] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    //printBoard(board);
    makeMove(board,5,targetPlayer);
    //printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[13] = WHITE;
    boardTest[21] = WHITE;
    boardTest[29] = WHITE;
    boardTest[37] = WHITE;
    boardTest[45] = WHITE;
    boardTest[53] = WHITE;
    boardTest[61] = WHITE;
    boardTest[5] = WHITE;

    //printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int crazyTest() {
    BOARD_STRUCT *b = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b);
    int *board = b->board;

    board[12] = WHITE;
    board[20] = BLACK;
    board[36] = BLACK;
    board[27] = BLACK;
    board[21] = BLACK;
    board[14] = WHITE;
    board[29] = BLACK;
    board[26] = WHITE;
    board[44] = WHITE;
    board[30] = WHITE;

    SIDE_TO_MOVE player = WHITE;
    SIDE_TO_MOVE targetPlayer = BLACK;
    //    printBoardLouisSide(board, player);
    printBoard(board);
    makeMove(board,28,targetPlayer);
    printBoard(board);

    BOARD_STRUCT *b2 = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToZero(b2);
    int *boardTest = b2->board;

    boardTest[12] = WHITE;
    boardTest[20] = WHITE;
    boardTest[21] = WHITE;
    boardTest[14] = WHITE;
    boardTest[36] = WHITE;
    boardTest[27] = WHITE;
    boardTest[29] = WHITE;
    boardTest[26] = WHITE;
    boardTest[44] = WHITE;
    boardTest[30] = WHITE;
    boardTest[28] = WHITE;

    printBoard(boardTest);
    for(int i=0; i<64; i++) {
        if(boardTest[i] != board[i]){
            //printBoardLouisSide(b, player);
            fprintf(stderr, "FAILED A BOARD TEST! Du kannst da  nicht hin\n");
            free(b2);
            free(b);
            exit(1);
        }
    }

    free(b);
    free(b2);
    printf("success!\n");
    return 0; // success
}

int main(){
    /*testEasyLeft();
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
    testEasyMAXBottom();*/
    crazyTest();
    testEasyTopRight();
    testEasyTopLeft();
    testEasyLeftBottom();
    testEasyRightBottom();

    
    return 0;
}


