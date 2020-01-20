#include "../thinker/board.h"

#include "connector.h"
#include "performConnection.c"
#include "config.h"

#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>

#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>

#include "boardmessageparser.h"

#define GAMEKINDNAME "Reversi"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"
#define DEFAULT_FILE_PATH "client.conf"
#define ADDR_STR_LEN 100

int getDefaultPort() {
    return PORTNUMBER;
}

int connectToGameServer(char *gameID, char *player,
                        int usingCustomConfigFile, char *filePath, BOARD_STRUCT *connectorBoard,
                        infoVonServer *info, pid_t thinker,
                        pid_t connector, void *shmInfo) {

    configurationStruct *configStruct = malloc(sizeof(configurationStruct));
    configStruct->hostname = calloc(' ', 200);
    configStruct->gamekindname = calloc(' ', 200);

    int failState = 0;

    struct addrinfo hints, *res, *resTemp;
    struct sockaddr_in server;
    server.sin_family = PF_INET;

    char addrstr[ADDR_STR_LEN];
    bzero(addrstr, ADDR_STR_LEN);
    void *ptr;

    int sock = 0, errcode, connectionStatus = 0;

    if (usingCustomConfigFile) {
        printf("### Using custom configuration file: %s\n", filePath);
        readConfigurationFile(filePath, configStruct);
    } else {
        printf("### Using default configuration file: %s\n", DEFAULT_FILE_PATH);
        readConfigurationFile(DEFAULT_FILE_PATH, configStruct);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    errcode = getaddrinfo(configStruct->hostname, NULL, &hints, &res);
    resTemp = res;
    while (resTemp) {

        if (!resTemp->ai_family) {
            break;
        }

        switch (resTemp->ai_family) {
            case AF_INET:
                ptr = &((struct sockaddr_in *) resTemp->ai_addr)->sin_addr;
                sock = socket(AF_INET, SOCK_STREAM, 0);
                break;
            case AF_INET6:
                sock = socket(AF_INET6, SOCK_STREAM, 0);
                ptr = &((struct sockaddr_in6 *) resTemp->ai_addr)->sin6_addr;
                break;
        }

        // error handling for socket
        if (sock == -1) {
            printf("### Could not create Socket\n");
            continue;
        } else {
            printf("### Created Socket\n");
        }

        inet_ntop(resTemp->ai_family, ptr, addrstr, ADDR_STR_LEN);
        printf("### IPv%d address: %s (%s)\n", resTemp->ai_family == PF_INET6 ? 6 : 4,
               addrstr, resTemp->ai_canonname);

        if (strlen(addrstr) == 0) {
            fprintf(stderr, "### ERROR, no host found\n");
            close(sock);
            break;
        }

        printf("### Attempting to connect to host %s on port %d\n", addrstr,
               configStruct->portnumber);
        server.sin_addr.s_addr = inet_addr(addrstr);

        server.sin_port = htons(PORTNUMBER);

        // connect the client socket to the server socket
        if (connect(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
            printf("### connection with the server failed... error is %s\n",
                   strerror(errno));
        } else {


            printf("### Success, connected to the server.\n");


            printf("### Connecting socket fd to epoll instance\n");




            event.events = EPOLLIN ;
            event.data.fd = sock;

            int xxx = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock, &event);
            if(xxx)
            {
                printf("### epoll failed ... error is %s\n",
                       strerror(errno));

                fprintf(stderr, "### Failed to add file descriptor to epoll, %d\n", xxx);
                failState = 1;
                break;
            } else {
                printf("### correctly registered epoll to pipe\n");
            }






            connectionStatus = haveConversationWithServer(sock, gameID, player,
                                                      configStruct->gamekindname, connectorBoard, info, thinker,
                                                      connector, shmInfo);
            break;
        }

        close(sock);
        resTemp = resTemp->ai_next;
    }

    freeaddrinfo(res);

    free(configStruct->gamekindname);
    free(configStruct->hostname);
    free(configStruct);

    return connectionStatus + failState;
}

int connectorMasterMethod(BOARD_STRUCT *connectorBoard, int argc, char *argv[], infoVonServer *info, pid_t thinker,
                          pid_t connector, void *shmInfo) {
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
        return 1;
    }

    if (strlen(gameID) > 13) {
        perror("Das Game-ID ist grosser als 13-stellige.\n");
        gameID = NULL;
        return 1;
    }
    int con = connectToGameServer(gameID, player, usingCustomConfigFile,
                                  configPath, connectorBoard, info, thinker, connector, shmInfo);

    if (con) {
        fprintf(stderr, "### Error during connection with server\n");
    } else {
//        printf("Connection with server appears to have gone well\n");
    }
    return con;
}
