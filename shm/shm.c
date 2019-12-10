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

/*variablen zur Speicherung der Pid's*/
pid_t thinker;
pid_t connector;
int shmid;
infoVonServer *shmdata;



void createShm() {

    printf("Ich bin ein Shared Memory\n");

    /*erstelle ein Shm mit getshm() */
    shmid = shmget(IPC_PRIVATE, sizeof(infoVonServer)+sizeof(Player), IPC_CREAT | SHM_R | SHM_W);
    printf("Die Shm-ID: %i\n", shmid);
    if (shmid == -1) {
        printf("Fehler bei key %d, mit der Größe %d\n", IPC_PRIVATE, SHMDATASIZE);
    }
}

void attachShm() {
    /* Shared-Memory-Segment
     anbinden */
    shmdata = (infoVonServer *) shmat(shmid, NULL, 0);
    //printf("Die Anfangsadresse vom Shm ist: %d\n", (int)*shmdata);
    if (shmdata == (void *) -1) {
        printf("Fehler bei der Anbindung mit shmat(): shmid %d\n", shmid);
    }
    
    
}

void deleteShm() {
    /*Löschen des SHM*/
    int res = shmctl(shmid, IPC_RMID,0);
    if (res == -1) {
        printf("Fehler beim Löschen des SHM");
    }
}


void writeShm(infoVonServer *g, pid_t me, pid_t pa) {
    /*in Shm schreiben -> im struct infos verwalten und im shm speichern*/

strcpy(shmdata->MitspielerAnzahl,(*g).MitspielerAnzahl);
//  strcpy(shmdata->gameID,(*g).gameID);
//  strcpy(shmdata->gameKindName,(*g).gameKindName);
// shmdata->thinker = pa;
// shmdata->connector = me;
// strcpy(shmdata->gameName,(*g).gameName);
// shmdata->majorVersionNr=(*g).majorVersionNr;
// shmdata->minorVersionNr=(*g).minorVersionNr;
// shmdata->me->bereit=(*g).me->bereit;
// strcpy(shmdata->me->mitspielerName,(*g).me->mitspielerName);
// shmdata->me->mitspielerNummer=(*g).me->mitspielerNummer;
printf("ich habe geschrieben.\n");
printf("shmdata.MitspielerAnzahl: %s\n",shmdata->MitspielerAnzahl);
// printf("shmdata.gameID: %s\n",shmdata->gameID);
// printf("shmdata.gameKindName: %s\n",shmdata->gameKindName);
// printf("shmdata.thinker: %d\n",shmdata->thinker);
// printf("shmdata.connector: %d\n",shmdata->connector);
}

void readShm() {


    printf("read\n");
    printf("Das erste Element im shm ist: %i\n", shmdata->connector);
    printf("Das zweite Element im shm ist: %s\n", shmdata->gameID);
    printf("Das dritte Element im shm ist: %s\n", shmdata->gameKindName);
    printf("Das vierte Element im shm ist: %s\n", shmdata->gameName);
    printf("Das fuenfte Element im shm ist: %i\n", shmdata->thinker);

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

