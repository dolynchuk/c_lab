#ifndef C_GROUP_H
#define C_GROUP_H

struct GroupModel {
    int groupID;
    int deleted;
    char name[50];
};

struct GroupModel CreateGroup(char *name);

char *URLEncodeGroup(struct GroupModel group);

struct GroupModel URLDecodeGroup(char *groupString);

#endif //C_GROUP_H
