#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connector/connector.h"
#include "thinker/thinker.h"
#include "connector/config.h"

#include "connector/boardmessageparser.h"

// if thinker is parent, retry logic may be easier to implement
// including learning
int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");


    /*
+ TOTAL 2
+ 0 IAMLOUIS 0
+ ENDPLAYERS
+ MOVE 3000
+ FIELD 8,8
+ 8 * * * * * * * *
+ 7 * * * * * B B B
+ 6 * * * * * W * *
+ 5 * * W W W B * *
+ 4 * B B B B * * *
+ 3 * * W * * * * *
+ 2 * * * * * * * *
+ 1 * * * * * * * *
+ ENDFIELD
     */

    char *exampleBoardMessage = "+ TOTAL 2\n"
                                "+ 0 IAMLOUIS 0\n"
                                "+ ENDPLAYERS\n"
                                "+ MOVE 3000\n"
                                "+ FIELD 8,8\n"
                                "+ 8 * * * * * * * *\n"
                                "+ 7 * * * * * B B B\n"
                                "+ 6 * * * * * W * *\n"
                                "+ 5 * * W W W B * *\n"
                                "+ 4 * B B B B * * *\n"
                                "+ 3 * * W * * * * *\n"
                                "+ 2 * * * * * * * *\n"
                                "+ 1 * * * * * * * *\n"
                                "+ ENDFIELD";


    moveTimeAndBoard* moveTimeAndBoard = parseBoardMessage(exampleBoardMessage);

//    thinkerMasterMethod();
//    connectorMasterMethod(argc,argv);

    return 0;
}
