#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


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


#define MAX 300


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
        char *version_msg = mystrcat(version,daten);
        return version_msg;
    }

    if (idikator == 2) {
        char *id_msg = mystrcat(id,daten);
        return id_msg;
    }

    if (idikator == 3) {
        char *player_msg = player;
        return player_msg;
    }

    return NULL;
}


/*int performConnection(int sockfd) {
    char version[MAX];
    char id[MAX];
    int n = 0;
    char *version_msg = createinfo(1, version);//VERSION XXX
    char *id_msg = createinfo(2, id);//ID XXX
    char *player_msg = createinfo(3, NULL);//PLAYER

    while(version[n++] = getchar() != '\n');
    write(sockfd,version_msg,sizeof(version_msg));
    read(sockfd,version_msg,sizeof(version_msg));
    printf("%s",version_msg);
    while(id[n++] = getchar() != '\n');
    write(sockfd,id_msg,sizeof(id_msg));
    read(sockfd,id_msg,sizeof(id_msg));
    printf("%s",id_msg);

    printf("%s",player_msg);

return 0;}
*/


void haveConversationWithServer(int sockfd) {
char buff[MAX];
    int n,readResponse = 0;

    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("%s", buff);

    for (;;) {
        if ((readResponse = read(sockfd, buff, sizeof(buff)))) {
            printf("%s\n", buff);

            // sometimes the server sends more than one command. If so, we wait.
            if (strncmp("+ PLAYING ", buff, 10) == 0) {
//                printf("received, \'%s', waiting\n", buff);
                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
//                printf("received, \'%s', proceeding RR %d\n", buff, readResponse);
                printf("%s\n", buff);
            }
            if (strncmp("+ YOU", buff, 6) == 0) {
//                printf("received, \'%s', waiting\n", buff);
                bzero(buff, sizeof(buff));
                readResponse = read(sockfd, buff, sizeof(buff));
//                printf("received, \'%s', proceeding\n", buff);
                printf("%s\n", buff);
            }
        }
        bzero(buff, sizeof(buff));
        n = 0;
    // you can manually talk to the server here
        while ((buff[n++] = getchar()) != '\n'); // todo! replace this line with our own communication

        write(sockfd, buff, sizeof(buff));

        bzero(buff, sizeof(buff));

        readResponse = read(sockfd, buff, sizeof(buff));

        printf("%s\n", buff);

        if (readResponse == -1) {
            printf("Could not read from server");
            exit(0);
        }

        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int performConnectionLouis(int sock) {

    haveConversationWithServer(sock);

    printf("performConnection %d\n", sock);

    return 0;
}