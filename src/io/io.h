#ifndef C_IO_H
#define C_IO_H
#include <wchar.h>

int WriteFileContent(char *filename, char *content, unsigned long contentLength);
char *ReadFileContent(char *filename, int start, unsigned long contentLength);
unsigned long GetFileContentLength(char *filename);

#endif //C_IO_H
