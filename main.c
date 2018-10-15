#include "src/io/io.h"
#include <stdio.h>
#include <string.h>

#include "src/db/User/User.h"
#include "src/db/Group/Group.h"
#include "src/db/GroupUsers/Group_users.h"
#include "src/io/io.h"
#include "src/db/indexfile.h"

size_t user_size = 816;
size_t group_size = 60;
size_t group_users_size = 16;
size_t index_size = 8;


user_model get_user(int id) {
    int first_byte = -1;
    for (int i = 0; i < index_size * 1000; i += index_size) {
        index_file_model *index = read_index_from_file("user.index", i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    if (first_byte == -1) {
        return create_user(0, "", "");
    } else return *read_user_from_file("user.db", first_byte);
}


int insert_user(user_model user) {
    int first_byte = append_user_to_file("user.db", user);
    index_file_model user_index = create_index(user.user_id, first_byte);
    append_index_to_file("user.index", user_index);
    return 0;
}

group_model get_group(int id) {
    int first_byte = -1;
    for (int i = 0; i < index_size * 1000; i += index_size) {
        index_file_model *index = read_index_from_file("group.index", i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    if (first_byte == -1) {
        return create_group("");
    } else return *read_group_from_file("group.db", first_byte);
}

int insert_group(group_model group) {
    int first_byte = append_group_to_file("group.db", group);
    index_file_model group_index = create_index(group.group_id, first_byte);
    append_index_to_file("group.index", group_index);
    return 0;
}


group_users_model get_group_users(int id) {
    int first_byte = -1;
    for (int i = 0; i < index_size * 1000; i += index_size) {
        index_file_model *index = read_index_from_file("group_users.index", i);
        if (index->id == id) {
            first_byte = index->first_byte;
            break;
        }
    }
    if (first_byte == -1) {
        return create_group_users(0, 0);
    } else return *read_group_users_from_file("group_users.db", first_byte);
}

int insert_group_users(group_users_model group_users) {
    int first_byte = append_group_users_to_file("group_users.db", group_users);
    index_file_model group_users_index = create_index(group_users.group_users_id, first_byte);
    append_index_to_file("group_users.index", group_users_index);
    return 0;
}

int main() {
    //CLEAR_FILES
    write_file_content("user.db", NULL, 0);
    write_file_content("group.db", NULL, 0);
    write_file_content("group_users.db", NULL, 0);

    //INITIAL DATA
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

    printf("%d", get_group_users(0).group_id);
    printf("%d", get_group_users(0).user_id);

    printf("\n");

    printf((char *) get_user(1).name);
    printf(" ");
    printf((char *) get_user(1).surname);


    printf("\n");
    printf((char *) get_group(1).name);

    return 0;
}
