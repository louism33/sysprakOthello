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

#include "connector/boardmessageparser.h"

#define BOARD int*

// if thinker is parent, retry logic may be easier to implement
// including learning

int main(int argc, char *argv[]) {
    printf("Hello World! I am Alex. This is the main method\n");

//    exampleUseCaseOfMessageParsing();

//    thinkerMasterMethod();
    connectorMasterMethod(argc,argv);

    return 0;
}
