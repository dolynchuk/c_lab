cmake_minimum_required(VERSION 3.12)
project(c C)

set(CMAKE_C_STANDARD 99)

add_executable(c main.c src/io/io.c src/io/io.h src/db/groups/groups.c src/db/groups/groups.h src/db/users/users.c src/db/users/users.h src/db/group_users/group_users.c src/db/group_users/group_users.h src/db/index_file/index_file.c src/db/index_file/index_file.h)
