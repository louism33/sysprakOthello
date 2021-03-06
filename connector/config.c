//
// Created by louis on 11/17/19.
//
#include "../thinker/board.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define LIMIT (150)
#define STR_SIZE (300)

int readConfigurationFile(char *pathName, configurationStruct *configurationStruct) {

    printf("### Attempting to read configuration data from %s\n", pathName);

    FILE *file = fopen(pathName, "r");
    char str[STR_SIZE];
    int limit = LIMIT;

    while (fgets(str, STR_SIZE, file) && strlen(str) != 0) {
        char attribute[limit];
        bzero(attribute, limit);
        char value[limit];
        bzero(value, limit);

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
                fprintf(stderr, "### Problem reading config file, entry too long\n");
                exit(1);
            }
        }

        if (i == -1) {
            fprintf(stderr, "### Problem reading config file\n");
            exit(1);
        }

        bzero(attribute, attEndIndex + 1);
        strncpy(attribute, str + attStartIndex,
                attEndIndex - attStartIndex + 1);
        attribute[attEndIndex + 1] = '\0';

        int l = valEndIndex - valStartIndex - 1;
        bzero(value, l);
        strncpy(value, str + valStartIndex, l);
        value[valEndIndex] = '\0';

        if (strncmp(attribute, "hostname", 8) == 0) {
            strcpy(configurationStruct->hostname, value);
        } else if (strncmp(attribute, "portnumber", 10) == 0) {
            configurationStruct->portnumber = atoi(value);
        } else if (strncmp(attribute, "gamekindname", 12) == 0) {
            strcpy(configurationStruct->gamekindname, value);
        }

        bzero(str, sizeof(str));
    }
    fclose(file);

    printf("### hostname: %s\n", configurationStruct->hostname);
    printf("### portnumber: %d\n", configurationStruct->portnumber);
    printf("### gamekindname: %s\n", configurationStruct->gamekindname);

    printf("### Successfully read data from %s\n", pathName);

    return 0;
}
