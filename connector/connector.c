//
// Created by louis on 11/13/19.
//
#include "connector.h"
#include "performConnection.c"


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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


#define GAMEKINDNAME "Reversi"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"

char * lookup_host (const char *host) { // todo move sock creation to here?

    struct addrinfo hints, *res;
    int errcode;
    char addrstr[100];
    char* finalAddrstr;
    void *ptr;

    finalAddrstr = malloc(sizeof(char) * 200); // todo clean this memory in calling function

    memset (&hints, 0, sizeof (hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    errcode = getaddrinfo (host, NULL, &hints, &res);
    if (errcode != 0)
    {
        perror ("getaddrinfo");
        return "x";
    }

    printf ("Host: %s\n", host);
    while (res)
    {
        inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, 100);

//        printf("addrstr:    %s \n", addrstr);

        switch (res->ai_family)
        {
            case AF_INET:
                ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
                break;
            case AF_INET6:
                ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
                break;
        }
        inet_ntop (res->ai_family, ptr, addrstr, 100);
        printf ("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
                addrstr, res->ai_canonname);

        if (res->ai_family != PF_INET6) {
            strcpy(finalAddrstr, addrstr);
            return finalAddrstr;
        }
        res = res->ai_next;
    }

    return finalAddrstr;

//    return "";
}


int connectToGameServer(int mockGame) {

    printf("attempting to connect to game server.\n");
    if (mockGame) {
        printf("MOCK GAME is TRUE\n");
    }else {
        printf("MOCK GAME is FALSE\n");
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
//        char *local = "127.0.0.1";
        char *local = "10.155.92.35"; // todo, hack
        server.sin_addr.s_addr = inet_addr(local);
        printf("Attempting to connect to host %s on port %d\n", local, PORTNUMBER);

    } else {
//        char *localh = "www.cnn.com";

        char *host = lookup_host(HOSTNAME);

        printf("Attempting to connect to host %s on port %d\n", host, PORTNUMBER);

        server.sin_addr.s_addr = inet_addr(HOSTNAME);
    }

    server.sin_port = htons(PORTNUMBER);

    // connect the client socket to the server socket
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
        printf("connection with the server failed... error is %s\n", strerror(errno));
        return 0;
    } else {
        printf("success!!!! connected to the server..\n");
    }


    performConnectionLouis(sock);

    close(sock);

    printf("i guess we are done\n");
    return 0;

}


// to get a mock game (don't use MNM server) please write:
// ./sysprak-client -m 1 -g 1234567890123 -p 1
int connectorMasterMethod(int argc, char *argv[]) {
    printf("Hi I am good at connecting\n");
    char *GAMEID;
    int GAMENUMBER = 0;
    int ret;
    int mockGame = 0;
    while ((ret = getopt(argc, argv, "g:p:m:")) != -1) {
        switch (ret) {
            case 'g':
                GAMEID = optarg;
                break;
            case 'p':
                GAMENUMBER = atoi(optarg);
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
    if (strlen(GAMEID) > 13) {
        perror("Das Game-ID ist grosser als 13-stellige.\n");
        GAMEID = NULL;
        exit(0);
    } else if (strlen(GAMEID) < 13) {
        perror("Das Game-ID ist kleiner als 13-stellige.\n");
        GAMEID = NULL;
        exit(0);
    }


    connectToGameServer(mockGame);

    return 0;
}






