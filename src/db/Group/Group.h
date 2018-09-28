#ifndef C_GROUP_H
#define C_GROUP_H

struct GroupModel {
    int groupID;
    int deleted;
    char name[50];
};

struct GroupModel CreateGroup(char *name);

#endif //C_GROUP_H
