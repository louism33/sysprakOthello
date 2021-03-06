//
// Created by louis on 11/14/19.
//

#ifndef SYSPRAKOTHELLO_PERFORMCONNECTION_H
#define SYSPRAKOTHELLO_PERFORMCONNECTION_H

#include "connector.h"
#include <sys/types.h>
#include <sys/epoll.h>
#include "boardmessageparser.h"

typedef struct FieldSizeColumnAndRow {
    int row;
    int col;
} FieldSizeColumnAndRow;

int haveConversationWithServer(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           infoVonServer *info, pid_t thinker, pid_t connector, void *shmInfo, int epoll_fd, struct epoll_event *events, int timeOffset);

char *convertMove(int move, char *antwort);

int getMoveTimeAndFieldSize(char *buff, char *moveTime, char *fieldSize);

struct FieldSizeColumnAndRow charInNummer(char *fieldSize);

int getWinnerFromServer(char* buff);

int getMoveTime(char *buff);

#endif //SYSPRAKOTHELLO_PERFORMCONNECTION_H
