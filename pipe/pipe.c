#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "pipe.h"
#include "../thinker/board.h"

int createPipe(int pd[])
{
    if (pipe(pd) < 0)
    {
        fprintf(stderr, "### Fehler bei der Erstellung der Pipe\n");
        return 1;
    }
    else
    {
        printf("### Erfolg bei der Erstellung der Pipe\n");
    }

    return 0;
}
