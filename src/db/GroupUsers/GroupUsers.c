#include "GroupUsers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
