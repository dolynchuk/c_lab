#include "src/io/index.h"
#include <stdio.h>
#include <string.h>

#include "src/db/User/index.h"

int main() {

    struct UserModel user1 = CreateUser(18, "Maxym", "Dolynchuk");

    char *user1String = URLEncodeUser(user1);

    struct UserModel user1parsed = URLDecodeUser(user1String);


    printf("%d", user1parsed.userID);

    return 0;
}
