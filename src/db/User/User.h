#ifndef C_USER_H
#define C_USER_H

typedef struct USER_MODEL {
    int user_id;
    int age;
    int deleted;
    char *name[50];
    char *surname[50];
} user_model;

user_model create_user(int age, char *name, char *surname);

int __append_user_to_file(char *filename, user_model user);

user_model *__read_user_from_file(char *filename, int seek);

int __update_user(char *filename, int seek, user_model *newUser);

int clear_user_db();

user_model get_user(int id);

#endif //C_USER_H
