//
// Created by louis on 11/14/19.
//

#ifndef SYSPRAKOTHELLO_PERFORMCONNECTION_H
#define SYSPRAKOTHELLO_PERFORMCONNECTION_H
#include "connector.h"
#include <sys/types.h>
#include "boardmessageparser.h"

//int performConnection(int sock, char *version, char *id, char *player);

struct fieldSizeNummer1and2
{
    int Nummer1;
    int Nummer2;
};

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                      	 infoVonServer *info,pid_t thinker,pid_t connector,void *shmInfo) ;
char *convertMove(int move, char *antwort);

int getMovetimeandFieldsize(char *buff, char *moveTime, char *fieldSize);
struct fieldSizeNummer1and2 charInNummer(char *fieldSize);

#endif //SYSPRAKOTHELLO_PERFORMCONNECTION_H
