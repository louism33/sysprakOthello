#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "pipe.h"
#include "../thinker/board.h"

int createPipe(int pd[])
{
    /*pipe erstellen mit pipe()*/

    if (pipe(pd) < 0)
    {
        printf("Fehler bei der Erstellung der Pipe\n");
        return 1;
    }
    else
    {
        printf("Erfolg bei der Erstellung der Pipe\n");
    }

    return 0;
}



void changeMsg(char* antwort){
    int random=rand()%63;
    getPrettyMove(random,antwort);
}

// /* nur zum Testen gewesen brauchen wir nicht mehr !*/
// void writePipe (int file) {
//   FILE *stream;
//   stream = fdopen (file, "w");
//   fprintf (stream, "hello, world!\n");
//   fprintf (stream, "goodbye, world!\n");
//   fclose (stream);
// }

// /*lesen tut der Connector*/
// void readPipe (int file) {
//   FILE *stream;
//   int c;
//   stream = fdopen (file, "r");
//   while ((c = fgetc (stream)) != EOF)
//   putchar (c);
//   fclose (stream);
// }