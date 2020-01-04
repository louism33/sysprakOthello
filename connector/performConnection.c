#include "../thinker/board.h"
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
#include <signal.h>

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
#include "connector.h"
#include "boardmessageparser.h"
#include "performConnection.h"
#include "../thinker/thinker.h"
#include "../main.h"
#include "../shm/shm.h"

#define MAX 240 // todo make better

bool schreiben = false;

enum Phase {
    PROLOG = 0,
    SPIELVERLAUF = 1,
    SPIELZUG = 2
};

// todo, be careful of people trolling you by calling game "game over", implement PHASE int/enum

int writeToServer(int sockfd, char message[]) {
    write(sockfd, message, strlen(message));
    printf("Sending to server-> %s\n", message);
    return 0;
}

char *convertMove(int move, char *antwort) {
    antwort[0] = 'A' + (move % 8);     //spalte
    antwort[1] = '0' + (8 - move / 8); //zeile
    antwort[2] = '\0';
    return antwort;
}

int dealWithGameOverCommand(char *buff) {
    printf("The game is over.\n");

    char *black;
    char *white;
    black = strstr(buff, "+ PLAYER0WON Yes");
    white = strstr(buff, "+ PLAYER1WON Yes");

    if (black != 0 && white != 0) {
        printf("draw \n");
    } else if (black != 0) {
        printf("black wins \n");
    } else if (white != 0) {
        printf("white wins \n");
    }

    return 0;
}


int getMoveTimeAndFieldSize(char *buff, char *moveTime, char *fieldSize) {
    char *moveString;
    char move[20] = {" "};
    int moveTimeNummer;
    char *fieldString;
    char field[20] = {" "};
    int fieldSizeNummer = 0;
    moveString = strstr(buff, "MOVE");
    fieldString = strstr(buff, "FIELD");
    int i = 0;
    unsigned int indexOfMove = 0;
    unsigned int indexOfMoveTime = 0;
    int j = 0;
    unsigned int indexOfField = 0;
    unsigned int indexOfFieldSize = 0;

    while (moveString[i] != '+') {
        move[i] = moveString[i];
        i++;
    }

    while (indexOfMove <= strlen(move)) {
        if (move[indexOfMove] >= '0' && move[indexOfMove] <= '9') {
            moveTime[indexOfMoveTime] = move[indexOfMove];
            indexOfMoveTime++;
        }
        indexOfMove++;
    }

    moveTime[indexOfMoveTime] = '\0';
    moveTimeNummer = atoi(moveTime);
    //printf("%d\n", moveTimeNummer);

    while (fieldString[j] != '+') {
        field[j] = fieldString[j];
        j++;
    }

    while (indexOfField <= strlen(field)) {
        if ((field[indexOfField] >= '0' && field[indexOfField] <= '9') || field[indexOfField] == ',') {
            fieldSize[indexOfFieldSize] = field[indexOfField];
            indexOfFieldSize++;
        }
        indexOfField++;
    }
    printf("indexOfFieldSize %d\n", indexOfFieldSize);
    fieldSize[indexOfFieldSize] = '\0';

    return moveTimeNummer;
}

FieldSizeColumnAndRow charInNummer(char *fieldSize) {
    char firstPart[10] = {" "};
    char secondPart[10] = {" "};
    int index = 0;
    unsigned int komma = 0;
    int num1 = 0;
    int num2 = 0;
    unsigned int indexNew = 0;
    FieldSizeColumnAndRow f;

    while (1) {
        if (fieldSize[index] == ',') // wenn Komma gibt
        {
            //printf("Es gibt Komma.\n");
            komma = index;
            while (indexNew != komma) {
                firstPart[num1] = fieldSize[indexNew];
                num1++;
                indexNew++;
            }

            while (komma < strlen(fieldSize)) {
                secondPart[num2] = fieldSize[komma + 1];
                num2++;
                komma++;
            }
            index++;
            if (atoi(firstPart) < 0 || atoi(secondPart) < 0) // pruefen, dass kein Nummer < 0 ist!
            {
                f.row = 0;
                f.col = 0;
            } else {
                firstPart[num1] = '\0';
                secondPart[num2] = '\0';
                f.row = atoi(firstPart);
                f.col = atoi(secondPart);
            }
            break;
        } else if (fieldSize[index] == '\0') // bis Ende kein Komma gibt
        {
            f.row = 0;
            f.col = 0;
            break;
        } else {
            index++;
        }
    }
    return f;
}


char *getMoveFromThinker(BOARD_STRUCT *connectorBoard, BOARD_STRUCT *thinkerBoard, int moveTime, char *moveRet) {
    if (moveTime <= 0) {
        fprintf(stderr, "A move time below or equal to zero? Bist du verrückt??? '%d'\n", moveTime);
        return NULL;
    }
    memcpy(thinkerBoard->board, connectorBoard->board, sizeof(int) * 8 * 8);

    thinkerBoard->sideToMove = connectorBoard->sideToMove;

    int move = doThink(thinkerBoard, moveTime);

    printf("move is: %d\n", move);

    if (move == getPassMove()) {
        printf("NO LEGAL MOVES FROM THIS BOARD");
        return NULL;
    }

    convertMove(move, moveRet);

    printf("converted move is: %s\n", moveRet);

    return moveRet;
}

// todo, handle end state, what do we do once game is over?
int
haveConversationWithServer(int sockfd, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           infoVonServer *info, pid_t thinker, pid_t connector, void *shmInfo) {

    strcpy(info->gameID, gameID);
    printf("info.gameId %s\n", info->gameID);
    info->connector = connector;
    info->thinker = thinker;

    strcpy(info->gameKindName, gameKindName);

    char buff[MAX];    // todo pick standard size for everything, and avoid buffer overflow with ex. strncpy
    char gameName[64] = {0}; // example: Game from 2019-11-18 17:42
    char playerNumber[32] = {0};
    char myPlayerName[32] = {0};
    char opponent[32] = {0};

    int endstate = 0;
    char mitspieleranzahl[32];

    int n = 0, readResponse = 0;

    char version[] = "VERSION 2.42\n";
    info->majorVersionNr = 2;
    info->minorVersionNr = 42;
    char okWait[] = "OKWAIT\n";

    char gameIdToSend[20] = {0};
    strcpy(gameIdToSend, "ID ");
    strcat(gameIdToSend, gameID);
    strcat(gameIdToSend, "\n");

    char blankPlayerToSend[] = "PLAYER\n"; // todo get from argument. need extra whitespace if there is a player provided
    char playerToSend[] = "PLAYER 1\n"; // todo get from argument. need extra whitespace if there is a player provided
    char thinking[] = "THINKING\n";
    int lengthOfPlayCommandToSendToKeep = 5;
    char moveReceivedFromThinker[3] = {0};
    char *moveReceivedFromThinkerTEMP;
    char gameKindNameFromServer[32] = {0};
    char playCommandToSend[10] = {0};


    if (player != NULL && strlen(player) != 1) {
        printf("moving player values around\n");
        printf("player: %s\n", player);
        printf("player[0]: %c\n", player[0]);
        if (player[0] == '1') {
            player[0] = '0';
        } else if (player[0] == '2') {
            player[0] = '1';
        }
    }

    SIDE_TO_MOVE sideToMove;

    enum Phase phase = PROLOG; // this can be used to make sure we do not get confused about what stage of the game we are in

    moveTimeAndBoard *mTB = malloc(sizeof(moveTimeAndBoard));

    mTB->movetime = 0;
    mTB->board = NULL;

    if (!gameKindName) {
        printf("game kind name not provided, exiting");
        endstate = 1;
    }

    for (; endstate == 0;) {
        if ((readResponse = read(sockfd, buff, sizeof(buff)))) {
            printf("--->%s\n", buff);

            if ((strncmp("- TIMEOUT Be faster next time", buff, 29)) == 0) {
                fprintf(stderr, "We were too slow! '%s'\n", buff);
                endstate = 1;
                break;
            }

            if ((strncmp("- Internal error. Sorry & Bye", buff, 29)) == 0) {
                fprintf(stderr, "Server screwed up (well, probably we did, but now we can blame the server)'%s'\n",
                        buff);
                endstate = 1;
                break;
            }

            if ((strncmp("- No free player", buff, 16)) == 0) {
                fprintf(stderr,
                        "Could not connect to game, the player is already taken, or there are no free players.\n");
                endstate = 1;
                break;
            }

            if ((strncmp("- ", buff, 2)) == 0) {
                fprintf(stderr, "Unknown Server error response! '%s'\n", buff);
                endstate = 1;
                break;
            }

            // step one, send VERSION 2.xxx
            if ((strncmp("+ MNM Gameserver", buff, 16)) == 0) {
                writeToServer(sockfd, version);
            }

            // step two, send game ID
            if ((strncmp("+ Client version accepted", buff, 25)) == 0) {
                writeToServer(sockfd, gameIdToSend);
            }

            // step three, read PLAYING, wait for another read, then send PLAYER info
            if (strncmp("+ PLAYING ", buff, 10) == 0) {
                strncpy(gameKindNameFromServer, buff + 10, strlen(buff) - strlen("+ PLAYING "));
                if (strncmp(gameKindName, gameKindNameFromServer, 7) == 0) {
                    printf("##### We play reversi now.#####\n");
                } else {
                    printf("##### We don't play reversi now.#####\n");
                    endstate = 1;
                    break;
                }

                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) &&
                       strlen(buff) < 1); // todo, possibly stick to only one central read?
                printf("%s\n", buff);
                strncpy(gameName, buff + 2, strlen(buff) - strlen("+ "));
                gameName[strlen(buff) - strlen("+ ")] = '\0';
                strcpy(info->gameName, gameName);
                printf("-----------save gameName: %s\n", gameName);


                // todo THIS IS TOTALLY FUCKED

                if (player == NULL || strlen(player) != 1) {
                    printf("### -------------> connecting with blank player string:'%s'\n", blankPlayerToSend);
                    writeToServer(sockfd, blankPlayerToSend);
                } else {
                    // todo THIS IS TOTALLY FUCKED
                    // todo THIS IS TOTALLY FUCKED
                    // todo THIS IS TOTALLY FUCKED
                    // todo THIS IS TOTALLY FUCKED
                    strcpy(playerToSend, "PLAYER ");
                    playerToSend[7] = player[0];
                    printf("### -------------> connecting with player string:'%s'\n", playerToSend);
                    writeToServer(sockfd, playerToSend);
                }
            }

            // step four, read YOU
            if (strncmp("+ YOU", buff, 5) == 0) {
                // todo, save information from Server here
                printf("  Received YOU info from server, buff is:%s", buff);
                strncpy(playerNumber, buff + 6, 1);
                playerNumber[2] = '\0';
                printf("--------save  playerNumber: %s\n", playerNumber);
                // this often gets weird crap
                info->players[atoi(playerNumber)].mitspielerNummer = atoi(playerNumber);
                printf("----save mitspielerNummer:%d\n", info->players[atoi(playerNumber)].mitspielerNummer);
                info->players[atoi(playerNumber)].bereit = true;

                if (playerNumber[0] == '0') {
                    sideToMove = getBlack();
                } else {
                    sideToMove = getWhite();
                }

                int l = strlen(buff) - strlen("+ YOU 0 ");
                strncpy(myPlayerName, buff + 8, strlen(buff) - strlen("+ YOU 0 "));
                myPlayerName[l] = '\0';
                printf("--------save my playerName: %s\n", myPlayerName);
                strcpy(info->players[atoi(playerNumber)].mitspielerName, myPlayerName);
                printf("---save mitspielerName:%s\n", info->players[atoi(playerNumber)].mitspielerName);
            }

            // step five, read TOTAL
            if (strncmp("+ TOTAL", buff, 7) == 0) {
                strncpy(mitspieleranzahl, buff + 8, 1);
                mitspieleranzahl[1] = '\0';
                //printf("  Received TOTAL info from server, buff is:%s", buff);
                info->MitspielerAnzahl = atoi(mitspieleranzahl);
                printf("--------save  MitspielerAnzahl: %d\n", info->MitspielerAnzahl);
                phase = SPIELVERLAUF;
            }

            info->infoBoard = shmInfo + sizeof(infoVonServer) + info->MitspielerAnzahl * sizeof(Player);
            info->infoBoard->board =
                    shmInfo + sizeof(infoVonServer) + info->MitspielerAnzahl * sizeof(Player) +
                    sizeof(BOARD_STRUCT);
            //moveTimeAndBoard->movetime=shmInfo + sizeof(infoVonServer) + info->MitspielerAnzahl * sizeof(Player) + sizeof(BOARD_STRUCT)+sizeof(int);
            // printf("sizeof: %p\n",info->infoBoard+40);

            // step six, read board information and time to move from server.
            // todo, extract timeToMove info
            // todo, extract board size
            // todo, replace all magic numbers
            // todo, read name of opponent
            // todo, read Breit 0 or 1 and save Breit. If 0, print "Spieler 1 (Uli) ist noch nicht bereit"
            if (strlen(buff) > 75) { // todo make better (add check for first chars for example)
                printf("sending thinking command\n");
                writeToServer(sockfd, thinking);
                printf("sent thinking command\n");

                printf("starting parse board, setting phase to spielzug\n");
                phase = SPIELZUG;
                int parse = parseBoardMessage(connectorBoard, mTB, buff);
                if (parse) {
                    fprintf(stderr, "Problem parsing board message\n");
                }
                printf("finished parse board, here is the board I was able to parse:\n");
                printBoardLouis(connectorBoard);

                schreiben = true;
                /* ----------------------- fertig mit schreiben des struct infoVonServer und schreiben in SHM ---*/
                /*---------- schreibe in das Shm das gefüllte Struct aus connectorMasterMethod ------------------*/

                memcpy(info->infoBoard->board, connectorBoard->board, sizeof(int) * 8 * 8);
                info->infoBoard->sideToMove = connectorBoard->sideToMove;


                printf("finished parse board\n");
                printf("sending relevant info to thinker\n");
                char *moveRet = malloc(3 * sizeof(char));

                connectorBoard->sideToMove = getBlack(); // todo todo todo!!! get from player or from response or from past response I dont't care
//                connectorBoard->sideToMove = getWhite(); // todo todo todo!!! get from player or from response or from past response I dont't care

                //signal schicken
                if (kill(thinker, SIGUSR1) == -1) {
                    printf("Fehler beim senden des Signals\n");
                    exit(1);
                } else {
                    printf("******************************************kill\n");
                }
                mTB->movetime = 3000; // todo get from server

                moveReceivedFromThinker[0] = moveRet[0];
                close(pd[1]);    // Schreibseite schließen
                char buffer[50]; // Puffer zum speichern von gelesenen Daten
                if (read(pd[0], buffer, sizeof(buffer)) ==
                    -1) { // Leseseite auslesen (blockiert hier bis Daten vorhanden)
                    perror("read");
                    endstate = 1;
                    break;
                } else {
                    printf("Connector(Kindsprozess) bekommt Nachricht von pipe: %s,length of buffer:%li\n\n",
                           buffer, strlen(buffer));
                }
                moveReceivedFromThinker[0] = buffer[0];
                moveReceivedFromThinker[1] = buffer[1];
                moveReceivedFromThinker[2] = '\0';

                free(moveRet);

                strcpy(playCommandToSend, "PLAY ");
                strcat(playCommandToSend, moveReceivedFromThinker);
                strcat(playCommandToSend, "\n");
                printf("playCommandToSend: %s\n", playCommandToSend);

                writeToServer(sockfd, playCommandToSend);
                phase = SPIELVERLAUF;
                playCommandToSend[0] = '\0';
            }

            if ((strncmp("+ WAIT", buff, 6)) == 0) {
                writeToServer(sockfd, okWait);
            }

            if ((strncmp("+ GAMEOVER", buff, 10)) == 0) {
                phase = PROLOG;
                dealWithGameOverCommand(buff);
                endstate = 0;
                break;
            }

            if (readResponse == -1) {
                printf("Could not read from server");
                endstate = 1;
                break;
            }
            bzero(buff, sizeof(buff));
        }
    }

    free(mTB);

    return endstate;
}

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           infoVonServer *info, pid_t thinker, pid_t connector, void *shmInfo) {

    return haveConversationWithServer(sock, gameID, player, gameKindName, connectorBoard, info, thinker, connector,
                                      shmInfo);
}
