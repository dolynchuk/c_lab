#ifndef C_INDEXFILE_H
#define C_INDEXFILE_H

typedef struct INDEX_FILE_MODEL {
    int id;
    int first_byte;
} index_file_model;

index_file_model create_index(int id, int first_byte);

int append_index_to_file(char *filename, index_file_model index);

index_file_model *read_index_from_file(char *filename, int seek);

#endif //C_INDEXFILE_H
