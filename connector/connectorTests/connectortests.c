#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../thinker/board.h"
#include "../performConnection.h"

int testConvertMove()
{   
    //char *test=malloc(sizeof(char)*10);
    
    char *test=convertMove(0);
    printf("Test of converMove(0): %s\n",test);
    
    
    // if (strcmp(test,"A8") != 0)
    // {
    //     printf("there is a problem in convertMove\n");
    //     exit(1);
    // }
    return 0;
}