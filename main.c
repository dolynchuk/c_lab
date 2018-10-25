#include "src/io/io.h"
#include "src/db/users/users.h"
#include "src/db/groups/groups.h"
#include "src/db/groups_users/groups_users.h"
#include "src/db/index_file/index_file.h"

void clear_files(void) {
    remove_users_data();
    remove_groups_data();
    remove_groups_users_data();
}

void log_users_to_console() {
    printf("\n");
    printf("\n");
    index_file_model *x = get_file_indexes("users.index");
    for (int i = 0; i < 100; i++) {
        printf("\nid: %d", x[i].id);
        printf(" byte: %08d", x[i].first_byte);
        user_model user = get_user(x[i].id);
        printf(" information: %s %s", user.name, user.surname);
    }
};

void log_groups_users_to_console() {
    printf("\n");
    printf("\n");
    index_file_model *x = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++) {
        groups_users_model groups_users = get_groups_users(x[i].id);
        printf(" user %d in group %d", groups_users.user_id, groups_users.group_id);
        printf("\n");
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

    user_model user4 = create_user(2, "AAAAA", "BBBBB");
    insert_user(user4);

    insert_groups_users(create_groups_users(100, 1));
    insert_groups_users(create_groups_users(1000, 2));
    insert_groups_users(create_groups_users(1221, 3));

    remove_user(2);

    log_users_to_console();
    log_groups_users_to_console();

    return 0;
}
