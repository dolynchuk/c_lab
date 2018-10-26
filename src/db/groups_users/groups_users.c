#include "groups_users.h"

int groups_users_id_counter = 1;

groups_users_model *__get_groups_users_db__(void) {
    FILE *file = fopen("groups_users.db", "rb");
    int i = 0;
    groups_users_model *groups_users = malloc(sizeof(groups_users_model) * 100);
    while (1) {
        fread(&groups_users[i], sizeof(groups_users_model), 1, file);
        i++;
        if (feof(file)) {
            break;
        }
    }
    fclose(file);
    return groups_users;
}

int __append_groups_users_to_db__(groups_users_model groups_users) {
    FILE *file = fopen("groups_users.db", "a");
    int first_byte = (int) ftell(file);

    groups_users_model *object = malloc(sizeof(groups_users_model));
    object->group_id = groups_users.group_id;
    object->user_id = groups_users.user_id;
    object->groups_users_id = groups_users.groups_users_id;


    if (file != NULL) {
        fwrite(object, sizeof(groups_users_model), 1, file);
        fclose(file);
        return first_byte;
    } else {
        fclose(file);
        return 1;
    }
}

groups_users_model *__read_groups_users_from_db__(int seek) {
    FILE *file = fopen("groups_users.db", "rb");

    groups_users_model *object = malloc(sizeof(groups_users_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(groups_users_model), 1, file);
    }
    fclose(file);
    return object;
}

int __update_groups_users_db__(int seek, groups_users_model *newGroupsUsers) {
    FILE *file = fopen("groups_users.db", "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(newGroupsUsers, sizeof(groups_users_model), 1, file);
        fclose(file);
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

//Public API functions

groups_users_model create_groups_users(int group_id, int user_id) {
    groups_users_model *groups_users = malloc(sizeof(groups_users_model));
    groups_users->group_id = group_id;
    groups_users->user_id = user_id;
    groups_users->groups_users_id = groups_users_id_counter++;

    return *groups_users;
}

int insert_groups_users(groups_users_model groups_users) {
    int first_byte = __append_groups_users_to_db__(groups_users);
    index_file_model groups_users_index = create_index(groups_users.groups_users_id, first_byte);
    append_index_to_file("groups_users.index", groups_users_index);
    return 0;
}

groups_users_model get_groups_users(int id) {
    if (id == 0) {
        return create_groups_users(0, 0);
    }

    index_file_model *indexes = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++) {
        if (indexes[i].id == id) {
            return *__read_groups_users_from_db__(indexes[i].first_byte);
        }
    }
    return create_groups_users(0, 0);
}

int update_groups_users(int id, groups_users_model groups_users) {
    groups_users.groups_users_id = id;

    index_file_model *indexes = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++) {
        if (indexes[i].id == id) {
            __update_groups_users_db__(indexes[i].first_byte, &groups_users);
        }
    }
    return 0;
}

int count_groups_users(void) {
    return count_indexes("groups_users.index");
}

int remove_groups_users_data(void) {
    remove("groups_users.db");
    remove("groups_users.index");
    write_file_content("groups_users.db", "", 0);
    write_file_content("groups_users.index", "", 0);
    return 0;
}

int remove_groups_users(int id){
    groups_users_model found = get_groups_users(id);
    if (found.groups_users_id == 0) {
        return 1;
    }
    groups_users_model *db = __get_groups_users_db__();

    groups_users_model *filtered_db = malloc(sizeof(groups_users_model) * 100);
    int filtered_counter = 0;
    for (int i = 0; i < 100; i++) {
        if (db[i].groups_users_id != id) {
            filtered_db[filtered_counter++] = db[i];
        }
    }

    remove_groups_users_data();

    for (int i = 0; i < 100; i++) {
        if (filtered_db[i].groups_users_id != 0) {
            insert_groups_users(filtered_db[i]);
        }
    }

    return 0;
}
