//
// Created by louis on 11/13/19.
//
#include "connector.h"
#include "performConnection.c"
#include "mockgameserver.h"

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

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


#define GAMEKINDNAME "Reversi"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"

char *lookup_host(const char *host) { // todo move sock creation to here?

    struct addrinfo hints, *res;
    int errcode;
    char addrstr[100];
    char *finalAddrstr;
    void *ptr;

    finalAddrstr = malloc(sizeof(char) * 200); // todo clean this memory in calling function

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    errcode = getaddrinfo(host, NULL, &hints, &res);
    if (errcode != 0) {
        perror("getaddrinfo");
        return "x";
    }

    printf("Host: %s\n", host);
    while (res) {
        inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

//        printf("addrstr:    %s \n", addrstr);

        switch (res->ai_family) {
            case AF_INET:
                ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
                break;
            case AF_INET6:
                ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
                break;
        }
        inet_ntop(res->ai_family, ptr, addrstr, 100);
        printf("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
               addrstr, res->ai_canonname);

        if (res->ai_family != PF_INET6) {
            strcpy(finalAddrstr, addrstr);
            return finalAddrstr;
        }
        res = res->ai_next;
    }

    return finalAddrstr;

}


int connectToGameServer(int mockGame, char *gameID, char* player) {
    printf("attempting to connect to game server.\n");

    if (mockGame) {
        printf("MOCK GAME IS TRUE\n");
    } else {
        printf("MOCK GAME IS FALSE\n");
    }

    // create
    int sock = socket(AF_INET, SOCK_STREAM, 0);
//    int sock = socket(AF_INET6, SOCK_STREAM, 0);

    // error handling for socket
    if (sock == -1) {
        printf("Could not create Socket\n");
        return 0;
    } else {
        printf("created Socket\n");
    }

    // set up server information as sockaddr_in
    struct sockaddr_in server;
    server.sin_family = PF_INET;

    if (mockGame) {
        char *local = "127.0.0.1";
        server.sin_addr.s_addr = inet_addr(local);
        printf("Attempting to connect to host %s on port %d\n", local, PORTNUMBER);
    } else {
        char *host = lookup_host(HOSTNAME);

        char *MNMip = "10.155.92.35"; // todo, hack

        printf("Attempting to connect to host %s on port %d\n", host, PORTNUMBER);

        server.sin_addr.s_addr = inet_addr(host);
//        server.sin_addr.s_addr = inet_addr(MNMip);
    }

    server.sin_port = htons(PORTNUMBER);

    // connect the client socket to the server socket
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
        printf("connection with the server failed... error is %s\n", strerror(errno));
        return 0;
    } else {
        printf("success!!!! connected to the server..\n");
    }


    performConnectionLouis(sock, gameID, player);

    close(sock);

    printf("i guess we are done\n");
    return 0;

}



int connectorMasterMethod(int argc, char *argv[]) {
    printf("Hi I am good at connecting\n");

    char *gameID;
    char* player = 0;
    int ret;
    int mockGame = 0;

    while ((ret = getopt(argc, argv, "g:p:m:")) != -1) {
        switch (ret) {
            case 'g':
                gameID = optarg;
                break;
            case 'p':
                player = optarg;
                break;
            case 'm':
                mockGame = 1;
                break;
            default:
                perror("keine gültige Game-ID oder Game-Number.\n");
                break;
        }
    }

    //Fehlerbehandelung
    if (strlen(gameID) > 13) {
        perror("Das Game-ID ist grosser als 13-stellige.\n");
        gameID = NULL;
        exit(0);
    } else if (strlen(gameID) < 13) {
        perror("Das Game-ID ist kleiner als 13-stellige.\n");
        gameID = NULL;
        exit(0);
    }

    if (mockGame) {
        pid_t pid;
        pid = fork();
        if (pid == 0) { /* child process */
            createMockGameServer();
            return 0;
        }

        int sleepMicroSeconds = 2000000;
        printf("sleeping for %d microseconds to give the mock server time to get ready\n", sleepMicroSeconds);
        usleep(sleepMicroSeconds);
    }

    connectToGameServer(mockGame, gameID, player);

    return 0;
}






