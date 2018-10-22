#include "src/io/io.h"
#include "src/db/users/users.h"
#include "src/db/groups/groups.h"
#include "src/db/group_users/group_users.h"
#include "src/db/index_file/index_file.h"

void clear_files(void) {
    remove_users_data();
    remove_groups_data();
    clear_group_users_db();
}

void log_users_to_console() {
    printf("\n");
    index_file_model *x = get_file_indexes("users.index");
    for (int i = 0; i < 100; i++) {
        printf("\nid: %d", x[i].id);
        printf(" byte: %08d", x[i].first_byte);
        user_model user = get_user(x[i].id);
        printf(" information: %s %s", user.name, user.surname);
    }
};

int main() {
    clear_files();

    user_model user1 = create_user(18, "Maxym", "Dolynchuk");
    insert_user(user1);

    user_model user2 = create_user(18, "Vasya", "Ruban");
    insert_user(user2);

    user_model user3 = create_user(20, "Alina", "Skalkina");
    insert_user(user3);

    remove_user(2);

    user_model user4 = create_user(2, "AAAAA", "BBBBB");
    insert_user(user4);


    update_user(4, create_user(12, "Oleg", "Vinnyk"));



    user_model found = get_user(3);
    printf("\nname of user with id 3 - %s", found.name);
    printf("\ntotal users count - %d", count_users());





    group_model anekdoty = create_group("anekdoty");
    insert_group(anekdoty);

    update_group(1, create_group("vasya"));

    printf("\n groups count - %d", count_groups());

    log_users_to_console();

    return 0;
}
