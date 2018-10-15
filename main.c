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
    int created_before_first_byte = __get_index_first_byte(user.user_id, "user.index");
    if (created_before_first_byte != -1) {
        update_user("user.db", created_before_first_byte, &user);
        index_file_model user_index = create_index(user.user_id, created_before_first_byte);
        append_index_to_file("user.index", user_index);
    } else {
        int first_byte = append_user_to_file("user.db", user);
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
    int created_before_first_byte = __get_index_first_byte(group.group_id, "group.index");
    if (created_before_first_byte != -1) {
        update_group("group.db", created_before_first_byte, &group);
        index_file_model group_index = create_index(group.group_id, created_before_first_byte);
        append_index_to_file("group.index", group_index);
    } else {
        int first_byte = append_group_to_file("group.db", group);
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
    int created_before_first_byte = __get_index_first_byte(group_users.group_users_id, "group_users.index");
    if (created_before_first_byte != -1) {
        update_group_users("group_users.db", created_before_first_byte, &group_users);
        index_file_model group_users_index = create_index(group_users.group_users_id, created_before_first_byte);
        append_index_to_file("group_users.index", group_users_index);
    } else {
        int first_byte = append_group_users_to_file("group_users.db", group_users);
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
    write_file_content("user.db", NULL, 0);
    write_file_content("group.db", NULL, 0);
    write_file_content("group_users.db", NULL, 0);
    write_file_content("user.index", NULL, 0);
    write_file_content("group.index", NULL, 0);
    write_file_content("group_users.index", NULL, 0);
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

    return 0;
}
