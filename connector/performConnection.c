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

#define MAX 240
#define PLAYER
#define BOARD int*

//Die Prolog-Phase der Kommunikation
// todo, reconnect logic
// todo, be careful of people trolling you by calling game "game over"

int writeToServer(int sockfd, char message[]) {
    write(sockfd, message, strlen(message));
    printf("Sending to server-> %s\n", message);
}

void haveConversationWithServer(int sockfd, char *gameID, char *player, char *gameKindName, BOARD connectorBoard) {
    char buff[MAX];
    char gameName[20];
    char playerNumber[5];
    char myPlayerName[9];
    char opponent[10];
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
    char gameKindNameFromServer[16];

    moveTimeAndBoard *moveTimeAndBoard = malloc(sizeof(moveTimeAndBoard));

    // todo, + ENDPLAYERS
    // todo, + GAMEOVER
    // todo, read move time

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
                    printf("##### We play reversi now.#####\n\n");
                } else {
                    printf("##### We don't play reversi now.#####\n\n");
                    exit(1);
                }

                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
                printf("%s", buff);

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
            if (strlen(buff) > 75) {
                printf("starting parse board\n");
                parseBoardMessage(connectorBoard, moveTimeAndBoard, buff);
                printf("finished parse board, here is the board I was able to parse:\n");

                printBoardLouis(connectorBoard);


                // todo , copy connectorBoard in to Thinkerboard
                printf("finished parse board\n");
                writeToServer(sockfd, thinking);
                writeToServer(sockfd, playf5);
            }

            if ((strncmp("+ WAIT", buff, 6)) == 0) {
                writeToServer(sockfd, okWait);
            }

            if ((strncmp("+ ENDFIELD", buff, 10)) == 0) {
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

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD connectorBoard) {

    haveConversationWithServer(sock, gameID, player, gameKindName, connectorBoard);

    printf("performConnection %d\n", sock);

    return 0;
}
