//
// Created by louis on 11/13/19.
//
#include "connector.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#define GAMEKINDNAME "Reversi"
#define PORTNUMBER 1357
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"

void connectorMasterMethod(int argc,char*argv[]){
 printf("Hi I am good at connecting\n");
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
}






