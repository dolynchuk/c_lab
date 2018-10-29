#ifndef C_GROUP_H
#define C_GROUP_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../io/io.h"
#include "../index_file/index_file.h"

typedef struct GROUP_MODEL {
    int group_id;
    char name[50];


} group_model;

group_model create_group(char *name);

group_model get_group(int id);

int insert_group(group_model group);

int count_groups(void);

int remove_group(int id);

int update_group(int id, group_model group);

int remove_groups_data(void);

#endif //C_GROUP_H
