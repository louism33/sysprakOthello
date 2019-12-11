#include <stdio.h>
#include <stdlb.h>



int pipetest1(){
char buff[]=
"+ 1 "White" player 0
+ ENDPLAYERS
+ MOVE 3000
+ FIELD 8,8
+ 8 * * * * * * * *
+ 7 * * * * * * * *
+ 6 * * * * * * * *
+ 5 * * * W B * * *
+ 4 * * * B W * * *
+ 3 * * * * * * * *
+ 2 * * * * * * * *
+ 1 * * * * * * * *
+ ENDFIELD";
return 0;

}


int pipetest(){
     pipetest1();
}