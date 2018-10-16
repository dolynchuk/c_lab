#include "Group_users.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../io/io.h"
#include "../../db/indexfile.h"

// autoIncrement for group primary key
int group_users_id_counter = 0;
size_t __group_users_index_size = 8;

group_users_model create_group_users(int group_id, int user_id) {
    group_users_model group_users;
    group_users.group_users_id = group_users_id_counter++;
    group_users.group_id = group_id;
    group_users.user_id = user_id;
    group_users.deleted = 0;
    return group_users;
}

group_users_model get_group_users(int id) {
    int first_byte = -1;
    for (int i = 0; i < __group_users_index_size * 1000; i += __group_users_index_size) {
        index_file_model *index = read_index_from_file("group_users.index", i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    if (first_byte == -1) {
        return create_group_users(0, 0);
    }
    return *__read_group_users_from_file("group_users.db", first_byte);
}

int __append_group_users_to_file(char *filename, group_users_model group_users) {
    FILE *file = fopen(filename, "a");
    int first_byte = (int) ftell(file);

    group_users_model *object = malloc(sizeof(group_users_model));
    object->group_users_id = group_users.group_users_id;
    object->deleted = group_users.deleted;
    object->group_id = group_users.group_id;
    object->user_id = group_users.user_id;

    if (file != NULL) {
        fwrite(object, sizeof(group_users_model), 1, file);
        fclose(file);
        return first_byte;
    } else {
        return 1;
    }
}

group_users_model *__read_group_users_from_file(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    group_users_model *object = malloc(sizeof(group_users_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(group_users_model), 1, file);
        fclose(file);
    }
    return object;
}

int __update_group_users(char *filename, int seek, group_users_model *new_group_users) {
    FILE *file = fopen(filename, "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(new_group_users, sizeof(group_users_model), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

int clear_group_users_db() {
    write_file_content("group_users.db", NULL, 0);
    write_file_content("group_users.index", NULL, 0);
}


