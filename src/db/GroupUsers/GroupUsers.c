#include "GroupUsers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// autoIncrement for group primary key
int groupUsersIDCounter = 0;

struct GroupUsersModel CreateGroupUsers(int groupID, int userID) {
    struct GroupUsersModel groupUsers;
    groupUsers.groupUsersID = groupUsersIDCounter++;
    groupUsers.groupID = groupID;
    groupUsers.userID = userID;
    groupUsers.deleted = 0;
    return groupUsers;
}

int AppendGroupToFile(char *filename, struct GroupUsersModel groupUsers) {
    FILE *file = fopen(filename, "a");

    struct GroupUsersModel *object = malloc(sizeof(struct GroupUsersModel));
    object->groupUsersID = groupUsers.groupUsersID;
    object->deleted = groupUsers.deleted;
    object->groupID = groupUsers.groupID;
    object->userID = groupUsers.userID;

    if (file != NULL) {
        fwrite(object, sizeof(struct GroupUsersModel), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

struct GroupUsersModel *ReadGroupUsersFromFile(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    struct GroupUsersModel *object = malloc(sizeof(struct GroupUsersModel));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(struct GroupUsersModel), 1, file);
        fclose(file);
    }
    return object;
}

int UpdateGroupUsers(char *filename, int seek, struct GroupUsersModel *newGroupUsers) {
    FILE *file = fopen(filename, "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(newGroupUsers, sizeof(struct GroupUsersModel), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}
