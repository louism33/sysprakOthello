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


return 0;}
*/


void haveConversationWithServer(int sockfd) {
char buff[MAX];
    int n,readResponse = 0;
    char serverbuff[MAX];
    char version[] = "VERSION 2.3";
    char gameid[] = "ID 1234567890123";
    char player[] = "PLAYER";

    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));//读取来自服务器的内容
    printf("%s", buff);//打印出服务器的输出的内容

    for (;;) {
        if ((readResponse = read(sockfd, buff, sizeof(buff)))) {
            printf("%s\n", buff);//把从客户端那边接收来的内容打在本地的cmd里

            // sometimes the server sends more than one command. If so, we wait.
            if (strncmp("+ PLAYING ", buff, 10) == 0) {//如果传来的内容是playing，那么应该
//                printf("received, \'%s', waiting\n", buff);
                bzero(buff, sizeof(buff));//首先先清空buff
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
//                printf("received, \'%s', proceeding RR %d\n", buff, readResponse);
                printf("%s\n", buff);
            }
            if (strncmp("+ YOU", buff, 5) == 0) {
//                printf("received, \'%s', waiting\n", buff);
                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) && strlen(buff) < 1);
//                printf("received, \'%s', proceeding\n", buff);
                printf("%s\n", buff);
            }
        }
        bzero(buff, sizeof(buff));
    // you can manually talk to the server here
    int count=0;
    if(readResponse=read(sockfd,serverbuff,sizeof(serverbuff))){
        if(strncmp("+ MNM Gameserver",serverbuff,16) == 0){
                count = 1;
            }else if(strncmp("+ Client version accepted",serverbuff,25) == 0){
                count = 2;
            }else if(strncmp("+ REVERSI",serverbuff,10) == 0){
                count = 3;}
    }
     switch(count){
         case 1:
         strcpy(buff,version);
         break;
         case 2:
         strcpy(buff,"ID 1234567890123");
         break;
         case 3:
         strcpy(buff,"PLAYER");
         break;
         default:
         bzero(buff,sizeof(buff));
         break;
         }
    write(sockfd, buff, sizeof(buff));
    printf("%s\n",buff);
    bzero(buff, sizeof(buff));
    bzero(serverbuff,sizeof(serverbuff));
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