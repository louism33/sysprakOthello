#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "shm.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "../thinker/board.h"
#include "../connector/connector.h"
#include "../thinker/board.h"


/*variablen zur Speicherung der Pid's*/
pid_t thinker;
pid_t connector;
int shmid;
infoVonServer *shmdata;



void createShm() {

    printf("Ich bin ein Shared Memory\n");

    /*erstelle ein Shm mit getshm() */
    shmid = shmget(IPC_PRIVATE, sizeof(infoVonServer)+sizeof(Player)+sizeof(BOARD_STRUCT), IPC_CREAT | SHM_R | SHM_W);
    printf("Die Shm-ID: %i\n", shmid);
    if (shmid == -1) {
        printf("Fehler bei key %d, mit der Größe %d\n", IPC_PRIVATE, SHMDATASIZE);
    }
}

infoVonServer *attachShm() {
    /* Shared-Memory-Segment anbinden */
    shmdata = (infoVonServer *) shmat(shmid, NULL, 0);
    //printf("Die Anfangsadresse vom Shm ist: %d\n", (int)*shmdata);
    if (shmdata == (void *) -1) {
        printf("Fehler bei der Anbindung mit shmat(): shmid %d\n", shmid);
    }
    
    return shmdata;
}

void deleteShm() {
    /*Löschen des SHM*/
    int res = shmctl(shmid, IPC_RMID,0);
    if (res == -1) {
        printf("Fehler beim Löschen des SHM");
    }
}

void writeShmEasy(char *x){
    strcpy(shmdata->gameName,x);
    printf("ich habe geschrieben:%s \n",shmdata->gameName );
}

void writeShm(infoVonServer *g, pid_t pidme, pid_t pidpa) {
    /*in Shm schreiben -> im struct infos verwalten und im shm speichern*/

//printf("(*g).me->mitspielerName): %s\n",(*g).me->mitspielerName);
strcpy(shmdata->MitspielerAnzahl,(*g).MitspielerAnzahl);
strcpy(shmdata->gameID,(*g).gameID);
strcpy(shmdata->gameKindName,(*g).gameKindName);
shmdata->thinker = pidpa;
shmdata->connector = pidme;
strcpy(shmdata->gameName,(*g).gameName);
shmdata->majorVersionNr=(*g).majorVersionNr;
shmdata->minorVersionNr=(*g).minorVersionNr;
//printf("------------------%s\n",shmdata->me->mitspielerName);
/*ToDo: funktioniert nicht !*/
//shmdata->me->bereit=(*g).me->bereit;
//strcpy(shmdata->me->mitspielerName,g->me->mitspielerName);
//shmdata->me->mitspielerNummer=g->me->mitspielerNummer;
//memcpy(shmdata->thinkerBoard->board, g->thinkerBoard->board, sizeof(int) * 8 * 8); //wenn Server eine Board von uns schickt.
//shmdata->thinkerBoard->sideToMove = g->thinkerBoard->sideToMove;
//printBoard(shmdata->thinkerBoard->board);

}

infoVonServer *readShm() {

    return shmdata;
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

