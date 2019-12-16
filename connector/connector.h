//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_CONNECTOR_H
#define ALEXTHEFRIENDLYAI_CONNECTOR_H


int doConnect(int argc, char *argv[], int mockGame, char *gameID, char *player,
              int usingCustomConfigFile, char *filePath, BOARD_STRUCT *connectorBoard,
              BOARD_STRUCT *thinkerBoard);


int connectorMasterMethod(BOARD_STRUCT * connectorBoard, BOARD_STRUCT * thinkerBoard, int argc, char *argv[]);

void performConnection();

int getDefaultPort();

#endif //ALEXTHEFRIENDLYAI_CONNECTOR_H
