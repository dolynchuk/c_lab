#ifndef C_BINARYIO_H
#define C_BINARYIO_H
#include <wchar.h>

int WriteFileContent(char *filename, char *content, unsigned long contentLength);
char *ReadFileContent(char *filename, int start, unsigned long contentLength);
unsigned long GetFileContentLength(char *filename);

#endif //C_BINARYIO_H
