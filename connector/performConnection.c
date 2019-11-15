
#include <stdio.h>


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define MAX 80

#define PLAYER
//Die Prolog-Phase der Kommunikation 
//Noch nicht fertig gemacht.


void readStuff(int sockfd)
{
    char buff[MAX];
    int n;
    bzero(buff, sizeof(buff));
    for (;;) {
        // read from server
        read(sockfd, buff, sizeof(buff));
        printf("%s", buff);
        bzero(buff, sizeof(buff));

        // write to server
        printf("Enter the string : ");
        n = 0;
        // you can manually talk to the server here
        while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));


        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int performConnection(int sock){

    readStuff(sock);


    printf("performConnection %d\n", sock);



    return 0;
}