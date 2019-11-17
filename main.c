#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "connector/connector.h"
#include "thinker/thinker.h"

int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");

    thinkerMasterMethod();
    connectorMasterMethod(argc,argv);

    return 0;
}