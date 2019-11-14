#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "connector/connector.h"
#include "thinker/thinker.h"

int main(int argc,char*argv[]) {
    char *GAMEID;
    int GAMENUMBER=0;
    int ret;
    while((ret=getopt(argc, argv, "g:p:")) != -1) {
        switch(ret){
            case 'g':
                GAMEID=optarg;
                break;
            case 'p':
                GAMENUMBER=atoi(optarg);
                break;
            default:
                perror("keine gültige Game-ID oder Game-Number.\n");
                break;
        }
    }
    //Fehlerbehandelung
   if(strlen(GAMEID)>13){
        perror("Das Game-ID ist grosser als 13-stellige.\n");
        GAMEID=NULL;
        exit(0);
    }else if(strlen(GAMEID)<13){
        perror("Das Game-ID ist kleiner als 13-stellige.\n");
        GAMEID=NULL;
        exit(0);
    } 
    printf("Hello World! I am Alex. This is the main method\n");
    connectorMasterMethod();
    thinkerMasterMethod();
    


    return 0;
}