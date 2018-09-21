#include "src/binary_io/index.h"
#include <stdio.h>

int main() {
    char * filename = "index";
    char * content = "012345678";

    write(filename, content, sizeof(&content));

    char * result = read_string("index", 0, 5);
    printf("%s", result);
    return 0;
}
