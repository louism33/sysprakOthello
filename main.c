#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connector/connector.h"
#include "thinker/thinker.h"


typedef struct configurationStruct{
    char* hostname;
    int portnumber;
    char* gamekindname;
} configurationStruct;


int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");

    char *pathName = "client.conf";

    FILE *fileAgain = fopen(pathName, "r");
    char *str = (char*) malloc(12*sizeof(char));
    fscanf(fileAgain, "%s", str);
    printf("%s\n", str);

//    struct configurationStruct configurationStruct;

//    thinkerMasterMethod();
//    connectorMasterMethod(argc,argv);

    return 0;
}