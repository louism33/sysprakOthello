//
// Created by louis on 11/14/19.
//

#ifndef SYSPRAKOTHELLO_PERFORMCONNECTION_H
#define SYSPRAKOTHELLO_PERFORMCONNECTION_H

struct fieldSizeNummer1and2
{
    int Nummer1;
    int Nummer2;
};

//int performConnection(int sock, char *version, char *id, char *player);

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard, BOARD_STRUCT *thinkerBoard);

char *convertMove(int move, char *antwort);

int getMovetimeandFieldsize(char *buff, char *moveTime, char *fieldSize);
struct fieldSizeNummer1and2 charInNummer(char *fieldSize);

#endif //SYSPRAKOTHELLO_PERFORMCONNECTION_H
