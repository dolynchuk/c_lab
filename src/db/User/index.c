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
    user.deleted = 0;
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
    strcat(buffer, "&");

    char numBuffer3[2];
    sprintf(numBuffer3, "%d", user.deleted);
    strcat(buffer, "deleted=");
    strcat(buffer, numBuffer3);

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


///ParseValue - helper function =)
///@param stringToParse
///@param param
char *ParseValue(char *stringToParse, char *param) {
    char *buffer = malloc(sizeof(char) * 100);
    for (int i = 0; i < strlen(buffer); i++) {
        buffer[i] = ' ';
    }
    char *a = strstr(stringToParse, param);
    char *b = strstr(a, "=");
    for (int i = 1; i < strlen(buffer); i++) {
        if (b[i] == '&' || b[i] == ' ' || b[i] == '\0') {
            return buffer;
        }
        buffer[i - 1] = b[i];
    }
    free(b);
    free(a);

    return buffer;
}

///URLDecodeUser - get user from string created withURLDecodeUser
///@param userString - string to parse
struct UserModel URLDecodeUser(char *userString) {
    struct UserModel user;

    char *userID = ParseValue(userString, "userID");
    user.userID = atoi(userID);
    free(userID);

    char *deleted = ParseValue(userString, "deleted");
    user.deleted = atoi(deleted);
    free(deleted);

    char *age = ParseValue(userString, "age");
    user.age = atoi(age);
    free(age);

    char *name = ParseValue(userString, "name");
    strcpy((char *) user.name, name);
    free(name);

    char *surname = ParseValue(userString, "surname");
    strcpy((char *) user.surname, surname);
    free(surname);

    return user;
}
