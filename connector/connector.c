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

int getDefaultPort() {
    return PORTNUMBER;
}

int connectToGameServer(int mockGame, char *gameID, char *player,
                        int usingCustomConfigFile, char *filePath, BOARD_STRUCT *connectorBoard,
                        BOARD_STRUCT *thinkerBoard) {

    configurationStruct *configStruct = malloc(sizeof(configurationStruct));
    configStruct->hostname = calloc(' ', 200);
    configStruct->gamekindname = calloc(' ', 200);

    struct addrinfo hints, *res;
    struct sockaddr_in server;
    server.sin_family = PF_INET;

    char  addrstr[100];
    void *ptr;

    int sock = 0, errcode;

    if (usingCustomConfigFile) {
        printf("Using custom configuration file: %s\n", filePath);
        readConfigurationFile(filePath, configStruct);
    } else {
        printf("Using default configuration file: %s\n", DEFAULT_FILE_PATH);
        readConfigurationFile(DEFAULT_FILE_PATH, configStruct);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    errcode = getaddrinfo(configStruct->hostname, NULL, &hints, &res);

    while (errcode != 0 && res) {
        switch (res->ai_family) {
            case AF_INET:
                ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
                sock = socket(AF_INET, SOCK_STREAM, 0);
                break;
            case AF_INET6:
                sock = socket(AF_INET6, SOCK_STREAM, 0);
                ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
                break;
        }

        // error handling for socket
        if (sock == -1) {
            printf("Could not create Socket\n");
            continue;
        } else {
            printf("created Socket\n");
        }

        inet_ntop(res->ai_family, ptr, addrstr, 100);
        printf("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
               addrstr, res->ai_canonname);

        if (res->ai_family != PF_INET6) {
            if (strlen(addrstr) == 0) {
                printf("ERROR, no host found\n");

                freeaddrinfo(res);
                free(configStruct->gamekindname);
                free(configStruct->hostname);
                free(configStruct);
                return 1;
            }

            printf("Attempting to connect to host %s on port %d\n", addrstr,
                   configStruct->portnumber);
            server.sin_addr.s_addr = inet_addr(addrstr);

            server.sin_port = htons(PORTNUMBER);

            // connect the client socket to the server socket
            if (connect(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
                printf("connection with the server failed... error is %s\n",
                       strerror(errno));
                continue;
            } else {
                printf("success!!!! connected to the server..\n");
            }

//            performConnectionLouis(sock, gameID, player,
//                                   configStruct->gamekindname, connectorBoard, thinkerBoard);


            break;
        }

        close(sock);
        res = res->ai_next;
    }


    close(sock);

    freeaddrinfo(res);

    free(configStruct->gamekindname);
    free(configStruct->hostname);
    free(configStruct);

    printf("i guess we are done\n");
    return 0;
}

int connectorMasterMethod(BOARD_STRUCT *connectorBoard, BOARD_STRUCT *thinkerBoard, int argc, char *argv[]) {
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
    if (!gameID || strlen(gameID) < 13) {
        perror("Das Game-ID ist kleiner als 13-stellige.\n");
        gameID = NULL;
        exit(1);
    }

    if (strlen(gameID) > 13) {
        perror("Das Game-ID ist grosser als 13-stellige.\n");
        gameID = NULL;
        exit(0);
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


//    int doConnectResult = doConnect(0, NULL, mockGame, gameID, player,
//                                    usingCustomConfigFile, configPath, connectorBoard,
//                                    thinkerBoard);

    connectToGameServer(mockGame, gameID, player, usingCustomConfigFile,
                        configPath, connectorBoard, thinkerBoard);
//
    return 0;
}

void performConnection() {

}
