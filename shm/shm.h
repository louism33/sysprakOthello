#ifndef shared_memory
#define SHMDATASIZE 1024

#include <sys/types.h>
#include <stdbool.h>
#include "../thinker/board.h"
#include "../connector/connector.h"

void createShm();

int createProcesses();

void *attachShm();

void writeShm();

void writeShmEasy(char *x);

void *readShm();

void deleteShm();

void waitForChild();

#endif 