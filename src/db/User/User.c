#include "User.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// autoIncrement for user primary key
int userIDCounter = 0;


struct UserModel CreateUser(int age, char *name, char *surname) {
    struct UserModel user;
    user.age = age;
    strcpy((char *) user.name, name);
    strcpy((char *) user.surname, surname);
    user.userID = userIDCounter++;
    user.deleted = 0;
    return user;
}

int AppendUserToFile(char *filename, struct UserModel user) {
    FILE *file = fopen(filename, "a");

    struct UserModel *object = malloc(sizeof(struct UserModel));
    object->userID = user.userID;
    object->deleted = user.deleted;
    object->age = user.age;
    strcpy((char *) object->name, (char *) user.name);
    strcpy((char *) object->surname, (char *) user.surname);

    if (file != NULL) {
        fwrite(object, sizeof(struct UserModel), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

struct UserModel *ReadUserFromFile(char *filename, int seek) {
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