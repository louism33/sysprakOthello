#include "thinker/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
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
#include <sys/epoll.h>


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
        denken = true;
    }

    if (sig == SIGUSR2) {
        printf("### received SIGUSR2, setting finished flag to true\n");
        sleep(3); // todo, necessary?
        everythingIsFinished = true;
    }
}

int main(int argc, char *argv[]) {

    struct epoll_event event, events[5];
    bzero(&event,sizeof(event));
    int epoll_fd;

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

        printf("Running fullTestSuite\n");
        fail += fullTestSuite();

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

        printf("Running testgetMoveTimeAndFieldSize().\n");
        fail += testGetMovetimeAndFieldSize();

        printf("Running testCharInNummer().\n");
        fail += testCharInNummer();

        printf("Running parse game over\n");
        fail += testParseGameover();

        printf("Running basic KI Suite\n");
        fail += kiTestsSimple();

        printf("Running medium KI Suite\n");
        fail += kiTestsBasicThinking();

        printf("Running strategy KI Suite\n");
        fail += kiTestsBasicStrategy();

        if (fail) {
            printf("Some tests failed, please fix them as soon as possible.\n");
            freeStatics();
            exit(1);
        }

        printf("Tested. All good.\n");
        freeStatics();
        return 0;
    }


    createShm();
    shmInfo = attachShm();
    info = shmInfo;
    info->players = shmInfo + sizeof(infoVonServer);
    int failState = 0;

//    connectorBoard = malloc(sizeof(BOARD_STRUCT));
//    initialiseBoardStructToStarter(connectorBoard);

    printf("### Setting up epoll X\n");

    epoll_fd = epoll_create1(0);

    if(epoll_fd == -1)
    {
        fprintf(stderr, "### Failed to create epoll file descriptor\n");
        return 1;
    }

    connectorBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(connectorBoard);

    fflush(stdout);
    createPipe(pd);
    switch (thinker = fork()) {
        /*Fehlerfall*/
        case -1:
            fprintf(stderr, "### Fehler bei fork()\n");
            break;

            /*Kindsprozess = Connector*/
        case 0:
            event.events = EPOLLIN;
            event.data.fd = pd[0];

            int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pd[0], &event);

            if(ret)
            {
                printf("### epoll failed ... error is %s\n",
                       strerror(errno));

                fprintf(stderr, "### Failed to add file descriptor from pipe to epoll, %d\n", ret);
                failState = 1;
            } else {
                printf("### correctly registered pipe to epoll\n");
            }

            connector = getpid();
            thinker = getppid();
            printf("### Starting Connector Master Method\n");


            int c = connectorMasterMethod(connectorBoard, argc, argv, info, thinker, connector, shmInfo, epoll_fd, events);
            printf("### Connector Master Method has ended, with value: %d\n", c);
            failState += c;
            break;

            /*Elternprozess = Thinker*/
        default:
            thinker = getpid();

            int thinkerReturnValue = 0;

            printf("### Setting up Signals\n");
            fflush(stdout);

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

            printf("### Starting Thinker Main Loop\n");
            fflush(stdout);
            char *antwort = malloc(10 * sizeof(char));
            close(pd[0]); // Leseseite schließen
            while (1) {
                //Schreibseite muss warten bis Leseseite fertig ist.
                while (!denken && !everythingIsFinished) {
                }

                if (everythingIsFinished) {
                    printf("### Received SIGUSR2, time to quit everything!\n");
                    fflush(stdout);
                    break;
                }

                denken = false;

                move = doThink(info->infoBoard, info->moveTime);
                getPrettyMove(move, antwort);

                if (! everythingIsFinished && write(pd[1], antwort, strlen(antwort) + 1) < 0) {
                    perror("### write");
                    failState = 1;
                    break;
                }
                bzero(antwort, sizeof(antwort));
            }

            fprintf(stderr, "### Thinker Main Loop has ended with value: %d\n", thinkerReturnValue);
            fflush(stdout);
            free(antwort);
            freeStatics();
            break;
    }

    printf("### Cleaning up SHM %d\n", getpid());
    fflush(stdout);
    deleteShm();

    freeBoardStruct(connectorBoard);
    if (failState != 0) {
        fprintf(stderr, "### Error happened somewhere\n");
    } else {
        printf("### seems to have gone ok\n");
    }

//    freeStatics();

    printf("done %d\n", getpid());
    return failState;
}
