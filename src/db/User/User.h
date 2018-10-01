#ifndef C_USER_H
#define C_USER_H

typedef struct  UserModel {
    int userID;
    int age;
    int deleted;
    char *name[50];
    char *surname[50];
}               user_model;

user_model CreateUser(int age, char *name, char *surname);

int AppendGroupToFile(char *filename, user_model user);

int UpdateUser(char *filename, int seek, user_model *newUser);

user_model *ReadGroupUsersFromFile(char *filename, int seek);

#endif //C_USER_H
