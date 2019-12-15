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
#include "../thinker/thinker.h"
#include "../main.h"
#include "../shm/shm.h"

#define MAX 240 // todo make better
#define PLAYER  // todo, still necessary?

bool schreiben = false;

enum Phase
{
    PROLOG = 0,
    SPIELVERLAUF = 1,
    SPIELZUG = 2
};

BOARD_STRUCT *getAktuellesBoard(BOARD_STRUCT *thinkerBoard) {
    return thinkerBoard;
}

//Die Prolog-Phase der Kommunikation
// todo, reconnect logic
// todo, be careful of people trolling you by calling game "game over", implement PHASE int/enum

int writeToServer(int sockfd, char message[])
{
    write(sockfd, message, strlen(message));
    printf("Sending to server-> %s\n", message);
    return 0;
}

char *convertMove(int move, char *antwort)
{
    antwort[0] = 'A' + (move % 8);     //spalte
    antwort[1] = '0' + (8 - move / 8); //zeile
    antwort[2] = '\0';
    return antwort;
}

int dealWithGameOverCommand(char *buff)
{
    /*
S: + GAMEOVER
S: + FIELD hh Anzahl Spalten ii,hh Anzahl Zeilen ii
Die folgende Zeile wird nun für jede Zeile des Spielfeldes geschickt, beginnend bei der obersten Zeile des Spiel-
felds:
S: + hh Y ii hh Stein 1Y ii hh Stein 2Y ii ... hh Stein X max Y ii
S: + ENDFIELD
S: + PLAYER0WON hh ’Yes’ oder ’No’ ii
S: + PLAYER1WON hh ’Yes’ oder ’No’ ii
S: + QUIT
hh Abbau der TCP-Verbindung durch Gameserver ii
Nach einem GAMEOVER stellen die weiteren Zeilen den Spielstand dar, mit dem das Partieende erreicht wurde. Dieser
wird an alle Mitspieler geschickt. Zudem wird angegeben, welche Mitspieler gewonnen haben. Es ist auch möglich, dass
eine Partie in einem Unentschieden endet. In dem Fall ist allen Mitspielern der Gewinnstatus der Partie auf Yes gesetzt.
Nach QUIT beendet der Server die Verbindung
     */

    printf("%s\n", buff);
    return 0; // todo, implement
}

/*char *getMoveFromThinker(BOARD_STRUCT *connectorBoard, BOARD_STRUCT *thinkerBoard, int moveTime, char *moveRet)
{
     memcpy(thinkerBoard->board, connectorBoard->board, sizeof(int) * 8 * 8); //wenn Server eine Board von uns schickt.
     thinkerBoard->sideToMove = connectorBoard->sideToMove;


     //getAktuellesBoard(thinkerBoard);

     int move = doThink(thinkerBoard, moveTime);

     printf("move is: %d\n", move);
     convertMove(move, moveRet);

     printf("converted move is: %s\n", moveRet);

     return moveRet;
 }*/

// todo, handle end state, what do we do once game is over?
int haveConversationWithServer(int sockfd, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                               BOARD_STRUCT *thinkerBoard, infoVonServer *info, pid_t thinker, pid_t connector, Player *myPlayer, Player *gegner)
{
    //bool killReady=false;
    printf("+++++++++++++++++++++++++++%s\n",gameID);
    gameID[13]='\0'; 
    strcpy(info->gameID, gameID);
    printf("info.gameId %s\n",info->gameID);
    info->me = myPlayer;
    info->thinkerBoard=thinkerBoard; //myPlayer ist schon in main definiert.Weist Player Struct myPlayer den InfoVonServer Struct zu.
    myPlayer->bereit = true;
    info->connector = connector;
    info->thinker = thinker;
    //info->thinkerBoard = thinkerBoard;

   
    strcpy(info->gameKindName, gameKindName);
    char buff[MAX];        // todo pick standard size for everything, and avoid buffer overflow with ex. strncpy
    char gameName[64];     // example: Game from 2019-11-18 17:42
    char playerNumber[32]; //1
    char myPlayerName[32]; //2
    char opponent[32];
    int n = 0, readResponse = 0;

    char version[] = "VERSION 2.42\n";
    info->majorVersionNr = 2;
    info->minorVersionNr = 42;
    char okWait[] = "OKWAIT\n";

    char gameIdToSend[20];
    strcpy(gameIdToSend, "ID ");
    strcat(gameIdToSend, gameID);
    strcat(gameIdToSend, "\n");

    char blankPlayerToSend[] = "PLAYER\n"; // todo get from argument. need extra whitespace if there is a player provided
    char playerToSend[] = "PLAYER 1\n";    // todo get from argument. need extra whitespace if there is a player provided
    char thinking[] = "THINKING\n";
    char playf5[] = "PLAY D6\n";
    int lengthOfPlayCommandToSendToKeep = 5;
    char moveReceivedFromThinker[3];
    char *moveReceivedFromThinkerTEMP;
    char gameKindNameFromServer[32];
    char playCommandToSend[10];

    SIDE_TO_MOVE sideToMove;

    enum Phase phase = PROLOG; // this can be used to make sure we do not get confused about what stage of the game we are in

    moveTimeAndBoard *moveTimeAndBoard = malloc(sizeof(moveTimeAndBoard));

    // todo, + ENDPLAYERS

    if (!gameKindName)
    {
        printf("game kind name not provided, exiting");
        exit(1);
    }

    printf("########## %s\n", gameKindName);
    for (;;)
    {
        if ((readResponse = read(sockfd, buff, sizeof(buff))))
        {
            printf("--->%s\n", buff);

            // todo for louis, error handling

            //            // ERROR HANDLING
            //            if ((strncmp("- TIMEOUT Be faster next time", buff, 29)) == 0) {
            // switch on phase?
            ////                writeToServer(sockfd, version);
            //            }
            //
            //            if ((strncmp("- Internal error. Sorry & Bye", buff, 29)) == 0) {
            // switch on phase?
            ////                writeToServer(sockfd, version);
            //            }
            //
            if ((strncmp("- No free player", buff, 16)) == 0)
            {
                printf("Could not connect to game, the player is already taken, or there are no free players.\n");
            }

            // step one, send VERSION 2.xxx
            if ((strncmp("+ MNM Gameserver", buff, 16)) == 0)
            {
                writeToServer(sockfd, version);
            }

            // step two, send game ID
            if ((strncmp("+ Client version accepted", buff, 25)) == 0)
            {
                writeToServer(sockfd, gameIdToSend);
            }

            // step three, read PLAYING, wait for another read, then send PLAYER info
            if (strncmp("+ PLAYING ", buff, 10) == 0)
            {
                strncpy(gameKindNameFromServer, buff + 10, strlen(buff) - strlen("+ PLAYING "));
                if (strncmp(gameKindName, gameKindNameFromServer, 7) == 0)
                {
                    printf("##### We play reversi now.#####\n");
                }
                else
                {
                    printf("##### We don't play reversi now.#####\n");
                    exit(1);
                }

                bzero(buff, sizeof(buff));
                while ((readResponse = read(sockfd, buff, sizeof(buff))) &&
                       strlen(buff) < 1)
                    ; // todo, possibly stick to only one central read?
                printf("%s\n", buff);
                strncpy(gameName, buff + 2, strlen(buff) - strlen("+ "));
                strcpy(info->gameName,gameName);
                printf("-----------save gameName: %s\n", gameName);
                if (player == NULL || strlen(player) != 1)
                {
                    printf("### -------------> connecting with blank player string:'%s'\n", blankPlayerToSend);
                    writeToServer(sockfd, blankPlayerToSend);
                }
                else
                {

                    strcpy(playerToSend, "PLAYER ");
                    playerToSend[7] = player[0];
                    printf("### -------------> connecting with player string:'%s'\n", playerToSend);
                    writeToServer(sockfd, playerToSend);
                }
            }
            // step four, read YOU
            if (strncmp("+ YOU", buff, 5) == 0)
            {
                // todo, save information from Server here
                //finished

                printf("  Received YOU info from server, buff is:%s", buff);
                strncpy(playerNumber, buff + 6, 1);
                playerNumber[2] = '\0';
                printf("--------save  playerNumber: %s\n", playerNumber);
                // this often gets weird crap
                info->me->mitspielerNummer = atoi(playerNumber);
                printf("----save mitspielerNummer:%d\n", info->me->mitspielerNummer);

                if (playerNumber[0] == '0')
                {
                    sideToMove = getBlack();
                }
                else
                {
                    sideToMove = getWhite();
                }

                int l = strlen(buff) - strlen("+ YOU 0 ");
                strncpy(myPlayerName, buff + 8, strlen(buff) - strlen("+ YOU 0 "));
                myPlayerName[l] = '\0';
                printf("--------save my playerName: %s\n", myPlayerName);
                strcpy(info->me->mitspielerName, myPlayerName);
                printf("---save mitspielerName:%s\n", info->me->mitspielerName);
            }

            // step five, read TOTAL
            if (strncmp("+ TOTAL", buff, 7) == 0)
            {
                printf("  Received TOTAL info from server, buff is:%s", buff);
                strncpy(info->MitspielerAnzahl, buff + 8, 1);
                info->MitspielerAnzahl[1] = '\0';
                printf("--------save  MitspielerAnzahl: %s\n", info->MitspielerAnzahl);
                phase = SPIELVERLAUF;
            }
           
            
            
            // step six, read board information and time to move from server.
            // todo, extract timeToMove info
            // todo, extract board size
            // todo, replace all magic numbers
            // todo, read name of opponent
            // todo, read Breit 0 or 1 and save Breit. If 0, print "Spieler 1 (Uli) ist noch nicht bereit"
            if (strlen(buff) > 75)
            { // todo make better (add check for first chars for example)
                printf("sending thinking command\n");
                writeToServer(sockfd, thinking);

                printf("sent thinking command\n");

                printf("starting parse board, setting phase to spielzug\n");
                phase = SPIELZUG;
                parseBoardMessage(connectorBoard, moveTimeAndBoard, buff);
            
                printf("+++++++++++++++++++++++++++++\n");
                printf("++++++\n");
                schreiben = true;
            
                 /* ----------------------- fertig mit schreiben des struct infoVonServer und schreiben in SHM ---*/
                 /*---------- schreibe in das Shm das gefüllte Struct aus connectorMasterMethod ------------------*/
            

                //signal schicken
                if (kill(thinker, SIGUSR1) == -1)
                {
                    printf("Fehler beim senden des Signals\n");
                    exit(1);
                }
                else
                {
                    printf("******************************************kill\n");
                }

                printf("finished parse board, here is the board I was able to parse:\n");
                printBoardLouis(connectorBoard);
                printf("finished parse board\n");
                printf("sending relevant info to thinker\n");

                memcpy(info->thinkerBoard->board, connectorBoard->board, sizeof(int) * 8 * 8); //wenn Server eine Board von uns schickt. wenn der server uns ein Board
                info->thinkerBoard->sideToMove = connectorBoard->sideToMove;
                // char *moveRet = malloc(3 * sizeof(char));
               // connectorBoard->sideToMove = getBlack(); // todo todo todo!!! get from player or from response or from past response I dont't care
                //                                          //                connectorBoard->sideToMove = getWhite(); // todo todo todo!!! get from player or from response or from past response I dont't care

                // moveReceivedFromThinkerTEMP = getMoveFromThinker(connectorBoard, thinkerBoard,
                //moveTimeAndBoard->movetime, moveRet);
                // printf("received from thinker: %s\n", moveReceivedFromThinkerTEMP);

                // printf("%s   %d\n", moveRet, (int)strlen(moveRet));
                // if (strlen(moveRet) != 2)
                // {
                //     fprintf(stderr, "move of incorrect length received from thinker: %s\n",
                //             moveRet);
                //     exit(1); // todo in future we want to implement retry logic etc to avoid crashing on a single error
                // }
                // moveReceivedFromThinker[0] = moveRet[0];
                // moveReceivedFromThinker[1] = moveRet[1];
                // moveReceivedFromThinker[2] = '\0';

                // free(moveRet);
                close(pd[1]);    // Schreibseite schließen
                char buffer[50]; // Puffer zum speichern von gelesenen Daten
                                  //ssize_t nread;
                                  // for (int i = 1; i < 5; i++)
                                  // {
                 if (read(pd[0], buffer, sizeof(buffer)) == -1)
                 { // Leseseite auslesen (blockiert hier bis Daten vorhanden)
                     perror("read");
                     exit(EXIT_FAILURE);
                 }
                 else
                { //sleep(1);
                     printf("Connector(Kindsprozess) bekommt Nachricht von pipe: %s,length of buffer:%li\n\n", buffer, strlen(buffer));
                 //sleep(1);
                     // }
                 }
                 moveReceivedFromThinker[0] = buffer[0];
                 moveReceivedFromThinker[1] = buffer[1];
                 moveReceivedFromThinker[2] = '\0';
                //Speilzug senden.
                strcpy(playCommandToSend, "PLAY ");
                strcat(playCommandToSend, moveReceivedFromThinker);
                strcat(playCommandToSend, "\n");
                printf("playCommandToSend: %s\n", playCommandToSend);

                writeToServer(sockfd, playCommandToSend);
                phase = SPIELVERLAUF;
                playCommandToSend[0] = '\0';
            }

            deleteShm();

            if ((strncmp("+ WAIT", buff, 6)) == 0)
            {
                writeToServer(sockfd, okWait);
            }

            if ((strncmp("+ GAMEOVER", buff, 10)) == 0)
            {
                phase = PROLOG;
                dealWithGameOverCommand(buff);
                //                writeToServer(sockfd, okWait);
            }

            if ((strncmp("+ ENDFIELD", buff, 10)) == 0)
            { // todo, is this necessary? I don't think this is ever called
                printf("endfield received, possibly something is wrong!!!\n");

                writeToServer(sockfd, thinking);
            }

            if (readResponse == -1)
            {
                printf("Could not read from server");
                exit(0);
            }
            bzero(buff, sizeof(buff));
        }
    }

    free(moveTimeAndBoard);
}

int performConnectionLouis(int sock, char *gameID, char *player, char *gameKindName, BOARD_STRUCT *connectorBoard,
                           BOARD_STRUCT *thinkerBoard, infoVonServer *info, pid_t thinker, pid_t connector, Player *myPlayer, Player *gegner)
{

    haveConversationWithServer(sock, gameID, player, gameKindName, connectorBoard, thinkerBoard, info, thinker, connector, myPlayer, gegner);
    //printf("###############################################################louis:%s\n", info->myPlayerName);
    printf("performConnection %d\n", sock);

    return 0;
}
