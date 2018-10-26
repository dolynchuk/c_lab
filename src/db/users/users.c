#include "users.h"

int user_id_counter = 1;

user_model *__get_users_db__(void) {
    FILE *file = fopen("users.db", "rb");
    int i = 0;
    user_model *users = malloc(sizeof(user_model) * 100);
    while (1) {
        fread(&users[i], sizeof(user_model), 1, file);
        i++;
        if (feof(file)) {
            break;
        }
    }
    fclose(file);
    return users;
}

int __append_user_to_db__(user_model user) {
    FILE *file = fopen("users.db", "a");
    int first_byte = (int) ftell(file);

    user_model *object = malloc(sizeof(user_model));
    object->user_id = user.user_id;
    object->age = user.age;
    strcpy((char *) object->name, (char *) user.name);
    strcpy((char *) object->surname, (char *) user.surname);

    if (file != NULL) {
        fwrite(object, sizeof(user_model), 1, file);
        fclose(file);
        return first_byte;
    } else {
        fclose(file);
        return 1;
    }
}

user_model *__read_user_from_db__(int seek) {
    FILE *file = fopen("users.db", "rb");

    user_model *object = malloc(sizeof(user_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(user_model), 1, file);
    }
    fclose(file);
    return object;
}

int __update_user_db__(int seek, user_model *newUser) {
    FILE *file = fopen("users.db", "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(newUser, sizeof(user_model), 1, file);
        fclose(file);
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

//Public API functions

user_model create_user(int age, char *name, char *surname) {
    user_model *user = malloc(sizeof(user_model));
    user->age = age;
    strcpy((char *) user->name, name);
    strcpy((char *) user->surname, surname);
    user->user_id = user_id_counter++;
    return *user;
}

int insert_user(user_model user) {
    int first_byte = __append_user_to_db__(user);
    index_file_model user_index = create_index(user.user_id, first_byte);
    append_index_to_file("users.index", user_index);
    return 0;
}

user_model get_user(int id) {
    if (id == 0) {
        return create_user(0, "", "");
    }

    index_file_model *indexes = get_file_indexes("users.index");
    for (int i = 0; i < 100; i++) {
        if (indexes[i].id == id) {
            return *__read_user_from_db__(indexes[i].first_byte);
        }
    }
    return create_user(0, "", "");
}

int update_user(int id, user_model user) {
    user.user_id = id;

    index_file_model *indexes = get_file_indexes("users.index");
    for (int i = 0; i < 100; i++) {
        if (indexes[i].id == id) {
            __update_user_db__(indexes[i].first_byte, &user);
        }
    }
    return 0;
}

int count_users(void) {
    return count_indexes("users.index");
}

int remove_users_data(void) {
    remove("users.db");
    remove("users.index");
    write_file_content("users.db", "", 0);
    write_file_content("users.index", "", 0);
    return 0;
}

int remove_user(int id) {
    user_model found = get_user(id);
    if (found.user_id == 0) {
        return 1;
    }
    user_model *users_db = __get_users_db__();

    user_model *filtered_users_db = malloc(sizeof(user_model) * 100);
    int filtered_counter = 0;
    for (int i = 0; i < 100; i++) {
        if (users_db[i].user_id != id) {
            filtered_users_db[filtered_counter++] = users_db[i];
        }
    }

    remove_users_data();

    for (int i = 0; i < 100; i++) {
        if (filtered_users_db[i].user_id != 0) {
            insert_user(filtered_users_db[i]);
        }
    }

    index_file_model *indexes = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++){
        groups_users_model groups_users = get_groups_users(indexes[i].id);
        if (groups_users.user_id == id){
            remove_groups_users(indexes[i].id);
        }
    }

    return 0;
}
