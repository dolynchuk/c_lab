#include "src/binary_io/index.h"

int main() {
    char filename[] = "index";
    char content[] = "[[1,2],[2,3],[3, 23444]]";

    write(filename, content, sizeof(content));
    return 0;
}
