#ifndef C_GROUPS_USERS_H
#define C_GROUPS_USERS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../io/io.h"
#include "../index_file/index_file.h"

typedef struct GROUP_USERS_MODEL {
    int groups_users_id;
    int group_id;
    int user_id;

} groups_users_model;

groups_users_model create_groups_users(int group_id, int user_id);

groups_users_model get_groups_users(int id);

int insert_groups_users(groups_users_model group);

int count_groups(void);

int remove_groups_users(int id);

int update_groups_users(int id, groups_users_model group);

int remove_groups_users_data(void);

#endif //C_GROUPS_USERS_H
