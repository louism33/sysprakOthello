#include <stdio.h>
#include <stdlib.h>
#include "../performConnection.h"


int testConvertMove(){
    if(convertMove(0) !="A8"){
        printf("there is a problem in convertMove");
        exit(1);
    }
    return 0;
}