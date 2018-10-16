#include "User.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../io/io.h"
#include "../../db/indexfile.h"

int user_id_counter = 0;
size_t __user_index_size = 8;

user_model get_user(int id) {
    int first_byte = -1;
    for (int i = 0; i < __user_index_size * 1000; i += __user_index_size) {
        index_file_model *index = read_index_from_file("user.index", i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    if (first_byte == -1) {
        return create_user(0, "", "");
    }
    return *__read_user_from_file("user.db", first_byte);
}

user_model create_user(int age, char *name, char *surname) {
    user_model user;
    user.age = age;
    strcpy((char *) user.name, name);
    strcpy((char *) user.surname, surname);
    user.user_id = user_id_counter++;
    user.deleted = 0;
    return user;
}

int __append_user_to_file(char *filename, user_model user) {
    FILE *file = fopen(filename, "a");
    int first_byte = (int) ftell(file);

    user_model *object = malloc(sizeof(user_model));
    object->user_id = user.user_id;
    object->deleted = user.deleted;
    object->age = user.age;
    strcpy((char *) object->name, (char *) user.name);
    strcpy((char *) object->surname, (char *) user.surname);

    if (file != NULL) {
        fwrite(object, sizeof(user_model), 1, file);
        fclose(file);
        return first_byte;
    } else {
        return 1;
    }
}

user_model *__read_user_from_file(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    user_model *object = malloc(sizeof(user_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(user_model), 1, file);
        fclose(file);
    }
    return object;
}

int __update_user(char *filename, int seek, user_model *newUser) {
    FILE *file = fopen(filename, "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(newUser, sizeof(user_model), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

int clear_user_db() {
    write_file_content("users.db", NULL, 0);
    write_file_content("user.index", NULL, 0);
}
