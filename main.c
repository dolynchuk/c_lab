#include "src/io/index.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *USERS_DB_FILENAME = "users.db";

    char *USERS_DB_CONTENT = "Maxym Dolynchuk";
    WriteFileContent(USERS_DB_FILENAME, USERS_DB_CONTENT, strlen(USERS_DB_CONTENT));

    char *result = ReadFileContent(USERS_DB_FILENAME, 0, GetFileContentLength(USERS_DB_FILENAME));
    printf("%s", result);

    return 0;
}
