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


#define MOVE int
#define SIDE_TO_MOVE int
#define BOARD int*
#define MOVES int*

#define BLACK 2
#define WHITE 1

#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35

#define STARTING_PLAYER BLACK
#define SWITCH_PLAYER_CONSTANT 3


// if thinker is parent, retry logic may be easier to implement
// including learning

int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");

    // todo, this is just an idea, it depends on how we do shm (shared memory)
    // we will use two separate boards. One for connector that we will update with info from server
    // one to be used internally by thinker. When connector receives update, we copy connector board into thinker board
    BOARD connectorBoard = malloc(64 * sizeof(int));
    BOARD thinkerBoard = malloc(64 * sizeof(int));

   //thinkerMasterMethod(thinkerBoard);
    connectorMasterMethod(connectorBoard, thinkerBoard, argc,argv);

    return 0;
}
