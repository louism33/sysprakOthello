#include <stdio.h>
#include <unistd.h>
#include "pipe.h"

int createPipe(int mypipe, int pd[]) {
	/*pipe erstellen mit pipe()*/
	mypipe = pipe(pd);
	if(mypipe == -1) {
		printf("Fehler bei der Erstellung der Pipe\n");
	}
	printf("Erfolg bei der Erstellung der Pipe\n");
}


/* nur zum Testen gewesen brauchen wir nicht mehr !*/
/*void writePipe (int file) {
  FILE *stream;
  stream = fdopen (file, "w");
  fprintf (stream, "hello, world!\n");
  fprintf (stream, "goodbye, world!\n");
  fclose (stream);
}*/


/*lesen tut der Connector*/
/*void readPipe (int file) {
  FILE *stream;
  int c;
  stream = fdopen (file, "r");
  while ((c = fgetc (stream)) != EOF)
  putchar (c);
  fclose (stream);
}*/
