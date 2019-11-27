#include "../thinker/board.h"
#include "connector.h"
#include "performConnection.c"
#include "mockgameserver.h"
#include "config.h"

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
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
#define DEFAULT_FILE_PATH "client.conf"

// pieces and SIDE_TO_MOVE constants
#define BLACK 2
#define WHITE 1
#define EMPTY 0



// to flip turn, we do SWITCH_PLAYER_CONSTANT - SIDE_TO_MOVE
//#define SWITCH_PLAYER_CONSTANT (BLACK+WHITE)



char *lookup_host(const char *host, char *finalAddrstr) { // todo move sock creation to here?
    struct addrinfo hints, *res;
    int errcode;
    char addrstr[100];
    void *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    errcode = getaddrinfo(host, NULL, &hints, &res);
    if (errcode != 0) {
        perror("getaddrinfo");
        return 0;
    }

    printf("Host: %s\n", host);
    while (res) {
        inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

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

int connectToGameServer(int mockGame, char *gameID, char *player,
                        int usingCustomConfigFile, char *filePath, BOARD_STRUCT *connectorBoard,
                        BOARD_STRUCT *thinkerBoard) {

    printf("Attempting to connect to game server.\n");

    configurationStruct *configurationStruct;

    if (mockGame) {
        printf("MOCK GAME IS TRUE\n");
    } else {
        printf("MOCK GAME IS FALSE\n");
    }

    // todo consider moving to dns resolution
    // create
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // int sock = socket(AF_INET6, SOCK_STREAM, 0);

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
        printf("Attempting to connect to host %s on port %d\n", local,
               PORTNUMBER);
        configurationStruct = malloc(sizeof(configurationStruct));
        configurationStruct->gamekindname = "REVERSI";

    } else {
        char host[150];

        if (usingCustomConfigFile) {
            printf("Using custom configuration file: %s\n", filePath);
        } else {
            printf("Using default configuration file: %s\n", DEFAULT_FILE_PATH);
        }

        configurationStruct =
                usingCustomConfigFile ?
                readConfigurationFile(filePath) :
                readConfigurationFile(DEFAULT_FILE_PATH);

        char *finalAddrstr = malloc(sizeof(char) * 200);
        finalAddrstr = lookup_host(configurationStruct->hostname, finalAddrstr);

        if (finalAddrstr) {
            strcpy(host, lookup_host(configurationStruct->hostname, finalAddrstr));
        } else {
            strcpy(host, "10.155.92.35");
        }

        free(finalAddrstr);

        if (strlen(host) == 0) {
            printf("ERROR, no host found\n");
            exit(1);
        }

        printf("Attempting to connect to host %s on port %d\n", host,
               configurationStruct->portnumber);
        server.sin_addr.s_addr = inet_addr(host);
    }

    server.sin_port = htons(PORTNUMBER);

    // connect the client socket to the server socket
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
        printf("connection with the server failed... error is %s\n",
               strerror(errno));
        return 0;
    } else {
        printf("success!!!! connected to the server..\n");
    }

    performConnectionLouis(sock, gameID, player,
                           configurationStruct->gamekindname, connectorBoard, thinkerBoard);

    free(configurationStruct->gamekindname);
    free(configurationStruct->hostname);
    free(configurationStruct);
    close(sock);

    printf("i guess we are done\n");
    return 0;
}

int connectorMasterMethod(BOARD_STRUCT *connectorBoard, BOARD_STRUCT *thinkerBoard, int argc, char *argv[]) {
    printf("Hi I am good at connecting\n");
//	char *configFromEnvironment = getenv("CONFIG_FILE");
//	printf("     config file is %s \n", configFromEnvironment);

    char *gameID;
    char *player = 0;
    int ret;
    int mockGame = 0;
    int usingCustomConfigFile = 0;
    char *configPath;

    while ((ret = getopt(argc, argv, "g:p:m:C:")) != -1) {
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
            case 'C':
//			if (!configFromEnvironment) {
//				printf(
//						"Could not read config file from option, defaulting to client.conf\n");
//				break;
//			}
                configPath = optarg;
                usingCustomConfigFile = 1;
                break;
            default:
                printf("Could not read provided option %c\n", ret);
                perror("Could not read provided option.\n");
                return 1;
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
        exit(1);
    }
    // todo, what if player is blank?

    if (mockGame) {
        pid_t pid;
        pid = fork();
        if (pid == 0) { /* child process */
            createMockGameServer();
            return 0;
        }

        int sleepMicroSeconds = 2000000;
        printf("sleeping for %d microseconds to give the mock server time to get ready\n",
               sleepMicroSeconds);
        usleep(sleepMicroSeconds);
    }

    connectToGameServer(mockGame, gameID, player, usingCustomConfigFile,
                        configPath, connectorBoard, thinkerBoard);

    return 0;
}

void performConnection() {

}
