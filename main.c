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
#include "main.h"
#include "shm/shm.h"
#include "pipe/pipe.h"
#include <stdbool.h>
#include "thinker/thinkertests/dothinktest.h"
// if thinker is parent, retry logic may be easier to implement
// including learning
bool denken = false;
infoVonServer *info;
Player *myPlayer;
BOARD_STRUCT *infoBoard;
BOARD_STRUCT *connectorBoard;
void *shmInfo;
int move;

void mysighandler(int sig)
{

    if (sig == SIGUSR1)
    {
        sleep(1);
        // printf("****SIGUSR1 empfangen.Thinker kann jetzt Nachricht in pipe schreiben.*****\n\n");
        // printf("ich habe geschrieben.\n");
        // printf("shmInfo.MitspielerAnzahl: %d\n", info->MitspielerAnzahl);
        // printf("shmInfo.gameID: %s\n", info->gameID);
        // printf("shmInfo.gameKindName: %s\n", info->gameKindName);
        // printf("shmInfo.thinker: %d\n", info->thinker);
        // printf("shmInfo.connector: %d\n", info->connector);
        // printf("shmInfo->majorVersionNr: %d\n", info->majorVersionNr);
        // printf("shmInfo->gameName: %s\n", info->gameName);
        // printf("shmInfo->minorVersionNr: %d\n", info->minorVersionNr);
        // printf("shmInfo->me->mitspielerNummer: %d\n", info->players[0].mitspielerNummer); // ToDo 0 stimmt nicht in jedem Fall -> überdenke die Schreibweise
        // printf("shmInfo->me->bereit: %d\n", info->players[0].bereit);
        // printf("shmInfo->me->mitspielerName: %s\n", info->players[0].mitspielerName);
        // printf("Wir haben ein board in shm.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        // printBoard(info->infoBoard->board);
        denken = true;
    }
}

int main(int argc, char *argv[])
{

    char *antwort = malloc(256 * sizeof(char));
    createShm();
    shmInfo = attachShm();
    info = shmInfo;
    info->players = shmInfo + sizeof(infoVonServer);
    // printf("shminfo:%p\n",shmInfo);
    // printf("info->player: %p\n",info->players);
    // printf("info: %p\n",info);
    // printf("info+sizeof:%p\n",info+sizeof(infoVonServer));
    //myPlayer = shmInfo + sizeof(infoVonServer);

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

        printf("Runnning dothinktest.\n");
        fail += denkentest();

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

    connectorBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(connectorBoard);

    createPipe(pd);
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
        connectorMasterMethod(connectorBoard, argc, argv, info, thinker, connector, shmInfo);
        break;

    /*Elternprozess = Thinker*/
    default:
        printf("Im Elternprozess\n");
        thinker = getpid();
        printf("ThinkerPID = %i\n", thinker);

        if (signal(SIGUSR1, mysighandler) == SIG_ERR)
        {
            printf("Error beim Empfangen des Signal.\n");
            exit(1);
        }

        close(pd[0]); // Leseseite schließen
        while (1)
        {
            //printf("in schleife.\n");
            while (!denken)
            {
                sleep(1); //Schreibseite muss warten bis Leseseite fertig ist.
            }
            denken = false;

            //printBoard(info->infoBoard->board);
            printf("jetzt thinking...\n\n");
            move = doThink(info->infoBoard, 3000);
            printf("Der Erste Zug geht zu %d\n", move);
            getPrettyMove(move, antwort);
            printf("antwort: %s\n", antwort);
            printf("Thinker(Elternprozess) schreibt Nachricht in pipe.\n");
            if (write(pd[1], antwort, strlen(antwort) + 1) < 0)
            { // In Schreibseite schreiben
                perror("write");
                exit(EXIT_FAILURE);
            }
            bzero(antwort, sizeof(antwort));
        }

        break;
    }

    deleteShm();
    free(antwort);
    freeBoardStruct(connectorBoard);
    return 0;
}
