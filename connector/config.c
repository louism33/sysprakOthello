//
// Created by louis on 11/17/19.
//

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

configurationStruct* readConfigurationFile(char *pathName){

    printf("%s\n", pathName);

    struct configurationStruct *configurationStruct = malloc(sizeof(configurationStruct));

    FILE *file = fopen(pathName, "r");
    char str[100];
    int limit = 150;

    while (fgets(str, 300, file) && strlen(str) != 0) {
        printf("--a\n");
        char attribute[limit];
        char value[limit];

        int index = 0, i = -1, endIndex = 0, endIndexAtt = 0;

        int stringLengthIncludingSpaces = 0;

        int foundAtt = 0, foundEq = 0, foundVal = 0;

        int attStartIndex = 0, attEndIndex = 0;
        int valStartIndex = 0, valEndIndex = 0;
        int eqIndex;

        for (;;) {
            i++;
            char c = str[i];
            if (foundVal && c == 0) {
                valEndIndex = i;
                break;
            }

            // ignore leading whitespace
            if (!foundAtt) {
                if (c != ' ') {
                    foundAtt = 1;
                    attStartIndex = i;
                }
                continue;
            }

            // get attribute and '=' info, ignore whitespace before '='
            if (!foundEq) {
                if (c == '=') {
                    foundEq = 1;
                    attEndIndex = i - 1;
                    eqIndex = i;
                }
                continue;
            }

            // ignore whitespace after '=' and get value info
            if (!foundVal) {
                if (c != ' ') {
                    foundVal = 1;
                    valStartIndex = i;
                }
                continue;
            } else {
                if (c == ' ') {
                    valEndIndex = i;
                    stringLengthIncludingSpaces = i + 1;
                    break;
                }
            }

            if (i > limit) {
                printf("problem reading config file, entry too long\n");
                printf("%d %d %d\n", foundAtt, foundEq, foundVal);
                exit(1);
            }
        }

        if (i == -1) {
            printf("problem reading config file\n");
            exit(1);
        }

        bzero(attribute, attEndIndex + 1);
        strncpy(attribute, str + attStartIndex, attEndIndex - attStartIndex + 1);
        attribute[attEndIndex + 1] = '\0';

        int l = valEndIndex - valStartIndex - 1;
        bzero(value, l);
        strncpy(value, str + valStartIndex, l);
        value[valEndIndex] = '\0';

        // todo, make scalable as per instructions
//        printf("try to match %s\n", attribute);
        if (strcmp(attribute, "hostname") == 0) {
//            printf("aaaaaaa\n");
            strcpy(configurationStruct->hostname, value);
        } else if (strcmp(attribute, "portnumber") == 0) {
//            printf("bbbbbbbbbbbbb\n");
            configurationStruct->portnumber = atoi(value);
        } else if (strcmp(attribute, "gamekindname") == 0) {
//            printf("ccccccccc\n");
            strcpy(configurationStruct->gamekindname, value);
        }



//        printf("z\n");

        bzero(str, sizeof(str));
        printf("--z\n");
    }
    printf("zz\n");
    fclose(file);


    printf("x\n");
    printf("%s\n", configurationStruct->hostname);
    printf("y\n");
    printf("%d\n", configurationStruct->portnumber);
    printf("z\n");
    printf("%s\n", configurationStruct->gamekindname);
    printf("zzzzz\n");

    printf("------%s\n", pathName);
    return configurationStruct;
}