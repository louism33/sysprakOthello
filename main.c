#include "thinker/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "connector/connector.h"
#include "thinker/thinker.h"
#include "connector/config.h"
#include "connector/boardmessageparser.h"
#include "thinker/thinkertests/boardtests.h"
#include "connector/connectorTests/connectortests.h"


// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0

// black makes first move
#define STARTING_PLAYER BLACK

// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)

// 4 square occupied in starting board
#define STARTING_WHITE_POSITION_1 27
#define STARTING_WHITE_POSITION_2 36
#define STARTING_BLACK_POSITION_1 28
#define STARTING_BLACK_POSITION_2 35


// if thinker is parent, retry logic may be easier to implement
// including learning

int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");

    if (argc > 1 && strcmp(argv[1], "TEST") == 0) {
        printf("Test begin:.........\n");
        printf("Running board test Suite\n");
        int fail = fullTestSuite();

        fail += testConvertMove();

        if (fail) {
            printf("Some tests failed, please fix them as soon as possible.\n");
            exit(1);
        }
        printf("Tested. All good.\n");
        return 0;
    }



    // todo, this is just an idea, it depends on how we do shm (shared memory)
    // we will use two separate boards. One for connector that we will update with info from server
    // one to be used internally by thinker. When connector receives update, we copy connector board into thinker board

    BOARD_STRUCT *connectorBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(connectorBoard);

    BOARD_STRUCT *thinkerBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(thinkerBoard);



    //thinkerMasterMethod(thinkerBoard);
    connectorMasterMethod(connectorBoard, thinkerBoard, argc, argv);


    freeBoardStruct(connectorBoard);
    freeBoardStruct(thinkerBoard);

    return 0;
}
