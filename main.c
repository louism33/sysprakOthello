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

#include "connector/connectorTests/connectortests.h"
#include "thinker/thinkertests/unmakemovetests.h"
#include "thinker/thinkertests/makemovetests.h"
#include "thinker/thinkertests/perft.h"
#include "thinker/thinkertests/biggerboardtest.h"
#include "ki/kitests/testkisimple.h"
#include "ki/kitests/testkibasicthinking.h"
#include "ki/kitests/testkibasicstrategy.h"
#include "main.h"
#include "shm/shm.h"
#include "pipe/pipe.h"
#include <stdbool.h>


bool denken = false;
bool everythingIsFinished = false;
infoVonServer *info;
Player *myPlayer;
BOARD_STRUCT *infoBoard;
BOARD_STRUCT *connectorBoard;
void *shmInfo;
int move;

void mysighandler(int sig) {
    if (sig == SIGUSR1) {
        printf("### received SIGUSR1\n");
        sleep(1); // todo....
        denken = true;
    }

    if (sig == SIGUSR2) {
        printf("### received SIGUSR2\n");
        sleep(100); // todo....
        everythingIsFinished = true;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "perft") == 0) {
        if (argc == 2) {
            printf("Please specify depth\n");
            exit(1);
        }
        int depth = atoi(argv[2]);
        printf("depth is %d\n", depth);
        fromCommandLine(depth);
        freeStatics();
        exit(0);
    }

    if (argc > 1 && strcmp(argv[1], "TEST") == 0) {
        printf("Test begin:.........\n");

        int fail = 0;

//        printf("Running fullTestSuite\n");
//        fail += fullTestSuite();
//
//        printf("Running convert move test Suite\n");
//        fail += testConvertMove();
//
//        printf("Running make move test Suite\n");
//        fail += runMakeMoveTests();
//
//        printf("Running unmake move test Suite\n");
//        fail += fullTestSuiteUnmakeMoveTests();
//
//        printf("Running big board tests Suite\n");
//        fail += testSuiteBigBoard();
//
//        printf("Running perft Suite\n");
//        fail += perftSuite();

        printf("Running testgetMoveTimeAndFieldSize().\n");
        fail += testGetMovetimeAndFieldSize();

        printf("Running testCharInNummer().\n");
        fail += testCharInNummer();

        printf("Running parse game over\n");
        fail += testParseGameover();

//        printf("Running basic KI Suite\n");
//        fail += kiTestsSimple();
//
//        printf("Running medium KI Suite\n");
//        fail += kiTestsBasicThinking();
//
//        printf("Running strategy KI Suite\n");
//        fail += kiTestsBasicStrategy();

        if (fail) {
            printf("Some tests failed, please fix them as soon as possible.\n");
            freeStatics();
            exit(1);
        }

        printf("Tested. All good.\n");
        freeStatics();
        return 0;
    }

    char *antwort = malloc(10 * sizeof(char));
    createShm();
    shmInfo = attachShm();
    info = shmInfo;
    info->players = shmInfo + sizeof(infoVonServer);
    int failState = 0;

    connectorBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(connectorBoard);

    createPipe(pd);
    switch (thinker = fork()) {
        /*Fehlerfall*/
        case -1:
            fprintf(stderr, "### Fehler bei fork()\n");
            break;

            /*Kindsprozess = Connector*/
        case 0:
            connector = getpid();
            thinker = getppid();
            connectorMasterMethod(connectorBoard, argc, argv, info, thinker, connector, shmInfo);
            break;

            /*Elternprozess = Thinker*/
        default:
            thinker = getpid();

            if (signal(SIGUSR1, mysighandler) == SIG_ERR) {
                fprintf(stderr, "### Error setting up signal for SIGUSR1.\n");
                failState = 1;
                break;
            }

            if (signal(SIGUSR2, mysighandler) == SIG_ERR) {
                fprintf(stderr, "### Error setting up signal for SIGUSR2.\n");
                failState = 1;
                break;
            }

            close(pd[0]); // Leseseite schließen
            while (1) {
                while (!denken) {
                    sleep(1); //Schreibseite muss warten bis Leseseite fertig ist.
                }
                denken = false;

//                printf("### Currently thinking...\n");
//                printBoardLouis(info->infoBoard);

                move = doThink(info->infoBoard, info->moveTime);
                getPrettyMove(move, antwort);

                //                printf("### Thinker(Elternprozess) schreibt Nachricht in pipe.\n");
                if (write(pd[1], antwort, strlen(antwort) + 1) < 0) {
                    perror("### write");
                    failState = 1;
                    break;
                }
                bzero(antwort, sizeof(antwort));

                if (everythingIsFinished) {
                    printf("### Received SIGUSR2, time to quit everything!\n");
                    break;
                }
            }

            break;
    }

    deleteShm();
    free(antwort);
    freeBoardStruct(connectorBoard);
    if (failState) {
        fprintf(stderr, "### Error happened somewhere\n");
    }

    freeStatics();

    return failState;
}
