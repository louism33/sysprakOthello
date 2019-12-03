//
// Created by louis on 11/13/19.
//

#ifndef ALEXTHEFRIENDLYAI_CONNECTOR_H
#define ALEXTHEFRIENDLYAI_CONNECTOR_H

gameInfo* connectorMasterMethod(BOARD_STRUCT * connectorBoard, BOARD_STRUCT * thinkerBoard, int argc, char *argv[]);

void performConnection();

int getDefaultPort();

#endif //ALEXTHEFRIENDLYAI_CONNECTOR_H
