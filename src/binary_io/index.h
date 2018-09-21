#ifndef C_BINARYIO_H
#define C_BINARYIO_H

int write(char * filename, char * content, int content_length);
char * read_string(char * filename, int start, int length);

#endif //C_BINARYIO_H
