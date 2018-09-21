#include "index.h"
#include <stdio.h>

///write - Write string to file.
///@param filename - Name of file to write.
///@param content - String with content to write.
///@param content_length - Number of chars in string.
int write(char *filename, char *content, int content_length) {
    FILE * file = fopen(filename, "w");
    fwrite(content, sizeof(char), content_length, file);
    fclose(file);

    return 0;
}

///read_string - Read string from file.
///@param filename - Name of file to read from.
///@param start - Start position to read.
///@param length - Length of string to read.
char *read_string(char *filename, int start, int length) {
    unsigned char buffer[length];

    FILE * file = fopen(filename, "r");
    fseek(file, start, SEEK_SET);
    fread(buffer, sizeof(buffer), 1, file);
    fclose(file);

    return buffer;
}


