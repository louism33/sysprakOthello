//
// Created by louis on 11/17/19.
//

#ifndef SYSPRAKOTHELLO_CONFIG_H
#define SYSPRAKOTHELLO_CONFIG_H

typedef struct configurationStruct {
    char hostname[100];
    int portnumber;
    char gamekindname[100];
} configurationStruct;


configurationStruct* readConfigurationFile(char *pathName);

#endif //SYSPRAKOTHELLO_CONFIG_H
