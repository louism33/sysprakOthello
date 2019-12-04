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
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
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

pid_t thinker;
pid_t connector;
int shmid;
gameInfo *shmdata;
gameInfo g1 = {"Marlene","7647","2"};


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
    int signalVonKill = 0;
    int fail=0;
    printf("Hello World! I am Alex. This is the main method\n");

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

        printf("Running convert move test Suite\n");
        fail += testConvertMove();

        printf("Running make move test Suite\n");
        fail += runMakeMoveTests();

        printf("Running unmake move test Suite\n");
        fail += fullTestSuiteUnmakeMoveTests();

    }

        // todo, this is just an idea, it depends on how we do shm (shared memory)
        // we will use two separate boards. One for connector that we will update with info from server
        // one to be used internally by thinker. When connector receives update, we copy connector board into thinker board

    BOARD_STRUCT *connectorBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(connectorBoard);

    BOARD_STRUCT *thinkerBoard = malloc(sizeof(BOARD_STRUCT));
    initialiseBoardStructToStarter(thinkerBoard);

    //shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    //printf("Id: %d\n", shmid);
    createShm();
    attachShm();

        // gameInfo *infoVonServer;
        // shmdata=infoVonServer;//kriegen wir von Server,also connectorMaterMethod()
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
        printf("Meine PID = %i\n", connector);

        //connectorMasterMethod(connectorBoard, thinkerBoard, argc, argv);
        writeShm(&g1, connector, thinker);
            //printf("ich ..\n");
        /*while (0)
        {
            sleep(3);
            signalVonKill = kill(thinker, SIGUSR1); //signal schicken
        }*/

        break;

        /*Elternprozess = Thinker*/
        default:
        sleep(2);
        printf("Im Elternprozess\n");
        thinker = getpid();
        printf("Meine PID = %i\n", thinker);
        //thinkerMasterMethod(thinkerBoard, signalVonKill);
        signal(SIGUSR1, mysighandler); //signal behandeln
        readShm();
        
        
        /*while (1)
        {
            

        }*/
                //waitForChild();
        //break;
    }

        freeBoardStruct(connectorBoard);
        freeBoardStruct(thinkerBoard);
        //shmctl(shmid, IPC_RMID,0);
        deleteShm();
        return 0;
}
