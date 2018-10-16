#ifndef C_GROUP_H
#define C_GROUP_H

typedef struct GROUP_MODEL {
    int group_id;
    int deleted;
    char name[50];
} group_model;

group_model create_group(char *name);

int __append_group_to_file(char *filename, group_model group);

group_model *__read_group_from_file(char *filename, int seek);

int __update_group(char *filename, int seek, group_model *new_group);

int clear_group_db();

group_model get_group(int id);

#endif //C_GROUP_H
