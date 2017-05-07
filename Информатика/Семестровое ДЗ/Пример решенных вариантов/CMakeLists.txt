cmake_minimum_required(VERSION 3.7)
project(IU4_Database)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c reader.c databases/books.c databases/books.h reader.h databases/students.c databases/students.h)
add_executable(IU4_Database ${SOURCE_FILES})