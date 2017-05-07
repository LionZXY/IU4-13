#ifndef IU4_DATABASE_BOOKS_H
#define IU4_DATABASE_BOOKS_H

#include <stdio.h>
#include <stdbool.h>

extern const char *STUDENT_FILE;
extern const char SEPARATOR_CHAR_STUDENT;

typedef struct Student {
    int bookId;
    char *surname;
    char *name;
    char *patronymic;
    char *faculty;
    char *speciality;
} Student;

typedef struct StudentTable {
    FILE *tableFile;
    int studentSize;
    int bufferSize;
    Student *studentArray;

    int sortedSize;
    Student **sortedStudent;
} StudentTable;

#endif //IU4_DATABASE_BOOKS_H
