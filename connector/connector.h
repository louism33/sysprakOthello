//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_CONNECTOR_H
#define ALEXTHEFRIENDLYAI_CONNECTOR_H

#include <sys/types.h>
#include "boardmessageparser.h"

typedef struct infoVonServer{
    char playerNumber[32];//0 oder 1 welche Spielfarbe wir sind.
    char myPlayerName[32];//spielerName 
    char gameId[32];//13 stellige nummer
}infoVonServer;

int connectorMasterMethod(BOARD_STRUCT * connectorBoard, BOARD_STRUCT * thinkerBoard, int argc, char *argv[],infoVonServer *info, pid_t thinker,pid_t connector, moveTimeAndBoard *moveTimeAndBoard );

void performConnection();

int getDefaultPort();

#endif //ALEXTHEFRIENDLYAI_CONNECTOR_H
