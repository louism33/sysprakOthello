#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "shm.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


/*variablen zur Speicherung der Pid's*/
pid_t thinker;
pid_t connector;
int shmid;
gameInfo *shmdata;


int createProcesses() {
    gameInfo g1 = {"Marlene", 4356, 1};

    createShm();
    attachShm();

    switch (thinker = fork()) {
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
            performConnection();
            writeShm(&g1, connector, thinker);
            break;

            /*Elternprozess = Thinker*/
        default:
            sleep(1);
            printf("Im Elternprozess\n");
            thinker = getpid();
            printf("Meine PID = %i\n", thinker);
            readShm();
            deleteShm();
            break;

    }
    return EXIT_SUCCESS;
}

void createShm() {

    printf("Ich bin ein Shared Memory\n");

    /*erstelle ein Shm mit getshm() */
    shmid = shmget(IPC_PRIVATE, sizeof(gameInfo) + sizeof(gamer), IPC_CREAT | SHM_R | SHM_W);
    printf("Die Shm-ID: %i\n", shmid);
    if (shmid == -1) {
        printf("Fehler bei key %d, mit der Größe %d\n", IPC_PRIVATE, SHMDATASIZE);
    }
}

void attachShm() {
    /* Shared-Memory-Segment anbinden */
    shmdata = (gameInfo *) shmat(shmid, NULL, 0);
    //printf("Die Anfangsadresse vom Shm ist: %d\n", (int)*shmdata);
    if (shmdata == (void *) -1) {
        printf("Fehler bei der Anbindung mit shmat(): shmid %d\n", shmid);
    }
}

void deleteShm() {
    /*Löschen des SHM*/
    int res = shmctl(shmid, IPC_RMID, NULL);
    if (res == -1) {
        printf("Fehler beim Löschen des SHM");
    }
}


void writeShm(gameInfo *g, pid_t me, pid_t pa) {
    /*in Shm schreiben -> im struct infos verwalten und im shm speichern*/

    shmdata->nGamer = (*g).nGamer;
    shmdata->myGamerId = (*g).myGamerId;
    strcpy(shmdata->myGamerName, (*g).myGamerName);
    shmdata->thinker = pa;
    shmdata->connector = me;


}

void readShm() {
    printf("Der erste Inhalt im shm ist: %i\n", shmdata->nGamer);
    printf("Das zweite Element im shm ist: %i\n", shmdata->myGamerId);
    printf("Das dritte Element im shm ist: %s\n", shmdata->myGamerName);
    printf("Das vierte Element im shm ist: %i\n", shmdata->thinker);
    printf("Das fuenfte Element im shm ist: %i\n", shmdata->connector);
}

void waitForChild() {
    int wait, status;
    wait = waitpid(connector, &status, WNOHANG);

    if (WIFEXITED(status)) {
        printf("Kind normal beendet mit Rückgabewert %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Kind mit Signalnummer %d beendet\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("Kind wurde angehalten mit Signalnummer %d\n", WSTOPSIG(status));
    }
}