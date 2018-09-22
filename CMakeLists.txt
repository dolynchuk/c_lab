cmake_minimum_required(VERSION 3.12)
project(c C)

set(CMAKE_C_STANDARD 99)

add_executable(c main.c src/io/index.c src/io/index.h)
