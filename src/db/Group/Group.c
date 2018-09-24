#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../help/help.h"

// autoIncrement for group primary key
int groupIDCounter = 0;

///CreateGroup - create group struct from params
///@param name - group name
struct GroupModel CreateGroup(char *name) {
    struct GroupModel group;
    strcpy((char *) group.name, name);
    group.groupID = groupIDCounter++;
    group.deleted = 0;
    return group;
}

///URLEncodeGroup - create url-like string from group struct
///@param group - group struct used to create string
char *URLEncodeGroup(struct GroupModel group) {
    char *buffer = malloc(sizeof(char) * 100);
    char *spacedBuffer = malloc(sizeof(char) * 100);

    strcpy(buffer, "name=");
    strcat(buffer, (char *) group.name);
    strcat(buffer, "&");

    char numBuffer2[100];
    sprintf(numBuffer2, "%d", group.groupID);
    strcat(buffer, "groupID=");
    strcat(buffer, numBuffer2);
    strcat(buffer, "&");

    char numBuffer3[2];
    sprintf(numBuffer3, "%d", group.deleted);
    strcat(buffer, "deleted=");
    strcat(buffer, numBuffer3);

    for (int i = 0; i < 100; i++) {
        if (i < strlen(buffer)) {
            spacedBuffer[i] = buffer[i];
        } else {
            spacedBuffer[i] = ' ';
        }
    }
    spacedBuffer[99] = '\0';

    free(buffer);

    return spacedBuffer;
}

///URLDecodeGroup - get group from string created withURLDecodeGroup
///@param groupString - string to parse
struct GroupModel URLDecodeGroup(char *groupString) {
    struct GroupModel group;

    char *groupID = ParseValue(groupString, "groupID");
    group.groupID = atoi(groupID);
    free(groupID);

    char *deleted = ParseValue(groupString, "deleted");
    group.deleted = atoi(deleted);
    free(deleted);

    char *name = ParseValue(groupString, "name");
    strcpy((char *) group.name, name);
    free(name);

    return group;
}
