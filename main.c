#include "src/io/index.h"

#include "src/db/User/index.h"

int main() {
    char *USERS_DB_FILENAME = "users.db";

    struct UserModel user = CreateUser(18, "Maxym", "Dolynchuk");

    char *userString = URLEncodeUser(user);
    WriteFileContent(USERS_DB_FILENAME, userString, strlen(userString));
    printf("%s", userString);
    return 0;
}
