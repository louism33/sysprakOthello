//int i,j;
/* char board[8][8] = {{'A','B','C','D','E','F','G','H'},
                    {'.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.'}}; */

/* void try1(){
    for(i = 0; i < 8; i++){
    for(j = 0; j < 8;j++){
        printf("%c ",board[i][j]);
        }
    printf("\n");
    }
}
void try2(){
    int x,y;
    scanf("%d %d",&i,&j);
    if(board[x][y]!= '.')
        printf("NO \n");
    else{
        board[x][y] = '0';
    }
    printf("%c ",board[i][j]);
}*/

/* void printBoard(){
    int g = 1;
    printf("    A B C D E F G H \n");
    printf("  +-----------------+ \n");
    for(i = 0; i < 8; i++){
        printf("%d | ",g);
        for(j = 0; j < 8; j++){
            board[i][j] = 0;
            printf(". ");
        }
        printf("| %d",g);
        g++;
        printf("\n");
    }
    printf("  +-----------------+ \n");
    printf("    A B C D E F G H \n");
    
} 

void playchess(){
    int x,y;
    scanf("%d %d",&x,&y);
    if(board[x][y]!= '.')
        printf("NO\n");
    else{
        board[x][y] = '0';
    }
}
*/
