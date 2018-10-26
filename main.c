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

void log_users_to_console(void) {
    printf("\n");
    printf("\n");
    index_file_model *x = get_file_indexes("users.index");
    for (int i = 0; i < 100; i++) {
        if (x[i].id != 0){
            printf("\nid: %d", x[i].id);
            printf(" byte: %08d", x[i].first_byte);
            user_model user = get_user(x[i].id);
            printf(" information: %s %s", user.name, user.surname);
        }
    }
};

void log_groups_users_to_console(void) {
    printf("\n");
    printf("\n");
    index_file_model *x = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++) {
        if (x[i].id != 0) {
            groups_users_model groups_users = get_groups_users(x[i].id);
            printf("user %d in group %d", groups_users.user_id, groups_users.group_id);
            printf("\n");
        }
    }
};

group_model *get_user_groups(int user_id){
    index_file_model *indexes = get_file_indexes("groups_users.index");
    group_model *groups = malloc(sizeof(group_model) * 100);
    int count = 0;
    for (int i = 0; i < 100; i++){
        if (indexes[i].id != 0){
            groups_users_model object = get_groups_users(indexes[i].id);
            if (object.user_id == user_id){
                groups[count] = get_group(object.group_id);
                count++;
            }
        }
    }

    return groups;
}


user_model *get_group_users(int group_id){
    index_file_model *indexes = get_file_indexes("groups_users.index");
    user_model *users = malloc(sizeof(user_model) * 100);
    int count = 0;
    for (int i = 0; i < 100; i++){
        if (indexes[i].id != 0){
            groups_users_model object = get_groups_users(indexes[i].id);
            if (object.group_id == group_id){
                users[count] = get_user(object.user_id);
                count++;
            }
        }
    }

    return users;
}


int main() {
    clear_files();

    insert_user(create_user(18, "Maxym", "Dolynchuk"));
    insert_user(create_user(48, "Vasya", "Ruban"));
    insert_user(create_user(20, "Alina", "Skalkina"));
    insert_user(create_user(2, "Poopock", "Maksimoveech"));

    insert_group(create_group("anekdoty"));
    insert_group(create_group("vasya"));
    insert_group(create_group("anonymny alkashi"));
    insert_group(create_group("fourth"));

    insert_groups_users(create_groups_users(1, 4));
    insert_groups_users(create_groups_users(2, 4));
    insert_groups_users(create_groups_users(3, 4));

    remove_user(2);

    group_model *a = get_user_groups(4);
    for (int i = 0; i < 100; i++){
        if (a[i].group_id != 0){
            printf("%s\n", a[i].name);
        }

    }

    log_users_to_console();
    log_groups_users_to_console();

    return 0;
}
