#include "src/io/io.h"
#include <stdio.h>
#include <string.h>

#include "src/db/User/User.h"
#include "src/db/Group/Group.h"
#include "src/db/GroupUsers/GroupUsers.h"

int main() {
    //first user
    struct UserModel user1 = CreateUser(18, "Maxym", "Dolynchuk");

    //first group
    struct GroupModel group1 = CreateGroup("anekdoty");

    //relate user with group
    struct GroupUsersModel groupUsersModel = CreateGroupUsers(0, 0);


    char *user1String = URLEncodeUser(user1);

    struct UserModel user1parsed = URLDecodeUser(user1String);


    printf("%d", user1parsed.userID);

    return 0;
}
