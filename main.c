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

int main() {
    //CLEAR_FILES
    write_file_content("user.db", NULL, 0);
    write_file_content("group.db", NULL, 0);
    write_file_content("group_users.db", NULL, 0);

    //INITIAL DATA
    user_model user1 = create_user(18, "Maxym", "Dolynchuk");
    user_model user2 = create_user(20, "Alina", "Skalkina");
    index_file_model user1Index = create_index(user1.user_id, 0);
    index_file_model user2Index = create_index(user2.user_id, (int) user_size);
    append_user_to_file("user.db", user1);
    append_user_to_file("user.db", user2);
    append_index_to_file("user.index", user1Index);
    append_index_to_file("user.index", user2Index);


    group_model group1 = create_group("anekdoty");
    group_model group2 = create_group("znakomstva");
    index_file_model group1Index = create_index(group1.group_id, 0);
    index_file_model group2Index = create_index(group2.group_id, (int) group_size);
    append_group_to_file("group.db", group1);
    append_group_to_file("group.db", group2);
    append_index_to_file("group.index", group1Index);
    append_index_to_file("group.index", group2Index);


    //Max joined both anekdoty and znakomstva
    //and Alina joined only znakomstva
    group_users_model groupUsers1 = create_group_users(0, 0);
    group_users_model groupUsers2 = create_group_users(0, 1);
    group_users_model groupUsers3 = create_group_users(1, 1);
    index_file_model groupUsers1Index = create_index(groupUsers1.group_users_id, 0);
    index_file_model groupUsers2Index = create_index(groupUsers2.group_users_id, (int) group_users_size);
    index_file_model groupUsers3Index = create_index(groupUsers3.group_users_id, (int) group_users_size * 2);
    append_group_users_to_file("group_users.db", groupUsers1);
    append_group_users_to_file("group_users.db", groupUsers2);
    append_group_users_to_file("group_users.db", groupUsers3);
    append_index_to_file("group_users.index", groupUsers1Index);
    append_index_to_file("group_users.index", groupUsers2Index);
    append_index_to_file("group_users.index", groupUsers3Index);


    printf("%d", get_group_users(2).group_id);
    printf("%d", get_group_users(2).user_id);

    printf("\n");

    printf(get_user(1).name);
    printf(" ");
    printf(get_user(1).surname);

    return 0;
}
