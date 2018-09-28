#include "src/io/io.h"
#include <stdio.h>
#include <string.h>

#include "src/db/User/User.h"
#include "src/db/Group/Group.h"
#include "src/db/GroupUsers/GroupUsers.h"

int main() {
    struct UserModel user1 = CreateUser(18, "Maxym", "Dolynchuk");

    AppendUserToFile("users.db", user1);

    struct UserModel user2 = CreateUser(18, "ALIN", "SKALKINA");

    UpdateUser("users.db", 0, &user2);

    struct UserModel *read = ReadUserFromFile("users.db", 0);

    printf((char *)read->name);

    return 0;
}
