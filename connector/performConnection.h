//
// Created by louis on 11/14/19.
//

#ifndef SYSPRAKOTHELLO_PERFORMCONNECTION_H
#define SYSPRAKOTHELLO_PERFORMCONNECTION_H


int performConnection(int sock, char *version, char *id, char *player);

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           BOARD_STRUCT *thinkerBoard,gameInfo* infoVonServer);
char *convertMove(int move, char *antwort);


#endif //SYSPRAKOTHELLO_PERFORMCONNECTION_H
