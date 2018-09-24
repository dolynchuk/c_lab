cmake_minimum_required(VERSION 3.12)
project(c C)

set(CMAKE_C_STANDARD 99)

add_executable(c main.c src/io/index.c src/io/index.h src/db/Group/index.c src/db/Group/index.h src/db/User/index.c src/db/User/index.h src/db/GroupUsers/index.c src/db/GroupUsers/index.h)
