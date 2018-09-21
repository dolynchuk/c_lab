#include "index.h"
#include <stdio.h>

int write(char* filename, char* content, int content_length){
    size_t char_size = sizeof(char);

    FILE *out;
    out = fopen(filename, "w");
    fwrite(content, char_size, content_length, out);
    fclose(out);

    return 0;
}
