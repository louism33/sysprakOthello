//
// Created by louis on 11/17/19.
//

#ifndef SYSPRAKOTHELLO_CONFIG_H
#define SYSPRAKOTHELLO_CONFIG_H

typedef struct configurationStruct {
    char *hostname;
    char *gamekindname;
    int portnumber;
} configurationStruct;


int readConfigurationFile(char *pathName, configurationStruct * configurationStruct);

#endif //SYSPRAKOTHELLO_CONFIG_H
