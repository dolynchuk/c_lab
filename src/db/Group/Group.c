#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../io/io.h"
#include "../../db/indexfile.h"

int group_id_counter = 0;
size_t __group_index_size = 8;

group_model create_group(char *name) {
    group_model group;
    strcpy((char *) group.name, name);
    group.group_id = group_id_counter++;
    group.deleted = 0;
    return group;
}

group_model get_group(int id) {
    int first_byte = -1;
    for (int i = 0; i < __group_index_size * 1000; i += __group_index_size) {
        index_file_model *index = read_index_from_file("group.index", i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    if (first_byte == -1) {
        return create_group("");
    }
    return *__read_group_from_file("group.db", first_byte);
}

int __append_group_to_file(char *filename, group_model group) {
    FILE *file = fopen(filename, "a");
    int first_byte = (int) ftell(file);

    group_model *object = malloc(sizeof(group_model));
    object->group_id = group.group_id;
    object->deleted = group.deleted;
    strcpy((char *) object->name, (char *) group.name);

    if (file != NULL) {
        fwrite(object, sizeof(group_model), 1, file);
        fclose(file);
        return first_byte;
    } else {
        return 1;
    }
}

group_model *__read_group_from_file(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    group_model *object = malloc(sizeof(group_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(group_model), 1, file);
        fclose(file);
    }
    return object;
}

int __update_group(char *filename, int seek, group_model *new_group) {
    FILE *file = fopen(filename, "r+");

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fwrite(new_group, sizeof(group_model), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

int clear_group_db() {
    write_file_content("group.db", NULL, 0);
    write_file_content("group.index", NULL, 0);
}