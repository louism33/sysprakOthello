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
#include <stdbool.h>
// if thinker is parent, retry logic may be easier to implement
// including learning
bool denken = false;
infoVonServer *shmInfo; 
void mysighandler(int sig)
{

    if (sig == SIGUSR1)
    {
        sleep(1);
        printf("****SIGUSR1 empfangen.Thinker kann jetzt Nachricht in pipe schreiben.*****\n\n");
        printf("ich habe geschrieben.\n");
        printf("shmInfo.MitspielerAnzahl: %s\n",shmInfo->MitspielerAnzahl);
        printf("shmInfo.gameID: %s\n",shmInfo->gameID);
        printf("shmInfo.gameKindName: %s\n",shmInfo->gameKindName);
        printf("shmInfo.thinker: %d\n",shmInfo->thinker);
        printf("shmInfo.connector: %d\n",shmInfo->connector);
        printf("shmInfo->majorVersionNr: %d\n", shmInfo->majorVersionNr);
        printf("shmInfo->gameName: %s\n",shmInfo->gameName);
        printf("shmInfo->minorVersionNr: %d\n", shmInfo->minorVersionNr);
        //printf("shmInfo->me->bereit: %d\n",shmInfo->me->bereit);
        printf("shmInfo->me->mitspielerName: %s\n",shmInfo->me->mitspielerName);
        //printf("shmInfo->me->mitspielerNummer: %d\n",shmInfo->me->mitspielerNummer);
        denken = true;

    }
}

int main(int argc, char *argv[])
{
    
    char *antwort = malloc(256 * sizeof(char));
    infoVonServer *info = malloc(sizeof(infoVonServer));
    Player *myPlayer = malloc(sizeof(Player));
    Player *gegner = malloc(8 * sizeof(Player));
    shmInfo =info;
    shmInfo->me=myPlayer;

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
    //  moveTimeAndBoard *movetime=malloc(sizeof(moveTimeAndBoard));
//int movetime;
    createShm();
    shmInfo = attachShm();
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
        // if (kill(thinker, SIGUSR1) && killready)
        // {
        //     printf("Fehler beim senden des Signals\n");
        //     exit(1);
        // }
        // else
        // {
        //     printf("*************Signal1 wird geschickt*************\n");
        // }
        connectorMasterMethod(connectorBoard, thinkerBoard, argc, argv, info, thinker, connector, myPlayer, gegner);
        // printf("info: %s\n", info->gameId);
        // close(pd[1]);    // Schreibseite schließen
        // char buffer[50]; // Puffer zum speichern von gelesenen Daten
        //                  //ssize_t nread;
        // for (int i = 1; i < 5; i++)
        // {
        //     if (read(pd[0], buffer, sizeof(buffer)) == -1)
        //     { // Leseseite auslesen (blockiert hier bis Daten vorhanden)
        //         perror("read");
        //         exit(EXIT_FAILURE);
        //     }
        //     else
        //     { //sleep(1);
        //         printf("Connector(Kindeprozess) bekommt Nachricht von pipe: %s\n\n", buffer);
        //         //sleep(1);
        //     }
        // }

        break;

    /*Elternprozess = Thinker*/
    default:
        printf("Im Elternprozess\n");
        thinker = getpid();
        printf("ThinkerPID = %i\n", thinker);
        close(pd[0]); // Leseseite schließen
        if (signal(SIGUSR1, mysighandler) == SIG_ERR)
        {
            printf("Error beim Empfangen des Signal.\n");
            exit(1);
        }
        while(1){
            //printf("in schleife.\n");
            while (!denken)
            {
                sleep(1); //Schreibseite muss warten bis Leseseite fertig ist.
            }
            denken = false;
            /*denke jetzt*/
            MOVE move = doThink(info->thinkerBoard);
            getPrettyMove(move,antwort);
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
    freeBoardStruct(connectorBoard);
    freeBoardStruct(thinkerBoard);
    free(info);
    free(antwort);
    free(myPlayer);
    free(gegner);
   // free(movetime);
    return 0;
}
