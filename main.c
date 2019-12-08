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
#include <sys/types.h>
#include <signal.h>
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
#include "shm/shm.h"
#include "pipe/pipe.h"
#include "main.h"

// if thinker is parent, retry logic may be easier to implement
// including learning
void mysighandler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("SIGUSR1 empfangen\n");
    }
}

int main(int argc, char *argv[])
{
    infoVonServer *info = malloc(sizeof(infoVonServer));
    printf("Hello World! I am Alex. This is the main method\n");
    //Test-block
    if (argc > 1 && strcmp(argv[1], "perft") == 0)
    {
        if (argc == 2)
        {
            printf("Please specify depth\n");
            exit(1);
        }
        int depth = atoi(argv[2]);
        fromCommandLine(depth);
        exit(0);
    }

    if (argc > 1 && strcmp(argv[1], "TEST") == 0)
    {
        printf("Test begin:.........\n");
        printf("Running board test Suite\n");

        int fail = 0;

        fail += fullTestSuite();

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

        if (fail)
        { // fail/=0 dann läuft if Bedingung
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

    createShm();
    attachShm();
    createPipe(pd);

    /*signal empfagen und behandeln -> thinkMasterMethod() aufrufen */
    if (SIG_ERR == signal(SIGUSR1, mysighandler))
    {
        printf("error bei empfangen des Signals\n");
    }
    else
    {
        thinkerMasterMethod(thinkerBoard);
        printf("Ich denke jetzt ------------------------------------\n");
    }

    switch (thinker = fork())
    {
        /*Fehlerfall*/
    case -1:
        printf("Fehler bei fork()\n");
        break;

        /*Kindsprozess = Connector*/
    case 0:
        printf("Im Kindsprozess\n");
        connector = getpid();
        thinker = getppid();
        printf("ConnectorPID = %i\n", connector);

        connectorMasterMethod(connectorBoard, thinkerBoard, argc, argv, info, thinker, connector);
        printf("info: %s\n", info->gameId);
        close(pd[1]);
        /* read pipe*/

        break;

    /*Elternprozess = Thinker*/
    default:
        sleep(5);
        printf("Im Elternprozess\n");
        thinker = getpid();
        printf("ThinkerPID = %i\n", thinker);
        close(pd[1]);
        /*write pipe*/

        break;
    }

    deleteShm();
    freeBoardStruct(connectorBoard);
    freeBoardStruct(thinkerBoard);
    free(info);
    return 0;
}