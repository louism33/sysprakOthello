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

#define MAX 240

#define PLAYER

//Die Prolog-Phase der Kommunikation
char *mystrcat(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *newstr = malloc(128 * sizeof(char));
    for (int i = 0; i < len1; i++) {
        *(newstr + i) = *(str1 + i);
    }
    for (int j = 1; j <= len2; j++) {
        *(newstr + len1 - 1 + j) = *(str2 + j - 1);
    }
    return newstr;
}

char *createinfo(int idikator, char *daten) {
    char temp1[] = "VERSION ";
    char temp2[] = "ID ";
    char temp3[] = "PLAYER ";
    char *version = &temp1[0];
    char *id = &temp2[0];
    char *player = &temp3[0];
    if (idikator == 1) {
        char *version_msg = mystrcat(version, daten);
        return version_msg;
    }

    if (idikator == 2) {
        char *id_msg = mystrcat(id, daten);
        return id_msg;
    }

    if (idikator == 3) {
        char *player_msg = player;
        return player_msg;
    }

    return NULL;
}

// todo, reconnect logic
// todo, be careful of people trolling you by calling game "game over"

int writeToServer(int sockfd, char message[]) {
    write(sockfd, message, strlen(message));
    printf("Sending to server-> %s\n", message);
}

void haveConversationWithServer(int sockfd, char *gameID, char *player, char *gameKindName) {
    char buff[MAX];
    int n, readResponse = 0;
    char version[] = "VERSION 2.42\n";
    char okWait[] = "OKWAIT\n";

    char gameIdToSend[20];
    strcpy(gameIdToSend, "ID ");
    strcat(gameIdToSend, gameID);
    strcat(gameIdToSend, "\n");

    char playerToSend[] = "PLAYER\n"; // todo get from argument. need extra whitespace if there is a player provided
    char thinking[] = "THINKING\n";
    char playf5[] = "PLAY C3\n";

    // todo, + ENDPLAYERS
    // todo, + GAMEOVER
    // todo, read move time

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
            // todo, check that gamekind is reversi
            // todo, get Game-Name from server
            if (strncmp("+ PLAYING ", buff, 10) == 0) {
                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
                writeToServer(sockfd, playerToSend);
            }

            // step four, read YOU
            // todo, save information from Server here
            if (strncmp("+ YOU", buff, 5) == 0) {
            }

            // step five, read board information and time to move from server.
            // todo, extract timeToMove info
            // todo, extract board info
            if (strlen(buff) > 75) {
                writeToServer(sockfd, thinking);
                writeToServer(sockfd, playf5);
            }

            if ((strncmp("+ WAIT", buff, 6)) == 0) {
                writeToServer(sockfd, okWait);
            }

            // todo, add error handling if server playing wrong kind of game
            if ((strncmp("+ Reversi", buff, 10)) == 0) {
                writeToServer(sockfd, playerToSend);
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

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName) {

    haveConversationWithServer(sock, gameID, player, gameKindName);

    printf("performConnection %d\n", sock);

    return 0;
}
