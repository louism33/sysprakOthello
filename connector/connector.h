//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_CONNECTOR_H
#define ALEXTHEFRIENDLYAI_CONNECTOR_H

#include <sys/types.h>
#include <stdbool.h>
#include "boardmessageparser.h"

typedef struct Player{
    int mitspielerNummer;
    bool bereit;
    char mitspielerName[32];
}Player;

typedef struct infoVonServer
{
    char gameName[32];
    char gameID[13];
    char gameKindName[32];
    int majorVersionNr;
    int minorVersionNr;
    char MitspielerAnzahl[5];
    struct Player* me;
    pid_t thinker;
    pid_t connector;
    struct BOARD_STRUCT *thinkerBoard;
} infoVonServer;



int connectorMasterMethod(BOARD_STRUCT *connectorBoard, BOARD_STRUCT *thinkerBoard, int argc, char *argv[], infoVonServer *info, pid_t thinker, pid_t connector,Player *myPlayer,Player *gegener);

void performConnection();

int getDefaultPort();

#endif //ALEXTHEFRIENDLYAI_CONNECTOR_H
