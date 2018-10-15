cmake_minimum_required(VERSION 3.12)
project(c C)

set(CMAKE_C_STANDARD 99)

add_executable(c main.c src/io/io.c src/io/io.h src/db/Group/Group.c src/db/Group/Group.h src/db/User/User.c src/db/User/User.h src/db/GroupUsers/Group_users.c src/db/GroupUsers/Group_users.h src/db/indexfile.c src/db/indexfile.h)
