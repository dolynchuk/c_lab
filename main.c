#include "src/io/io.h"
#include <string.h>
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
    index_file_model *x = get_file_indexes("users.index");
    for (int i = 0; i < 100; i++) {
        if (x[i].id != 0){
            printf("\nuser_id: %d, ", x[i].id);
            user_model user = get_user(x[i].id);
            printf("name: %s, surname: %s, age: %d", user.name, user.surname, user.age);
        }
    }
};

void log_groups_users_to_console(void) {
    index_file_model *x = get_file_indexes("groups_users.index");
    for (int i = 0; i < 100; i++) {
        if (x[i].id != 0) {
            printf("\ngroups_users_id: %d, ", x[i].id);
            groups_users_model groups_users = get_groups_users(x[i].id);
            printf("group_id: %d, user_id: %d", groups_users.group_id, groups_users.user_id);
        }
    }
};

void log_groups_to_console(void) {
    index_file_model *x = get_file_indexes("groups.index");
    for (int i = 0; i < 100; i++) {
        if (x[i].id != 0){
            printf("\nid: %d, ", x[i].id);
            group_model group = get_group(x[i].id);
            printf("name: %s", group.name);
        }
    }
};

char *tolowercase(char *string){
    char *new_string = malloc(strlen(string) * sizeof(char));
    for (int i = 0; i < strlen(string); i++){
        new_string[i] = tolower(string[i]);
    }
    return new_string;
}

int startswith(char *pre, char *str) {
    size_t lenpre = strlen(pre),
            lenstr = strlen(str);
    return lenstr < lenpre
           ? 0
           : strncmp(pre, str, lenpre) == 0;
}

user_model parse_user_from_command(char *command){
    char *ss = strstr(command, "user");
    char *res = malloc(sizeof(char) * strlen(ss) - 4);
    int res_count = 0;
    for (int i = 5; i < strlen(ss); i++){
        res[res_count++] = ss[i];
    }
    char * first_space = strchr(res, ' ');
    int first_space_index = (int)(first_space - res);
    char *name = malloc(sizeof(char) * first_space_index);
    int name_count = 0;
    for (int i = 0; i < first_space_index; i++){
        name[name_count++] = res[i];
    }
    char *next = first_space + 1;
    char * next_space = strchr(next, ' ');
    int next_space_index = (int)(next_space - next);
    char *surname = malloc(sizeof(char) * next_space_index);
    int surname_count = 0;
    for (int i = 0; i < next_space_index; i++){
        surname[surname_count++] = next[i];
    }
    int age = atoi(next_space + 1);

    user_model user = create_user(age, name, surname);
    return user;
}

group_model parse_group_from_command(char *command){
    char *ss = strstr(command, "group");
    char *res = malloc(sizeof(char) * strlen(ss) - 5);
    int res_count = 0;
    for (int i = 5; i < strlen(ss); i++){
        res[res_count++] = ss[i];
    }
    group_model group = create_group(res);
    return group;
}

groups_users_model parse_groups_users_from_command(char *command){
    char *ss = strstr(command, "groups_users");
    int res_count = 0;
    char *res = malloc(sizeof(char) * strlen(ss) - 13);
    for (int i = 13; i < strlen(ss); i++){
        res[res_count++] = ss[i];
    }
    char * first_space = strchr(res, ' ');
    int first_space_index = (int)(first_space - res);
    char *group_id = malloc(sizeof(char) * first_space_index);
    int group_id_count = 0;
    for (int i = 0; i < first_space_index; i++){
        group_id[group_id_count++] = res[i];
    }

    groups_users_model groups_users = create_groups_users(atoi(group_id), atoi(first_space + 1));
    return groups_users;
}

char *extract(const char *string, int start, int end){
    char *result = malloc(sizeof(char) * (end - start));
    int count = 0;
    int i = start;

    while(i < end) {
        result[count++] = string[i++];
    }

    return result;
}

int main() {
    char *raw_input = malloc(sizeof(char) * 200);

    while(1){
        printf("\nenter command: \n");
        scanf("%[^\n]%*c", raw_input);

        char *command = tolowercase(raw_input);
        int command_length = (int)strlen(command);

        if (startswith("exit", command)){
            break;
        }

        if (startswith("select users for group", command)) {
            char *id_string = malloc(sizeof(char) * 50);
            printf("what group? ");
            scanf("%[^\n]%*c", id_string);
            index_file_model *x = get_file_indexes("groups_users.index");
            for (int i = 0; i < 100; i++) {
                groups_users_model groups_users = get_groups_users(x[i].id);
                if (groups_users.group_id == atoi(id_string) && atoi(id_string) != 0) {
                    user_model user = get_user(groups_users.user_id);
                    printf(
                            "\ngroup_id: %d, name: %s, surname: %s, age: %d",
                            user.user_id,
                            user.name,
                            user.surname,
                            user.age
                    );
                }
            }
            continue;
        }

        if (startswith("select groups for user", command)) {
            char *id_string = malloc(sizeof(char) * 50);
            printf("what user? ");
            scanf("%[^\n]%*c", id_string);
            index_file_model *x = get_file_indexes("groups_users.index");
            for (int i = 0; i < 100; i++) {
                groups_users_model groups_users = get_groups_users(x[i].id);
                if (groups_users.user_id == atoi(id_string) && atoi(id_string) != 0) {
                    group_model group = get_group(groups_users.group_id);
                    printf("\ngroup_id: %d, name: %s", group.group_id, group.name);
                }
            }
            continue;
        }

        if (startswith("select user", command)){
            char *param = extract(command, 12, command_length);
            if (param[0] == '*'){
                log_users_to_console();
                continue;
            }
            int number = atoi(param);
            user_model selected = get_user(number);
            printf(
                "\nuser_id: %d, name: %s, surname: %s, age: %d\n",
                selected.user_id,
                selected.name,
                selected.surname,
                selected.age
            );
            continue;
        }

        if (startswith("select groups_users", command)){
            char *param = extract(command, 20, command_length);
            if (param[0] == '*'){
                log_groups_users_to_console();
                continue;
            }
            int number = atoi(param);
            groups_users_model selected = get_groups_users(number);
            printf(
                "\ngroups_users_id: %d, group_id: %d, user_id: %d",
                selected.groups_users_id,
                selected.group_id,
                selected.user_id
            );
            continue;
        }

        if (startswith("select group", command)){
            char *param = extract(command, 13, command_length);
            if (param[0] == '*'){
                log_groups_to_console();
                continue;
            }
            int number = atoi(param);
            group_model selected = get_group(number);
            printf(
                "\ngroup_id: %d, name: %s",
                selected.group_id,
                selected.name
            );
            continue;
        }

        if (startswith("insert user", command)){
            user_model user = parse_user_from_command(command);
            printf("created user with id %d", user.user_id);
            insert_user(user);
            continue;
        }

        if (startswith("update user", command)){
            user_model user = parse_user_from_command(command);
            printf("what user you want to update? ");
            char* id_string = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", id_string);
            update_user(atoi(id_string), user);
            printf("user %d updated.\n", user.user_id);
            continue;
        }

        if (startswith("insert groups_users", command)){
            groups_users_model groups_users = parse_groups_users_from_command(command);
            printf("created groups_users with id %d", groups_users.groups_users_id);
            insert_groups_users(groups_users);
            continue;
        }

        if (startswith("update groups_users", command)){
            groups_users_model groups_users = parse_groups_users_from_command(command);
            printf("what groups_users you want to update? ");
            char* id_string = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", id_string);
            update_groups_users(atoi(id_string), groups_users);
            printf("groups_users %d updated.\n", groups_users.groups_users_id);
            continue;
        }

        if (startswith("insert group", command)){
            group_model group = parse_group_from_command(command);
            printf("created group with id %d", group.group_id);
            insert_group(group);
            continue;
        }

        if (startswith("update group", command)){
            group_model group = parse_group_from_command(command);
            printf("what group you want to update? ");
            char* id_string = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", id_string);
            update_group(atoi(id_string), group);
            printf("group %d updated.\n", group.group_id);
            continue;
        }

        if (startswith("count users", command)){
            printf("users count - %d", count_users());
            continue;
        }

        if (startswith("count groups_users", command)){
            printf("users count - %d", count_groups_users());
            continue;
        }

        if (startswith("count groups", command)){
            printf("users count - %d", count_groups());
            continue;
        }

        if (startswith("remove user", command)) {
            printf("what user you want to remove? ");
            char *id_string = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", id_string);
            remove_user(atoi(id_string));
            printf("user %s removed", id_string);
            continue;
        }

        if (startswith("remove groups_users", command)) {
            printf("what groups_users you want to remove? ");
            char *id_string = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", id_string);
            remove_groups_users(atoi(id_string));
            printf("groups_users %s removed", id_string);
            continue;
        }

        if (startswith("remove group", command)) {
            printf("what groups_users you want to remove? ");
            char *id_string = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", id_string);
            remove_group(atoi(id_string));
            printf("group %s removed", id_string);
            continue;
        }

        if (startswith("clear database", command)) {
            printf("are you sure? ");
            char *answer = malloc(sizeof(char) * 50);
            scanf("%[^\n]%*c", answer);
            if (answer[0] == 'y') {
                clear_files();
            }
        }
    }

    return 0;
}
