#include "index_file.h"

index_file_model create_index(int id, int first_byte) {
    index_file_model index;
    index.id = id;
    index.first_byte = first_byte;
    return index;
}

int append_index_to_file(char *filename, index_file_model index) {
    FILE *file = fopen(filename, "a");

    index_file_model *object = malloc(sizeof(index_file_model));
    object->id = index.id;
    object->first_byte = index.first_byte;

    if (file != NULL) {
        fwrite(object, sizeof(index_file_model), 1, file);
        fclose(file);
        return 0;
    } else {
        return 1;
    }
}

index_file_model *read_index_from_file(char *filename, int seek) {
    FILE *file = fopen(filename, "rb");

    index_file_model *object = malloc(sizeof(index_file_model));

    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(object, sizeof(index_file_model), 1, file);
        fclose(file);
    }
    return object;
}
