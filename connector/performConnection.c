#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "boardmessageparser.h"
#include "../thinker/thinker.h"

#define MAX 240
#define PLAYER
#define MOVE int
#define BOARD int*

enum Phase {PROLOG = 0, SPIELVERLAUF = 1, SPIELZUG = 2};

//Die Prolog-Phase der Kommunikation
// todo, reconnect logic
// todo, be careful of people trolling you by calling game "game over", implement PHASE int/enum

int writeToServer(int sockfd, char message[]) {
    write(sockfd, message, strlen(message));
    printf("Sending to server-> %s\n", message);
}

char *convertMove(int move) {
    return "D3"; // todo, implement conversion between 0-63 and [A-H][1-8]
}

int dealWithGameOverCommand(char* buff) {
    /*
S: + GAMEOVER
S: + FIELD hh Anzahl Spalten ii,hh Anzahl Zeilen ii
Die folgende Zeile wird nun für jede Zeile des Spielfeldes geschickt, beginnend bei der obersten Zeile des Spiel-
felds:
S: + hh Y ii hh Stein 1Y ii hh Stein 2Y ii ... hh Stein X max Y ii
S: + ENDFIELD
S: + PLAYER0WON hh ’Yes’ oder ’No’ ii
S: + PLAYER1WON hh ’Yes’ oder ’No’ ii
S: + QUIT
hh Abbau der TCP-Verbindung durch Gameserver ii
Nach einem GAMEOVER stellen die weiteren Zeilen den Spielstand dar, mit dem das Partieende erreicht wurde. Dieser
wird an alle Mitspieler geschickt. Zudem wird angegeben, welche Mitspieler gewonnen haben. Es ist auch möglich, dass
eine Partie in einem Unentschieden endet. In dem Fall ist allen Mitspielern der Gewinnstatus der Partie auf Yes gesetzt.
Nach QUIT beendet der Server die Verbindung
     */
    return 0; // todo, implement
}

char *getMoveFromThinker(BOARD connectorBoard, BOARD thinkerBoard, int moveTime) {
    memcpy(thinkerBoard, connectorBoard, sizeof(int) * 8 * 8);

    int move = doThink(thinkerBoard, moveTime);

    printf("move is: %d\n", move);

    char *convertedMove = convertMove(move);

    printf("converted move is: %s\n", convertedMove);

    return convertedMove;
}

// todo, handle end state, what do we do once game is over?
void haveConversationWithServer(int sockfd, char *gameID, char *player, char *gameKindName, BOARD connectorBoard,
                                BOARD thinkerBoard) {
    char buff[MAX]; // todo pick standard size for everything, and avoid buffer overflow with ex. strncpy
    char gameName[64]; // example: Game from 2019-11-18 17:42
    char playerNumber[32];
    char myPlayerName[32];
    char opponent[32];
    int n, readResponse = 0;

    char version[] = "VERSION 2.42\n";
    char okWait[] = "OKWAIT\n";

    char gameIdToSend[20];
    strcpy(gameIdToSend, "ID ");
    strcat(gameIdToSend, gameID);
    strcat(gameIdToSend, "\n");

    char playerToSend[] = "PLAYER\n"; // todo get from argument. need extra whitespace if there is a player provided
    char thinking[] = "THINKING\n";
    char playf5[] = "PLAY D3\n";
    int lengthOfPlayCommandToSendToKeep = 5;
    char moveReceivedFromThinker[3];
    char *moveReceivedFromThinkerTEMP;
    char gameKindNameFromServer[32];
    char playCommandToSend[10];

    enum Phase phase = PROLOG; // this can be used to make sure we do not get confused about what stage of the game we are in

    moveTimeAndBoard *moveTimeAndBoard = malloc(sizeof(moveTimeAndBoard));

    // todo, + ENDPLAYERS

    if (!gameKindName) {
        printf("game kind name not provided, exiting");
        exit(1);
    }

    printf("########## %s\n", gameKindName);
    for (;;) {
        if ((readResponse = read(sockfd, buff, sizeof(buff)))) {
            printf("%s\n", buff);

            // step one, send VERSION 2.xxx
            if ((strncmp("+ MNM Gameserver", buff, 16)) == 0) {
                writeToServer(sockfd, version);
            }

            // step two, send game ID
            if ((strncmp("+ Client version accepted", buff, 25)) == 0) {
                writeToServer(sockfd, gameIdToSend);
            }

            // step three, read PLAYING, wait for another read, then send PLAYER info
            if (strncmp("+ PLAYING ", buff, 10) == 0) {
                strncpy(gameKindNameFromServer, buff + 10, strlen(buff) - strlen("+ PLAYING "));
                if (strncmp(gameKindName, gameKindNameFromServer, 7) == 0) {
                    printf("##### We play reversi now.#####\n");
                } else {
                    printf("##### We don't play reversi now.#####\n");
                    exit(1);
                }

                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1); // todo, possibly stick to only one central read?
                printf("%s\n", buff);

                strncpy(gameName, buff + 2, strlen(buff) - strlen("+ "));
                printf("-----------save gameName: %s\n", gameName);
                if (player == NULL) {
                    writeToServer(sockfd, playerToSend);
                } else {
                    strcpy(playerToSend, "PLAYER ");
                    strcat(playerToSend, player);
                    writeToServer(sockfd, playerToSend);
                }
            }

            // step four, read YOU
            if (strncmp("+ YOU", buff, 5) == 0) {
                // todo, save information from Server here
                //finished
                strncpy(playerNumber, buff + 6, 1);
                printf("--------save  playerNumber: %s\n", playerNumber);
                strncpy(myPlayerName, buff + 8, strlen(buff) - strlen("+ YOU 0 "));
                printf("--------save my playerName: %s\n", myPlayerName);
            }

            // step five, read board information and time to move from server.
            // todo, extract timeToMove info
            // todo, extract board info
            // todo, read name of opponent
            // todo, read Breit 0 or 1 and save Breit. If 0, print "Spieler 1 (Uli) ist noch nicht bereit"
            if (strlen(buff) > 75) { // todo make better (add check for first chars for example)
                printf("sending thinking command\n");
                writeToServer(sockfd, thinking);
                printf("sent thinking command\n");

                printf("starting parse board\n");
                parseBoardMessage(connectorBoard, moveTimeAndBoard, buff);
                printf("finished parse board, here is the board I was able to parse:\n");
                printBoardLouis(connectorBoard);
                printf("finished parse board\n");
                printf("sending relevant info to thinker\n");

                moveReceivedFromThinkerTEMP = getMoveFromThinker(connectorBoard, thinkerBoard, moveTimeAndBoard->movetime);
                printf("received from thinker: %s\n", moveReceivedFromThinkerTEMP);
                if (strlen(moveReceivedFromThinkerTEMP) != 2) {
                    fprintf(stderr, "move of incorrect length received from thinker: %s\n",
                            moveReceivedFromThinkerTEMP);
                    exit(1); // todo in future we want to implement retry logic etc to avoid crashing on a single error
                }
                moveReceivedFromThinker[0] = moveReceivedFromThinkerTEMP[0];
                moveReceivedFromThinker[1] = moveReceivedFromThinkerTEMP[1];
                moveReceivedFromThinker[2] = '\0';

                strcpy(playCommandToSend, "PLAY ");
                strcat(playCommandToSend, moveReceivedFromThinker);
                strcat(playCommandToSend, "\n");
                printf("playCommandToSend: %s\n", playCommandToSend);

                writeToServer(sockfd, playCommandToSend);
                playCommandToSend[0] = '\0';
            }

            if ((strncmp("+ WAIT", buff, 6)) == 0) {
                writeToServer(sockfd, okWait);
            }

            if ((strncmp("+ GAMEOVER", buff, 10)) == 0) {
                phase = PROLOG;
                dealWithGameOverCommand(buff);
//                writeToServer(sockfd, okWait);
            }

            if ((strncmp("+ ENDFIELD", buff, 10)) == 0) { // todo, is this necessary? I don't think this is ever called
                printf("endfield received, possibly something is wrong!!!\n");
                writeToServer(sockfd, thinking);
            }

            if (readResponse == -1) {
                printf("Could not read from server");
                exit(0);
            }
            bzero(buff, sizeof(buff));
        }
    }
}

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD connectorBoard,
                           BOARD thinkerBoard) {

    haveConversationWithServer(sock, gameID, player, gameKindName, connectorBoard, thinkerBoard);

    printf("performConnection %d\n", sock);

    return 0;
}
