#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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