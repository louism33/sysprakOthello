//
// Created by louis on 11/13/19.
//
#include "connector.h"
#include "performConnection.c"

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
#include <sys/socket.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>

#define GAMEKINDNAME "Reversi"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"




int connectToGameServer(bool testing) {

    // create
    int sock = socket(AF_INET, SOCK_STREAM, 0);

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

    if (testing) {
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    } else {
        server.sin_addr.s_addr = inet_addr(HOSTNAME);

    }
    server.sin_port = htons(PORTNUMBER);

    // connect the client socket to the server socket
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
        printf("connection with the server failed...\n");
        return 0;
    } else {
        printf("success!!!! connected to the server..\n");
    }


    performConnection(sock);

    close(sock);

    printf("i guess we are done\n");
    return 0;

}


int connectToRealGameServer() {
    return connectToGameServer(false);
}

int connectToMockGameServer() {
//    createMockGameServer();
    return connectToGameServer(true);
}




void connectorMasterMethod(int argc, char *argv[]) {
    printf("Hi I am good at connecting\n");
    char *GAMEID;
    int GAMENUMBER = 0;
    int ret;
    while ((ret = getopt(argc, argv, "g:p:")) != -1) {
        switch (ret) {
            case 'g':
                GAMEID = optarg;
                break;
            case 'p':
                GAMENUMBER = atoi(optarg);
                break;
            default:
                perror("keine gültige Game-ID oder Game-Number.\n");
                break;
        }
    }
    //Fehlerbehandelung
    if (strlen(GAMEID) > 13) {
        perror("Das Game-ID ist grosser als 13-stellige.\n");
        GAMEID = NULL;
        exit(0);
    } else if (strlen(GAMEID) < 13) {
        perror("Das Game-ID ist kleiner als 13-stellige.\n");
        GAMEID = NULL;
        exit(0);
    }


    connectToMockGameServer();
}






