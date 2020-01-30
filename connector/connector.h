//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_CONNECTOR_H
#define ALEXTHEFRIENDLYAI_CONNECTOR_H

#include <sys/types.h>
#include <sys/epoll.h>
#include <stdbool.h>
#include "boardmessageparser.h"
#include "../thinker/board.h"

typedef struct Player {
    int mitspielerNummer;
    bool bereit;
    char mitspielerName[32];
} Player;

typedef struct infoVonServer {
    char gameName[32];
    char gameID[13];
    char gameKindName[32];
    int majorVersionNr;
    int minorVersionNr;
    int MitspielerAnzahl;
    struct Player *me;
    Player *players;
    pid_t thinker;
    pid_t connector;
    BOARD_STRUCT *infoBoard;
    int moveTime;
} infoVonServer;


int connectorMasterMethod(BOARD_STRUCT *connectorBoard, int argc, char *argv[], infoVonServer *info, pid_t thinker,
                          pid_t connector, void *shmInfo, int epoll_fd, struct epoll_event *events);

void performConnection();

int getDefaultPort();

#endif //ALEXTHEFRIENDLYAI_CONNECTOR_H
