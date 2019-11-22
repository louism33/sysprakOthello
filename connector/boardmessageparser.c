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

#include <regex.h>
#include <stdio.h>
#include <string.h>

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


moveTimeAndBoard *parseBoardMessage(int *board, char *message) {

    printf("%s\n\n\n", message);
    printf("%d\n", (int) strlen(message));
    printf("---\n");

//    char * source = "___ abc123def ___ ghi456 ___";
//    char * regexString = "[a-z]*([0-9]+)([a-z]*)";
    char * regexString = "\\+ MOVE ([0-9]+)";
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Could not compile regular expression.\n");
        return NULL;
    };

    if (regexec(&regexCompiled, message, maxGroups, groupArray, 0) == 0ul)
    {
        unsigned int g = 0;
        for (g = 0; g < maxGroups; g++)
        {
            if (groupArray[g].rm_so == (int)(size_t)-1)
                break;  // No more groups

            char sourceCopy[strlen(message) + 1];
            strcpy(sourceCopy, message);
            sourceCopy[groupArray[g].rm_eo] = 0;
            printf("Group %u: [%2u-%2u]: %s\n",
                   g, groupArray[g].rm_so, groupArray[g].rm_eo,
                   sourceCopy + groupArray[g].rm_so);
        }
    }

    regfree(&regexCompiled);





    char c;
    int boardIndex = 0;

    for (int i = (int) strlen(message) - 170; i < (int) strlen(message); i++) {
        c = message[i];
//        if ((int) c == 10) {
//            printf("->%c %d<>%d<-  ", c, (int)c, ('\n' == c));
//        }
//        printf("%c %d  ", c, (int)c);
//        printf("%c", c);


        switch (c) {
            case 'B':
                board[boardIndex] = 2;
                boardIndex++;
                continue;
            case 'W':
                board[boardIndex] = 1;
                boardIndex++;
                continue;
            case '*':
                boardIndex++;
                continue;
            case 'E': // + ENDFIELD is the end of the message
                break;
        }

    }


    printf("\n");

//    char buff[1000];
//    char *s;
//
//    s = strstr(message, "ENDFIELD");      // search for string "hassasin" in buff
//    if (s != NULL)                     // if successful then s now points at "hassasin"
//    {
//        printf("Found string at index = %d\n", (int)(s - message));
//    }                                  // index of "hassasin" in buff can be found by pointer subtraction
//    else
//    {
//        printf("String not found\n");  // `strstr` returns NULL if search string not found
//    }



//    char *string = "qwertye";
//    char *e;
//    int index;
//    e = strchr(string, 'e');
//    index = (int)(e - string);
//    printf("\n%d\n", index);

    printf("\n");


    return NULL;
}