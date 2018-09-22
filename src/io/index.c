#include "index.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


///WriteFileContent - Write string to file.
///@param filename - Name of file to write.
///@param content - String with content to write.
///@param contentLength - Number of chars in string.
int WriteFileContent(char *filename, char *content, unsigned long contentLength) {
    FILE *file = fopen(filename, "w");

    fwrite(content, sizeof(char), contentLength, file);
    fclose(file);

    return 0;
}

///ReadFileContent - Write string to file.
///@param filename - Name of file to write.
///@param start - starting point.
///@param contentLength - Number of chars in string.
char *ReadFileContent(char *filename, int start, unsigned long contentLength) {
    FILE *file = fopen(filename, "r");

    char buffer[contentLength];
    buffer[contentLength - 1] = '\0';
    fseek(file, start * sizeof(char), SEEK_SET);
    fgets(buffer, sizeof(buffer) + 1, file);
    fclose(file);

    return buffer;
}


///GetFileContentLength - Calculate file content length in bytes.
///@param filename - Name of file;
unsigned long GetFileContentLength(char *filename){
    FILE *file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    long lengthOfFile = ftell(file);
    fclose(file);

    return (unsigned long)lengthOfFile;
}
