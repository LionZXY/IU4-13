cmake_minimum_required(VERSION 3.7)
project(IU4_Database)

set(CMAKE_C_STANDARD 99)
file(GLOB_RECURSE SOURCE_FILES
        "databases/*.h"
        "databases/*.c"
        "utils/*.c"
        "utils/*.h"
        "main.c")

add_executable(IU4_Database ${SOURCE_FILES})