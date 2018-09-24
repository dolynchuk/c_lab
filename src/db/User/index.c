#include "index.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// autoIncrement for user primary key
int userIDCounter = 0;

///CreateUser - create user struct from params
///@param age - user age
///@param name - user name
///@param surname - user surname
struct UserModel CreateUser(int age, char *name, char *surname) {
    struct UserModel user;
    user.age = age;
    strcpy((char *) user.name, name);
    strcpy((char *) user.surname, surname);
    user.userID = userIDCounter++;
    return user;
}

///URLEncodeUser - create url-like string from user struct
///@param user - user struct used to create string
char *URLEncodeUser(struct UserModel user) {
    char *buffer = malloc(sizeof(char) * 100);
    char *spacedBuffer = malloc(sizeof(char) * 100);

    strcpy(buffer, "name=");
    strcat(buffer, (char *) user.name);
    strcat(buffer, "&");

    strcat(buffer, "surname=");
    strcat(buffer, (char *) user.surname);
    strcat(buffer, "&");

    char numBuffer[100];
    sprintf(numBuffer, "%d", user.age);
    strcat(buffer, "age=");
    strcat(buffer, numBuffer);
    strcat(buffer, "&");

    char numBuffer2[100];
    sprintf(numBuffer2, "%d", user.userID);
    strcat(buffer, "userID=");
    strcat(buffer, numBuffer2);

    for (int i = 0; i < 100; i++) {
        if (i < strlen(buffer)) {
            spacedBuffer[i] = buffer[i];
        } else {
            spacedBuffer[i] = ' ';
        }
    }
    spacedBuffer[99] = '\0';

    free(buffer);

    return spacedBuffer;
}
