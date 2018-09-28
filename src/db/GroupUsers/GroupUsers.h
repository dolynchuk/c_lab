#ifndef C_GROUP_USERS_H
#define C_GROUP_USERS_H

struct GroupUsersModel {
    int groupUsersID;
    int deleted;
    int groupID;
    int userID;
};

struct GroupUsersModel CreateGroupUsers(int groupID, int userID);

#endif //C_GROUP_USERS_H
