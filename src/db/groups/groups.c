#include "groups.h"
#include "../groups_users/groups_users.h"

group_model *__get_groups_db__(void) {
    FILE *file = fopen("groups.db", "rb");
    int i = 0;
    group_model *groups = malloc(sizeof(group_model) * 100);
    while (1) {
        fread(&groups[i], sizeof(group_model), 1, file);
        i++;
        if (feof(file)) {
            break;
        }
    }
    fclose(file);
    return groups;
}

int __append_group_to_db__(group_model group) {
    FILE *file = fopen("groups.db", "a");
    int first_byte = (int) ftell(file);

    group_model *object = malloc(sizeof(group_model));
    object->group_id = group.group_id;
    strcpy((char *) object->name, (char *) group.name);


    if (file != NULL) {
        fwrite(object, sizeof(group_model), 1, file);
        fclose(file);
        return first_byte;
    } else {
        fclose(file);
        return 1;
    }
}

group_model *__read_group_from_db__(int seek) {
    FILE *file = fopen("groups.db", "rb");

    group_model *object = malloc(sizeof(group_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(group_model), 1, file);
    }
    fclose(file);
    return object;
}

int __update_group_db__(int seek, group_model *newGroup) {
    FILE *file = fopen("groups.db", "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(newGroup, sizeof(group_model), 1, file);
        fclose(file);
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

//Public API functions

group_model create_group(char *name) {
    group_model *group = malloc(sizeof(group_model));
    strcpy((char *) group->name, name);
    group->group_id = (int)time(NULL) - 1500000000;

    return *group;
}

group_model create_empty_group() {
    group_model *group = malloc(sizeof(group_model));
    strcpy((char *) group->name, "");
    group->group_id = 0;

    return *group;
}


int insert_group(group_model group) {
    int first_byte = __append_group_to_db__(group);
    index_file_model group_index = create_index(group.group_id, first_byte);
    append_index_to_file("groups.index", group_index);
    return 0;
}

group_model get_group(int id) {
    if (id == 0) {
        return create_empty_group();
    }

    index_file_model *indexes = get_file_indexes("groups.index");
    for (int i = 0; i < 100; i++) {
        if (indexes[i].id == id) {
            return *__read_group_from_db__(indexes[i].first_byte);
        }
    }
    return create_empty_group();
}

int update_group(int id, group_model group) {
    group.group_id = id;

    index_file_model *indexes = get_file_indexes("groups.index");
    for (int i = 0; i < 100; i++) {
        if (indexes[i].id == id) {
            __update_group_db__(indexes[i].first_byte, &group);
        }
    }
    return 0;
}

int count_groups(void) {
    return count_indexes("groups.index");
}

int remove_groups_data(void) {
    remove("groups.db");
    remove("groups.index");
    write_file_content("groups.db", "", 0);
    write_file_content("groups.index", "", 0);
    return 0;
}

int remove_group(int id){
    group_model found = get_group(id);
    if (found.group_id == 0) {
        return 1;
    }
    group_model *db = __get_groups_db__();

    group_model *filtered_db = malloc(sizeof(group_model) * 100);
    int filtered_counter = 0;
    for (int i = 0; i < 100; i++) {
        if (db[i].group_id != id) {
            filtered_db[filtered_counter++] = db[i];
        }
    }

    remove_groups_data();

    for (int i = 0; i < 100; i++) {
        if (filtered_db[i].group_id != 0) {
            insert_group(filtered_db[i]);
        }
    }


    index_file_model *indexes = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++){
        groups_users_model groups_users = get_groups_users(indexes[i].id);
        if (groups_users.group_id == id){
            remove_groups_users(indexes[i].id);
        }
    }

    return 0;
}
