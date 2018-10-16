#include "src/io/io.h"
#include <stdio.h>
#include <string.h>

#include "src/db/User/User.h"
#include "src/db/Group/Group.h"
#include "src/db/GroupUsers/Group_users.h"
#include "src/io/io.h"
#include "src/db/indexfile.h"

size_t index_size = 8;

//size_t user_size = 816;
//size_t group_size = 60;
//size_t group_users_size = 16;

int __get_index_first_byte(int id, char *index_filename) {
    int first_byte = -1;
    for (int i = 0; i < index_size * 1000; i += index_size) {
        index_file_model *index = read_index_from_file(index_filename, i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    return first_byte;
}


int count_users() {
    return ((int) get_file_content_length("user.index") / (int) index_size) - 1;
}

int insert_user(user_model user) {
    int created_before_first_byte = __get_index_first_byte(user.user_id, "user.index");
    if (created_before_first_byte != -1) {
        __update_user("user.db", created_before_first_byte, &user);
        index_file_model user_index = create_index(user.user_id, created_before_first_byte);
        append_index_to_file("user.index", user_index);
    } else {
        int first_byte = __append_user_to_file("user.db", user);
        index_file_model user_index = create_index(user.user_id, first_byte);
        append_index_to_file("user.index", user_index);
    }
    return 0;
}

int delete_user(int id) {
    user_model user = get_user(id);
    user.deleted = 1;
    insert_user(user);
}


int count_group() {
    return (int) get_file_content_length("group.index") / (int) index_size;
}

int insert_group(group_model group) {
    int created_before_first_byte = __get_index_first_byte(group.group_id, "group.index");
    if (created_before_first_byte != -1) {
        __update_group("group.db", created_before_first_byte, &group);
        index_file_model group_index = create_index(group.group_id, created_before_first_byte);
        append_index_to_file("group.index", group_index);
    } else {
        int first_byte = __append_group_to_file("group.db", group);
        index_file_model group_index = create_index(group.group_id, first_byte);
        append_index_to_file("group.index", group_index);
    }
    return 0;
}

int delete_group(int id) {
    group_model group = get_group(id);
    group.deleted = 1;
    insert_group(group);

    //TODO: delete group_users for this group id
}

int count_group_users() {
    return (int) get_file_content_length("group_users.index") / (int) index_size;
}

int insert_group_users(group_users_model group_users) {
    int created_before_first_byte = __get_index_first_byte(group_users.group_users_id, "group_users.index");
    if (created_before_first_byte != -1) {
        __update_group_users("group_users.db", created_before_first_byte, &group_users);
        index_file_model group_users_index = create_index(group_users.group_users_id, created_before_first_byte);
        append_index_to_file("group_users.index", group_users_index);
    } else {
        int first_byte = __append_group_users_to_file("group_users.db", group_users);
        index_file_model user_index = create_index(group_users.group_users_id, first_byte);
        append_index_to_file("group_users.index", user_index);
    }
    return 0;
}

int delete_group_users(int id) {
    group_users_model group_users = get_group_users(id);
    group_users.deleted = 1;
    insert_group_users(group_users);
}

void clear_files(void) {
    clear_user_db();
    clear_group_db();
    clear_group_users_db();
}

int main() {
    clear_files();

    user_model user1 = create_user(18, "Maxym", "Dolynchuk");
    insert_user(user1);
    user_model user2 = create_user(20, "Alina", "Skalkina");
    insert_user(user2);

    group_model group1 = create_group("anekdoty");
    insert_group(group1);
    group_model group2 = create_group("znakomstva");
    insert_group(group2);

    //Max joined both anekdoty and znakomstva
    //and Alina joined only znakomstva
    group_users_model groupUsers1 = create_group_users(0, 0);
    insert_group_users(groupUsers1);
    group_users_model groupUsers2 = create_group_users(0, 1);
    insert_group_users(groupUsers2);
    group_users_model groupUsers3 = create_group_users(1, 1);
    insert_group_users(groupUsers3);

    delete_user(1);

    //check results
    printf("%d", get_group_users(0).group_id);
    printf("%d", get_group_users(0).user_id);
    printf("\n");
    printf((char *) get_user(1).name);
    printf(" ");
    printf((char *) get_user(1).surname);
    printf("\n");
    printf("%d", get_user(1).deleted);
    printf("\n");
    printf((char *) get_group(1).name);

    printf("\n");
    printf("users count: ");
    printf("%d", count_users());

    printf("\n");
    printf("groups count: ");
    printf("%d", count_group());

    printf("\n");
    printf("group-users count: ");
    printf("%d", count_group_users());

    return 0;
}
