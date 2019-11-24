#include <stdio.h>
#include <stdlib.h>


int testConvertMove(){
    if(ConvertMove(0)!="A8"){
        printf("there is a problem in convertMove");
        exit(1);
    }
    return 0;
}