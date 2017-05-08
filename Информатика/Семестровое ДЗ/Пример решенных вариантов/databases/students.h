#ifndef IU4_DATABASE_STUDENTS_H
#define IU4_DATABASE_STUDENTS_H

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


StudentTable *studentsLoad(const char *filename);

void freeStudentTable(StudentTable *table);

void saveStudentTable(StudentTable *table, const char *filename);

int addStudentInStudentTable(StudentTable *table, Student student, bool checkExist);

void sortStudentTable(StudentTable *table);

void printStudent(Student *book);

Student *findStudentByID(StudentTable *table, int id);

void printAllStudent(StudentTable *table, bool sorted);

int removeStudent(StudentTable *table, int id);

void findAndPrintStudent(StudentTable *table, char *surname);

#endif //IU4_DATABASE_BOOKS_H
