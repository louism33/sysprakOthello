#ifndef shared_memory
#define SHMDATASIZE 1024

#include <sys/types.h>
#include <stdbool.h>

void createShm();

int createProcesses();

void attachShm();

void writeShm();

void readShm();

void deleteShm();

void waitForChild();


/* struct mit Informationen über Spielername, Spielernummer, Anzahl der Spieler, PID's  
die Infos bekommt der Connector vom Server und legt sie in shm in dieses Struct gameInfo ab */

// typedef struct {
//     char myGamerName[32];
//     char myGamerId[32];
//     char nGamer[32];
//     /* PID von Kind- und Vaterprozess*/
//     pid_t thinker;
//     pid_t connector;

// } gameInfo;

// typedef struct {
//     int gamerId;
//     char gamerName[10];
//     bool readyOrNot; //Flag: true bzw.false. true ready und false notready

// } gamer;


#endif 