//
// Created by louis on 11/20/19.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

#include "boardmessageparser.h"



/*
+ TOTAL 2
+ 0 IAMLOUIS 0
+ ENDPLAYERS
+ MOVE 3000
+ FIELD 8,8
+ 8 * * * * * * * *
+ 7 * * * * * B B B
+ 6 * * * * * W * *
+ 5 * * W W W B * *
+ 4 * B B B B * * *
+ 3 * * W * * * * *
+ 2 * * * * * * * *
+ 1 * * * * * * * *
+ ENDFIELD
 */


moveTimeAndBoard *parseBoardMessage(char *message){

    printf("%s\n", message);

    return NULL;
}