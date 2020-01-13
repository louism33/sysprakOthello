#include "../thinker/board.h"

#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "connector.h"
#include "boardmessageparser.h"
#include "performConnection.h"
#include "../thinker/thinker.h"
#include "../main.h"
#include "../shm/shm.h"

#define MAX 240 // todo make better
#define MAJOR_VERSION_INDEX_LOCAL 8
#define MAJOR_VERSION_INDEX_SERVER 18
#define MOVE_STRING_LENGTH 10
#define SMALL_STRING 32
#define BIG_STRING 64

bool schreiben = false;

int printMore = 1;

enum Phase {
    PROLOG = 0,
    SPIELVERLAUF = 1,
    SPIELZUG = 2
};

int writeToServer(int sockfd, char message[]) {
    write(sockfd, message, strlen(message));
    if (printMore) {
        printf("<------US:\n%s", message);
    }
    return 0;
}

char *convertMove(int move, char *antwort) {
    antwort[0] = 'A' + (move % 8);     //spalte
    antwort[1] = '0' + (8 - move / 8); //zeile
    antwort[2] = '\0';
    return antwort;
}

int getWinnerFromServer(char *buff) {
    char *black;
    char *white;
    black = strstr(buff, "+ PLAYER0WON Yes");
    white = strstr(buff, "+ PLAYER1WON Yes");

    if (black != 0 && white != 0) {
        printf("### Draw! \n");
        return getDraw();
    } else if (black != 0) {
        printf("### BLACK wins!\n");
        return getBlack();
    } else if (white != 0) {
        printf("### WHITE wins!\n");
        return getWhite();
    } else {
        fprintf(stderr, "### Failed to meaningfully parse gameover string, no idea who won \n");
        return -1;
    }
}

// return 1 if fail, 0 if success
int dealWithGameOverCommand(char *buff) {
    printf("### The game is over.\n");

    int fail = 0;

    int winner = getWinnerFromServer(buff);

    if (winner == -1) {
        fail = 1;
    }

    return fail;
}

int getMoveTime(char *buff) {
    char move[10] = {" "};
    int len = strlen(buff);
    int i = 7, j = 0;
    while (i < len && (buff[i] >= '0' && buff[i] <= '9')) {
        move[j++] = buff[i++];
    }

    int mvTime = atoi(move);
    printf("### Parsed move time of %d\n", mvTime);
    return mvTime;
}


int getMoveTimeAndFieldSize(char *buff, char *moveTime, char *fieldSize) {
    char *moveString;
    char move[20] = {" "};
    int moveTimeNummer;
    char *fieldString;
    char field[20] = {" "};
    int fieldSizeNummer = 0;
    moveString = strstr(buff, "+ MOVE");
    fieldString = strstr(buff, "FIELD");
    int i = 0;
    unsigned int indexOfMove = 0;
    unsigned int indexOfMoveTime = 0;
    int j = 0;
    unsigned int indexOfField = 0;
    unsigned int indexOfFieldSize = 0;

    int moveTimeRet = 0;
    if (moveString != NULL) {
        moveTimeRet = getMoveTime(moveString);
    }

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
    fieldSize[indexOfFieldSize] = '\0';

    return moveTimeRet;
}


FieldSizeColumnAndRow charInNummer(char *fieldSize) {
//    printf("### Parsing field size message: %s\n", fieldSize);
    char firstPart[MOVE_STRING_LENGTH] = {" "};
    char secondPart[MOVE_STRING_LENGTH] = {" "};
    int index = 0;
    unsigned int komma = 0;
    int num1 = 0;
    int num2 = 0;
    unsigned int indexNew = 0;
    FieldSizeColumnAndRow f;

    while (1) {
        if (fieldSize[index] == ',') // wenn Komma gibt
        {
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

int hasLineBreak(char *str, int len, int startIndex) {
    for (int i = startIndex; i < len; i++) {
        if (str[i] == '\n') {
            return i;
        }
    }
    return -1;
}

char myInternalBuffer[1024];
//
//// select? epoll?
//int readNextLine(int socket, char *buffer) {
//
//    // read next line until there is nothing in buff, then read sock?
//
////    int bytesRead = 0;
////    int result = 0;
////
////    int x = sizeof(myInternalBuffer);
////    int lineBreak = 0;
////    printf("---------------------------  x: %d\n", x);
////
////    int i = 0;
////
////    while (1) {
//
////        if (i > 0){
////            printf("                                                         in the loop again %d\n", i);
////        }
////        i++;
//
//
////        result = read(socket, myInternalBuffer + bytesRead, x - bytesRead);
//    int readResponse;
//
//    if (readResponse = read(socket, buffer, sizeof(buffer))) {
//        return readResponse;
//    }
//
//    if (1) {
//        return readResponse;
//    }
//
////        if (result < 1) {
////            // Throw your error.
////            printf("ohno\n");
////        }
//
////        bytesRead += result;
//
////        printf("/// myInternalBuffer: %s", myInternalBuffer);
////        printf("/// result: %d\n", result);
//
////        if ((lineBreak = hasLineBreak(myInternalBuffer, result, 0)) != -1) {
////            printf("             /*******************************// result: %d\n", result);
//////            break;
////        }
//
////        break;
////    }
//
////    strncpy(buffer, myInternalBuffer, x);
//
////    printf("//////          buffer: %s", buffer);
////    printf("////// myInternalBuffer: %s", myInternalBuffer);
////    printf("////// bytesRead: %d\n", bytesRead);
//
////    bzero(myInternalBuffer, x);
//
////    printf("             /*************************     ******// result: %d, bytesRead %d\n", result, bytesRead);
//
////    return bytesRead;
//    return readResponse;
//}



// select? epoll?
int readNextLine(int socket, char *buffer) {

    int readResponse;

    if (readResponse = read(socket, buffer, sizeof(buffer))) {
        return readResponse;
    }

    exit(19);
//    return readResponse;
}

int haveConversationWithServer(int sockfd, char *gameID, char *player, char *gameKindName,
                               BOARD_STRUCT *connectorBoard,
                               infoVonServer *info, pid_t thinker, pid_t connector, void *shmInfo) {

    strcpy(info->gameID, gameID);
    info->connector = connector;
    info->thinker = thinker;

    strcpy(info->gameKindName, gameKindName);

    char buff[MAX] = {" "};    // todo pick standard size for everything, and avoid buffer overflow with ex. strncpy
    char okthinkbuff[SMALL_STRING] = {" "};
    char gameName[BIG_STRING] = {0}; // example: Game from 2019-11-18 17:42
    char playerNumber[SMALL_STRING] = {0};
    char myPlayerName[SMALL_STRING] = {0};
    char opponent[SMALL_STRING] = {0};

    int endstate = 0;
    char mitspieleranzahl[SMALL_STRING];
    int n = 0, readResponse = 0;

    char version[] = "VERSION 0.42\n";
    info->majorVersionNr = 2;
    info->minorVersionNr = 42;
    char okWait[] = "OKWAIT\n";

    char gameIdToSend[SMALL_STRING] = {0};
    strcpy(gameIdToSend, "ID ");
    strcat(gameIdToSend, gameID);
    strcat(gameIdToSend, "\n");

    char blankPlayerToSend[] = "PLAYER\n";
    char playerToSend[] = "PLAYER 1\n";
    char thinking[] = "THINKING\n";
    int lengthOfPlayCommandToSendToKeep = 5;
    char moveReceivedFromThinker[3] = {0};
    char *moveReceivedFromThinkerTEMP;
    char gameKindNameFromServer[SMALL_STRING] = {0};
    char playCommandToSend[MOVE_STRING_LENGTH] = {0};


    char *moveTime = malloc(SMALL_STRING * sizeof(char));
    char *fieldSize = malloc(SMALL_STRING * sizeof(char));


    if (player != NULL && strlen(player) == 1) {
        if (player[0] == '1') {
            player[0] = '0';
        } else if (player[0] == '2') {
            player[0] = '1';
        }
    }

    SIDE_TO_MOVE sideToMove;

    // this can be used to make sure we do not get confused about what stage of the game we are in
    enum Phase phase = PROLOG;

    moveTimeAndBoard *mTB = malloc(sizeof(moveTimeAndBoard));

    mTB->movetime = 0;
    mTB->board = NULL;

    info->infoBoard = NULL;

    if (!gameKindName) {
        fprintf(stderr, "### Game kind name not provided, exiting");
        endstate = 1;
    }

    char buffer[BIG_STRING]; // Puffer zum speichern von gelesenen Daten
    int mvTime = 0;

    for (; endstate == 0;) {
//        if ((readResponse = read(sockfd, buff, sizeof(buff)))) {
        if ((readResponse = readNextLine(sockfd, buff))) {


            // todo dont print the stuff for server, make everything pretty
            if (printMore) {
                printf("------>SERVER:\n%s", buff);
                fflush(stdout);
            }

            if ((strncmp("- TIMEOUT Be faster next time", buff, 29)) == 0) {
                fprintf(stderr, "### We were too slow!\n");
                // todo make sure we are actually ending everything (sigusr2)
                if (kill(thinker, SIGUSR2) == -1) {
                    fprintf(stderr, "### Fehler beim senden des Signals für Game over\n");
                    exit(1);
                } else {
                    printf("### Sending SIGUSR2 to thinker to signal the game is over, due to timeout\n");
                }

                endstate = 1;
                break;
            }

            if ((strncmp("- Internal error. Sorry & Bye", buff, 29)) == 0) {
                fprintf(stderr, "Server screwed up (well, probably we did, but now we can blame the server)\n");
                endstate = 1;
                break;
            }

            if ((strncmp("- No free player", buff, 16)) == 0) {
                fprintf(stderr,
                        "### Could not connect to game, the player is already taken, or there are no free players.\n");
                endstate = 1;
                break;
            }

            if ((strncmp("- Invalid Move: Invalid position", buff, 32)) == 0) {
                fprintf(stderr,
                        "### We seem to have made an invalid move :(. Maybe we thought the wrong colour was playing?.\n");
                endstate = 1;
                break;
            }

            if ((strncmp("- ", buff, 2)) == 0) {
                fprintf(stderr, "### Unknown Server error response! '%s'\n", buff);
                endstate = 1;
                break;
            }

            // step one, send VERSION 2.xxx
            if ((strncmp("+ MNM Gameserver", buff, 16)) == 0) {
                info->majorVersionNr = buff[MAJOR_VERSION_INDEX_SERVER];
                printf("### Gameserver major version is: %c\n", buff[MAJOR_VERSION_INDEX_SERVER]);
                version[MAJOR_VERSION_INDEX_LOCAL] = buff[MAJOR_VERSION_INDEX_SERVER];
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
                    printf("### The server will play Reversi\n");
                } else {
                    printf("### The server is not set up to play Reversi, exiting...\n");
                    endstate = 1;
                    break;
                }

                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) &&
                       strlen(buff) < 1);
                if (printMore) {
                    printf("------>Server:\n%s", buff);
                    fflush(stdout);
                }
                strncpy(gameName, buff + 2, strlen(buff) - strlen("+ "));
                gameName[strlen(buff) - strlen("+ ")] = '\0';
                strcpy(info->gameName, gameName);
                if (printMore) {
                    printf("### Saving gameName: %s", gameName);
                    fflush(stdout);
                }

                if (player == NULL || strlen(player) != 1) {
                    printf("### Connecting with blank player string: %s", blankPlayerToSend);
                    fflush(stdout);
                    writeToServer(sockfd, blankPlayerToSend);
                } else {
                    strcpy(playerToSend, "PLAYER ");
                    playerToSend[7] = player[0];
                    printf("### Connecting with player string: %s", playerToSend);
                    fflush(stdout);
                    writeToServer(sockfd, playerToSend);
                }
            }

            // step four, read YOU
            if (strncmp("+ YOU", buff, 5) == 0) {
                strncpy(playerNumber, buff + 6, 1);
                playerNumber[2] = '\0';
                printf("### Saving playerNumber: %s\n", playerNumber);
                // todo!!!!
                // why is players an array?????
                info->players[atoi(playerNumber)].mitspielerNummer = atoi(playerNumber); // this line is not useful

                info->players[atoi(playerNumber)].bereit = true;

                if (playerNumber[0] == '0') {
//                    printf("### Setting player colour to B\n");
                    sideToMove = getBlack();
                } else {
//                    printf("### Setting player colour to W\n");
                    sideToMove = getWhite();
                }

                int l = strlen(buff) - strlen("+ YOU 0 ");
                strncpy(myPlayerName, buff + 8, strlen(buff) - strlen("+ YOU 0 "));
                myPlayerName[l] = '\0';
                printf("### Saving my playerName: %s", myPlayerName);
                fflush(stdout);
                strcpy(info->players[atoi(playerNumber)].mitspielerName, myPlayerName);
                printf("### Saving my MitspielerName: %s", info->players[atoi(playerNumber)].mitspielerName);
                fflush(stdout);
            }

            // step five, read TOTAL
            if (strncmp("+ TOTAL", buff, 7) == 0) {
                strncpy(mitspieleranzahl, buff + 8, 1);
                mitspieleranzahl[1] = '\0';
                info->MitspielerAnzahl = atoi(mitspieleranzahl);
                printf("### Saving MitspielerAnzahl: '%d'\n", info->MitspielerAnzahl);
                phase = SPIELVERLAUF;
            }

            if ((strncmp("+ GAMEOVER", buff, 10)) == 0) {
                phase = PROLOG;
                if (strlen(buff) > 20) {
                    printf("### received gameover and full string, parsing then exiting\n");
                    endstate += dealWithGameOverCommand(buff);
                } else {
                    printf("### received only gameover, waiting for final board\n");

                    while ((readResponse = read(sockfd, buff, sizeof(buff))) &&
                           strlen(buff) < 1);
                    printf("### final full string:\n%s", buff);
                    fflush(stdout);
                    printf("### parsing then exiting\n");
                    endstate += dealWithGameOverCommand(buff);
                }

                if (kill(thinker, SIGUSR2) == -1) {
                    fprintf(stderr, "### Fehler beim senden des Signals für Game over\n");
                    exit(1);
                } else {
                    printf("### Sending SIGUSR2 to thinker to signal the game is over\n");
                }

                endstate = 0;
                break;
            }


            if ((strncmp("+ MOVEOK", buff, 8)) == 0) {
                if (printMore) {
                    printf("### We made a legal move\n");
                }
            }

            if ((strncmp("+ MOVE ", buff, 7)) == 0) {
                mvTime = getMoveTime(buff);
            }

            // step six, read board information and time to move from server.
            // todo, replace all magic numbers
            // todo, read name of opponent
            if (strstr(buff, "+ FIELD ")) {//strlen(buff) > 75) {
                writeToServer(sockfd, thinking);

                while ((readResponse = read(sockfd, okthinkbuff, sizeof(okthinkbuff))) &&
                       strlen(buff) < 1);

                if (printMore) {
                    printf("------>Server:\n%s", okthinkbuff);
                    fflush(stdout);
                }

                phase = SPIELZUG;

                info->infoBoard = shmInfo + sizeof(infoVonServer) + info->MitspielerAnzahl * sizeof(Player);
                info->infoBoard->board = shmInfo + sizeof(infoVonServer)
                                         + info->MitspielerAnzahl * sizeof(Player) +
                                         sizeof(BOARD_STRUCT);

                connectorBoard->sideToMove = sideToMove;

                bzero(moveTime, SMALL_STRING);
                bzero(fieldSize, SMALL_STRING);
//                moveTime[0] = '\0';
//                fieldSize[0] = '\0';
                int mvt = getMoveTimeAndFieldSize(buff, moveTime, fieldSize);
//                printf("### Parsed message, got movetime: %d\n", mvt);
                if (mvt != 0) {
//                    printf("### Setting move time to : %d\n", mvt);
                    mvTime = mvt;
                } else {
//                    printf("### Not changing movetime, it stays at : %d\n", mvTime);
                }

                FieldSizeColumnAndRow fieldsize = charInNummer(fieldSize);

//                printf("### Starting parse board, setting phase to spielzug\n");
                int parse = parseBoardMessage(connectorBoard, mTB, buff);
                if (parse) {
                    fprintf(stderr, "### Problem parsing board message\n");
                }

//                printf("### finished parse board, here is the board I was able to parse:\n");
//                printBoardLouis(connectorBoard);

                schreiben = true; // todo, what is this global doing???

                memcpy(info->infoBoard->board, connectorBoard->board,
                       sizeof(int) * fieldsize.row * fieldsize.col);
                info->infoBoard->sideToMove = connectorBoard->sideToMove;


//                printf("### Move time from server: %d\n", mvTime);


                // mvTime - 500 seems best
//                info->moveTime = mvTime - 700;
//                info->moveTime = mvTime - 1000; // todo, commando param?? and why so high
                info->moveTime = 100;
                // mvTime - 500 seems best



//                printf("### Move time for us: %d\n", info->moveTime);

//                printf("### Finished parse board\n");
//                printf("### Sending relevant info to thinker\n");

                if (kill(thinker, SIGUSR1) == -1) {
                    printf("Fehler beim senden des Signals\n");
                    exit(1);
                } else {
                    printf("### Sending SIGUSR1 to thinker to start thinking\n");
                }


                close(pd[1]);    // Schreibseite schließen

                bzero(buffer, BIG_STRING);
                // Leseseite auslesen (blockiert hier bis Daten vorhanden)
                if (read(pd[0], buffer, sizeof(buffer)) == -1) {
                    perror("read");
                    endstate = 1;
                    break;
                } else {
                    printf("### Read from Pipe: %s\n", buffer);
                }
                moveReceivedFromThinker[0] = buffer[0];
                moveReceivedFromThinker[1] = buffer[1];
                moveReceivedFromThinker[2] = '\0';

                strcpy(playCommandToSend, "PLAY ");
                strcat(playCommandToSend, moveReceivedFromThinker);
                strcat(playCommandToSend, "\n");
                printf("### Play Command To Send: %s", playCommandToSend);
                fflush(stdout);

                writeToServer(sockfd, playCommandToSend);
                phase = SPIELVERLAUF;
                playCommandToSend[0] = '\0';
            }

            if ((strncmp("+ WAIT", buff, 6)) == 0) {
                writeToServer(sockfd, okWait);
            }

            if (readResponse == -1) {
                fprintf(stderr, "### Could not read from server\n");
                endstate = 1;
                break;
            }
            bzero(buff, sizeof(buff));
        }
    }

    free(mTB);
    free(moveTime);
    free(fieldSize);

    return endstate;
}
