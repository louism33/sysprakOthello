//
// Created by louis on 11/14/19.
//

#ifndef SYSPRAKOTHELLO_PERFORMCONNECTION_H
#define SYSPRAKOTHELLO_PERFORMCONNECTION_H

#include "connector.h"
#include <sys/types.h>
#include "boardmessageparser.h"

typedef struct FieldSizeColumnAndRow {
    int row;
    int col;
} FieldSizeColumnAndRow;

//int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
//                           infoVonServer *info, pid_t thinker, pid_t connector, void *shmInfo);

int haveConversationWithServer(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           infoVonServer *info, pid_t thinker, pid_t connector, void *shmInfo);

char *convertMove(int move, char *antwort);

int getMoveTimeAndFieldSize(char *buff, char *moveTime, char *fieldSize);

struct FieldSizeColumnAndRow charInNummer(char *fieldSize);

#endif //SYSPRAKOTHELLO_PERFORMCONNECTION_H
