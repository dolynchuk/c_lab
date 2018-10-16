#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

///WriteFileContent - Write string to file.
///@param filename - Name of file to write.
///@param content - String with content to write.
///@param content_length - Number of chars in string.
int write_file_content(char *filename, char *content, size_t content_length) {
    FILE *file = fopen(filename, "w");

    fwrite(content, sizeof(char), content_length, file);
    fclose(file);

    return 0;
}

///ReadFileContent - Write string to file.
///@param filename - Name of file to write.
///@param start - starting point.
///@param content_length - Number of chars in string.
char *read_file_content(char *filename, int start, size_t content_length) {
    FILE *file = fopen(filename, "r");

    char buffer[content_length];
    buffer[content_length - 1] = '\0';
    fseek(file, start * sizeof(char), SEEK_SET);
    fgets(buffer, sizeof(buffer) + 1, file);
    fclose(file);

    return buffer;
}


///GetFileContentLength - Calculate file content length in bytes.
///@param filename - Name of file;
size_t get_file_content_length(char *filename) {
    FILE *file = fopen(filename, "r");
    int fd = fileno(file);
    struct stat buf;
    fstat(fd, &buf);
    return buf.st_size;
}
