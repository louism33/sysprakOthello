#include <stdio.h>
#include "connector/connector.h"
#include "thinker/thinker.h"
#include "shm/shm.h"

int main() {

    printf("Hello World! I am Alex. This is the main method\n");

    connectorMasterMethod();
    thinkerMasterMethod();
    return 0;
}