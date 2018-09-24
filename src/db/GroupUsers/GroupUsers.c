#include "GroupUsers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../help/help.h"

// autoIncrement for group primary key
int groupUsersIDCounter = 0;

///CreateGroupUsers - create groupUsers struct from params
///@param groupID
///@param userID
struct GroupUsersModel CreateGroupUsers(int groupID, int userID) {
    struct GroupUsersModel groupUsers;
    groupUsers.groupUsersID = groupUsersIDCounter++;
    groupUsers.groupID = groupID;
    groupUsers.userID = userID;
    groupUsers.deleted = 0;
    return groupUsers;
}

///URLEncodeGroupUsers - create url-like string from GroupUsers struct
///@param groupUsers - group struct used to create string
char *URLEncodeGroupUsers(struct GroupUsersModel groupUsers) {
    char *buffer = malloc(sizeof(char) * 100);
    char *spacedBuffer = malloc(sizeof(char) * 100);

    char numBuffer1[100];
    sprintf(numBuffer1, "%d", groupUsers.groupUsersID);
    strcat(buffer, "groupUsersID=");
    strcat(buffer, numBuffer1);
    strcat(buffer, "&");

    char numBuffer2[100];
    sprintf(numBuffer2, "%d", groupUsers.groupID);
    strcat(buffer, "groupID=");
    strcat(buffer, numBuffer2);
    strcat(buffer, "&");


    char numBuffer3[100];
    sprintf(numBuffer2, "%d", groupUsers.userID);
    strcat(buffer, "userID=");
    strcat(buffer, numBuffer2);
    strcat(buffer, "&");

    char numBuffer4[2];
    sprintf(numBuffer3, "%d", groupUsers.deleted);
    strcat(buffer, "deleted=");
    strcat(buffer, numBuffer4);

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

///URLDecodeGroupUsers - get group from string created withURLDecodeGroupUsers
///@param groupUsersString - string to parse
struct GroupUsersModel URLDecodeGroupUsers(char *groupUsersString) {
    struct GroupUsersModel groupUsers;

    char *groupUsersID = ParseValue(groupUsersString, "groupUsersID");
    groupUsers.groupUsersID = atoi(groupUsersID);
    free(groupUsersID);

    char *groupID = ParseValue(groupUsersString, "groupID");
    groupUsers.groupID = atoi(groupID);
    free(groupUsersID);

    char *userID = ParseValue(groupUsersString, "userID");
    groupUsers.userID = atoi(groupUsersID);
    free(userID);

    char *deleted = ParseValue(groupUsersString, "deleted");
    groupUsers.deleted = atoi(deleted);
    free(deleted);

    return groupUsers;
}
