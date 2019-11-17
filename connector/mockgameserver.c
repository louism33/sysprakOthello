//
// Created by louis on 11/14/19.
//

#include "mockgameserver.h"

#include <errno.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h>
#include <unistd.h>

#define MAX 300
#define PORTNUMBER 1357
#define SA struct sockaddr


int waitLoop(int sockfd){
    char buff[MAX];
    for (int i = 0; i < 10; i++) {
        bzero(buff, MAX);
        strncpy(buff, "+ WAIT", 10);
        write(sockfd, buff, sizeof(buff));

        read(sockfd, buff, sizeof(buff));

        if (strncmp("OKWAIT", buff, 6) != 0) {
            fprintf(stderr, "MOCKGAMESERVER: INCORRECT WAIT RESPONSE\n");
            fprintf(stderr, "You sent %s\n", buff);
            fprintf(stderr, "Server will exit...\n");
            bzero(buff, MAX);
            return -1;
        }
    }
}


// Function designed for chat between client and server.
int dummyInteraction(int sockfd) {
    char buff[MAX];

    int playingAgainstAnAI = 0;

    fprintf(stderr, "\n");

    // version
    bzero(buff, MAX);
    strncpy(buff, "+ MNM Gameserver v2.666 accepting connections", 50);
    write(sockfd, buff, sizeof(buff));//将内容写给客户端

    read(sockfd, buff, sizeof(buff));//从客户端读取内容

    if (strncmp("VERSION 2.", buff, 10) != 0) {//检验客户端的内容
        fprintf(stderr, "MOCKGAMESERVER: INCORRECT VERSION RESPONSE\n");
        fprintf(stderr, "You sent %s\n", buff);
        fprintf(stderr, "Server will exit...\n");
        bzero(buff, MAX);
        return -1;
    }
//    fprintf(stderr, "You correctly sent version information!\n");

    // game ID
    bzero(buff, MAX);
    strncpy(buff, "+ Client version accepted - please send Game-ID to join", 120);
    write(sockfd, buff, sizeof(buff));//写给客户端
    bzero(buff, MAX);

    read(sockfd, buff, sizeof(buff));

//    fprintf(stderr, "MOCKGAMESERVER: From client, I read: %s\n: ", buff);

    if (strncmp("ID ", buff, 3) != 0 || strlen(buff) != 17) {
        fprintf(stderr, "MOCKGAMESERVER: INCORRECT ID RESPONSE\n");
        fprintf(stderr, "You sent %s\n", buff);
        fprintf(stderr, "Server will exit...\n");
        bzero(buff, MAX);
        return -1;
    }

//    fprintf(stderr, "You correctly sent an ID of correct length!\n");



    // gamekind name
    bzero(buff, MAX);
    strncpy(buff, "+ PLAYING REVERSI", 120);
    write(sockfd, buff, sizeof(buff));
    bzero(buff, MAX);

    usleep(100000);

    strncpy(buff, "+ GAME-NAME", 120);
//    fprintf(stderr, "        %s\n", buff);
    write(sockfd, buff, sizeof(buff));
//    fprintf(stderr, "        wrote\n");
    bzero(buff, MAX);

    read(sockfd, buff, sizeof(buff));

    fprintf(stderr, "MOCKGAMESERVER: From client, I read: %s\n: ", buff);

    if (strncmp("PLAYER ", buff, 7) == 0) {
        fprintf(stderr, "MOCKGAMESERVER: you want to play against a specific player!\n");
        playingAgainstAnAI = 0;
    } else if (strncmp("PLAYER", buff, 6) == 0) {
        fprintf(stderr, "MOCKGAMESERVER: you want to play against an AI!\n");
        playingAgainstAnAI = 1;
    } else {
        fprintf(stderr, "MOCKGAMESERVER: INCORRECT PLAYER RESPONSE\n");
        fprintf(stderr, "You sent %s\n", buff);
        fprintf(stderr, "Server will exit...\n");
        bzero(buff, MAX);
        return -1;
    }


    // player info
    bzero(buff, MAX);
    strncpy(buff, "+ YOU 1 ALEX", 120);
    write(sockfd, buff, sizeof(buff));
    bzero(buff, MAX);

    usleep(100000);

    strncpy(buff, "+ TOTAL 2", 120);
    write(sockfd, buff, sizeof(buff));
    bzero(buff, MAX);


//    waitLoop(sockfd);


    fprintf(stderr, "\nYou got to the end of the mock server, congrats\n");

    return 0;
}




int createMockGameServer() {
    int sockfd, connfd;
    unsigned int len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("MOCKGAMESERVER: socket creation failed...\n");
        exit(0);
    } else {
        printf("MOCKGAMESERVER: Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORTNUMBER);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) != 0) {
        printf("MOCKGAMESERVER: socket bind failed... error is %s\n", strerror(errno));
        exit(0);
    } else
        printf("MOCKGAMESERVER: Socket successfully bound..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("MOCKGAMESERVER: Listen failed...\n");
        exit(0);
    } else {
        printf("MOCKGAMESERVER: Server listening..\n");
    }

    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr *) &cli, &len);
    if (connfd < 0) {
        printf("MOCKGAMESERVER: server acccept failed...\n");
        exit(0);
    } else {
        printf("MOCKGAMESERVER: server acccepts the client...\n");
    }

    // Function for chatting between client and server
    int i = dummyInteraction(connfd);

    if (i != 0) {
        printf("YOU HAVE FAILED IN YOUR INTERACTION WITH MOCK GAME SERVER.\n");
    }
    // After chatting close the socket
    close(sockfd);

    return 0;
}

