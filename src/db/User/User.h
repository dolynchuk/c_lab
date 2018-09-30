#ifndef C_USER_H
#define C_USER_H

struct UserModel {
    int userID;
    int age;
    int deleted;
    char *name[50];
    char *surname[50];
};

struct UserModel CreateUser(int age, char *name, char *surname);

int AppendGroupToFile(char *filename, struct UserModel user);

int UpdateUser(char *filename, int seek, struct UserModel *newUser);

struct UserModel *ReadGroupUsersFromFile(char *filename, int seek);

#endif //C_USER_H
