#ifndef C_GROUP_USERS_H
#define C_GROUP_USERS_H

struct GroupUsersModel {
    int groupUsersID;
    int deleted;
    int groupID;
    int userID;
};

struct GroupUsersModel CreateGroupUsers(int groupID, int userID);

int AppendGroupToFile(char *filename, struct UserModel groupUsers);

struct GroupUsersModel *ReadGroupUsersFromFile(char *filename, int seek);

int UpdateGroupUsers(char *filename, int seek, struct GroupUsersModel *newGroupUsers);

#endif //C_GROUP_USERS_H
