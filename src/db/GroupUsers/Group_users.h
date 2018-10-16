#ifndef C_GROUP_USERS_H
#define C_GROUP_USERS_H

typedef struct GROUP_USERS_MODEL {
    int group_users_id;
    int deleted;
    int group_id;
    int user_id;
} group_users_model;

group_users_model create_group_users(int group_id, int user_id);

int __append_group_users_to_file(char *filename, group_users_model groupUsers);

group_users_model *__read_group_users_from_file(char *filename, int seek);

int __update_group_users(char *filename, int seek, group_users_model *new_group_users);

int clear_group_users_db();

group_users_model get_group_users(int id);

#endif //C_GROUP_USERS_H
