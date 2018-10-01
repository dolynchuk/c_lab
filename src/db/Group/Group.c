#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int groupIDCounter = 0;

struct GroupModel CreateGroup(char *name) {
    struct GroupModel group;
    strcpy((char *) group.name, name);
    group.groupID = groupIDCounter++;
    group.deleted = 0;
    return group;
}

int AppendGroupToFile(char *filename, struct GroupModel group) {
    FILE *file = fopen(filename, "a");

    struct GroupModel *object = malloc(sizeof(struct GroupModel));
    object->groupID = group.groupID;
    object->deleted = group.deleted;
    strcpy((char *) object->name, (char *) group.name);

    if (file != NULL) {
        fwrite(object, sizeof(struct GroupModel), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

struct UserModel *ReadGroupUsersFromFile(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    struct UserModel *object = malloc(sizeof(struct UserModel));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(struct UserModel), 1, file);
        fclose(file);
    }
    return object;
}

int UpdateUser(char *filename, int seek, struct UserModel *newUser) {
    FILE *file = fopen(filename, "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(newUser, sizeof(struct UserModel), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}
