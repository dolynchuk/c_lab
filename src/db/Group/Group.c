#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int group_id_counter = 0;

group_model create_group(char *name) {
    group_model group;
    strcpy((char *) group.name, name);
    group.group_id = group_id_counter++;
    group.deleted = 0;
    return group;
}

int append_group_to_file(char *filename, group_model group) {
    FILE *file = fopen(filename, "a");

    group_model *object = malloc(sizeof(group_model));
    object->group_id = group.group_id;
    object->deleted = group.deleted;
    strcpy((char *) object->name, (char *) group.name);

    if (file != NULL) {
        fwrite(object, sizeof(group_model), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

group_model *read_group_from_file(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    group_model *object = malloc(sizeof(group_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(group_model), 1, file);
        fclose(file);
    }
    return object;
}

int update_group(char *filename, int seek, group_model *new_group) {
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
