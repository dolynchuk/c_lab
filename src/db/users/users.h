#ifndef C_USER_H
#define C_USER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../../io/io.h"
#include "../index_file/index_file.h"
#include "../groups_users/groups_users.h"

typedef struct USER_MODEL {
    int user_id;
    int age;
    char *name[50];
    char *surname[50];
} user_model;

user_model create_user(int age, char *name, char *surname);

user_model get_user(int id);

int insert_user(user_model user);

int count_users(void);

int remove_user(int id);

int update_user(int id, user_model user);

int remove_users_data(void);

#endif //C_USER_H
