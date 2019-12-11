//
// Created by louis on 11/14/19.
//

#ifndef SYSPRAKOTHELLO_PERFORMCONNECTION_H
#define SYSPRAKOTHELLO_PERFORMCONNECTION_H
#include "connector.h"
#include <sys/types.h>
#include "boardmessageparser.h"

//int performConnection(int sock, char *version, char *id, char *player);

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           BOARD_STRUCT *thinkerBoard, infoVonServer *info,pid_t thinker,pid_t connector,Player *myPlayer,Player *gegener) ;
char *convertMove(int move, char *antwort);


#endif //SYSPRAKOTHELLO_PERFORMCONNECTION_H
