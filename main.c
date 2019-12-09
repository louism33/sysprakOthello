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
#include "thinker/thinkertests/boardtests2.h"
#include "connector/connectorTests/connectortests.h"
#include "thinker/thinkertests/unmakemovetests.h"
#include "thinker/thinkertests/makemovetests.h"
#include "thinker/thinkertests/perft.h"
#include "thinker/thinkertests/biggerboardtest.h"
#include "ki/kitests/testkisimple.h"
#include "ki/kitests/testkibasicthinking.h"
#include "ki/kitests/testkibasicstrategy.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "perft") == 0) {
        if (argc == 2) {
            printf("Please specify depth\n");
            exit(1);
        }
        int depth = atoi(argv[2]);
        fromCommandLine(depth);
        exit(0);
    }

    if (argc > 1 && strcmp(argv[1], "TEST") == 0) {
        printf("Test begin:.........\n");

        int fail = 0;

        printf("Running fullTestSuite\n");
        fail += fullTestSuite();

        printf("Running fullTestSuiteBoard2\n");
        fail += fullTestSuiteBoard2();

        printf("Running convert move test Suite\n");
        fail += testConvertMove();

        printf("Running make move test Suite\n");
        fail += runMakeMoveTests();

        printf("Running unmake move test Suite\n");
        fail += fullTestSuiteUnmakeMoveTests();

        printf("Running big board tests Suite\n");
        fail += testSuiteBigBoard();

        printf("Running perft Suite\n");
        fail += perftSuite();

        printf("Running basic KI Suite\n");
        fail += kiTestsSimple();

        printf("Running medium KI Suite\n");
        fail += kiTestsBasicThinking();

        printf("Running strategy KI Suite\n");
        fail += kiTestsBasicStrategy();

        if (fail) {// fail/=0 dann läuft if Bedingung
            printf("Some tests failed, please fix them as soon as possible.\n");
            exit(1);
        }

        printf("Tested. All good.\n");
        return 0;
    }

    BOARD_STRUCT *connectorBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(connectorBoard);

    BOARD_STRUCT *thinkerBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(thinkerBoard);

    thinkerMasterMethod(thinkerBoard);
    connectorMasterMethod(connectorBoard, thinkerBoard, argc, argv);

    freeBoardStruct(connectorBoard);
    freeBoardStruct(thinkerBoard);

    return 0;
}
