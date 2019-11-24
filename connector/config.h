//
// Created by louis on 11/17/19.
//

#ifndef SYSPRAKOTHELLO_CONFIG_H
#define SYSPRAKOTHELLO_CONFIG_H

typedef struct configurationStruct {
    char *hostname;
    int portnumber;
    char *gamekindname;
} configurationStruct;


configurationStruct *readConfigurationFile(char *pathName);

#endif //SYSPRAKOTHELLO_CONFIG_H
