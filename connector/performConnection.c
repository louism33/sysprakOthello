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

void haveConversationWithServer(int sockfd, char *gameID, char *playerXXX, char *gameKindName) {
    char buff[MAX];
    int n, readResponse = 0;
    char version[] = "VERSION 2.3\n";
    char okWait[] = "OKWAIT\n";
    char gameid[] = "ID 36uni1vt419yw\n";
    char player[] = "PLAYER\n";
    char thinking[] = "THINKING\n";
    char playf5[] = "PLAY C5\n";


    for (;;) {
        if ((readResponse = read(sockfd, buff, sizeof(buff)))) {
            printf("%s\n", buff);

            if (strlen(buff) > 75) {
//                printf(" !!!!!!!!!!!!!!!!!!!!!!! read endfield from server \n");
                bzero(buff, sizeof(buff));
                strcpy(buff, thinking);
                write(sockfd, buff, strlen(buff));
                printf("%s", buff);

                bzero(buff, sizeof(buff));
                strcpy(buff, playf5);
                write(sockfd, buff, strlen(buff));
                printf("%s", buff);
            }

            if (strncmp("+ PLAYING ", buff, 10) == 0) {
                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
                bzero(buff, sizeof(buff));
                strcpy(buff, player);
                write(sockfd, buff, strlen(buff));
//                printf("%s\n", buff);
            }

            if ((strncmp("+ WAIT", buff, 6)) == 0) {
                bzero(buff, sizeof(buff));
                strcpy(buff, okWait);
                write(sockfd, buff, strlen(buff));
//                printf("%s", buff);
            }

//        }
            if (strncmp("+ YOU", buff, 5) == 0) {

                bzero(buff, sizeof(buff));
//                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
//            printf("%s\n", buff);
            }
//            usleep(20);
            // you can manually talk to the server here
            if ((strncmp("+ MNM Gameserver", buff, 16)) == 0) {
                bzero(buff, sizeof(buff));
                strcpy(buff, version);
                write(sockfd, buff, strlen(buff));
//                printf("%s", buff);
            }
            if ((strncmp("+ Client version accepted", buff, 25)) == 0) {
                bzero(buff, sizeof(buff));
                strcpy(buff, gameid);
                write(sockfd, buff, strlen(buff));
//                printf("%s", buff);
            }

            // todo, add error handling if server playing wrong kind of game
            if ((strncmp("+ Reversi", buff, 10)) == 0) {
                bzero(buff, sizeof(buff));
                strcpy(buff, player);
                write(sockfd, buff, strlen(buff));
//                printf("%s", buff);
            }

            if ((strncmp("+ ENDFIELD", buff, 10)) == 0) {
//                printf(" read endfield from server \n");
                bzero(buff, sizeof(buff));
                strcpy(buff, thinking);
                write(sockfd, buff, strlen(buff));
//                printf("%s", buff);
            }
            if (readResponse == -1) {
                printf("Could not read from server");
                exit(0);
            }

            if ((strncmp(buff, "exit", 4)) == 0) {
                printf("Client Exit...\n");
                break;
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
