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
#include "connector/config.h"

int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");

//    int pathName = 1;
//    if (pathName) {
//        readConfigurationFile("client.conf");
//    }

//    thinkerMasterMethod();
    connectorMasterMethod(argc,argv);

    return 0;
}