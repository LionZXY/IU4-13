//
// Created by lionzxy on 06.05.17.
//
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "../utils/reader.h"

const char *STUDENT_FILE = "students.csv";
const char SEPARATOR_CHAR_STUDENT = ';';

Student studentFromString(char *str) {
    Student student;
    int strIndex = 0;

    student.bookId = nextInt(str, &strIndex, SEPARATOR_CHAR_STUDENT);
    student.surname = nextString(str, &strIndex, SEPARATOR_CHAR_STUDENT);
    student.name = nextString(str, &strIndex, SEPARATOR_CHAR_STUDENT);
    student.patronymic = nextString(str, &strIndex, SEPARATOR_CHAR_STUDENT);
    student.faculty = nextString(str, &strIndex, SEPARATOR_CHAR_STUDENT);
    student.speciality = nextString(str, &strIndex, SEPARATOR_CHAR_STUDENT);

    return student;
}

StudentTable *studentsLoad(const char *filename) {
    StudentTable *table = NULL;
    table = (StudentTable *) calloc(1, sizeof(StudentTable));

    table->tableFile = fopen(filename, "r");
    if (table->tableFile == NULL) {
        printf("Ошибка при открытии файла\n");
        return NULL;
    }
    table->studentSize = 0;
    table->bufferSize = START_BUFFER;
    table->studentArray = (Student *) malloc(sizeof(Student) * (table->bufferSize));
    char buffer[256]; // Пусть максимальная длинна строки будет 256

    while (fgets(buffer, sizeof(buffer), table->tableFile)) {
        addStudentInStudentTable(table, studentFromString(buffer), false);
    }
    printf("Загрузка БД в память завершена! Всего элементов: %d. Сортировка ... ", table->studentSize);
    sortStudentTable(table);
    printf("OK\n");
    fclose(table->tableFile);
    table->tableFile = NULL;
    return table;
}

int removeStudent(StudentTable *table, int bookId) {
    for (int i = 0; i < table->studentSize; i++) {
        if (table->studentArray[i].bookId == bookId) {
            free(table->studentArray[i].speciality);
            free(table->studentArray[i].surname);
            free(table->studentArray[i].name);
            free(table->studentArray[i].patronymic);
            free(table->studentArray[i].faculty);
            if (i != table->studentSize - 1)
                memmove(&table->studentArray[i], &table->studentArray[i + 1],
                        sizeof(Student) * (table->studentSize - i));
            table->studentSize--;
            sortStudentTable(table);
            return 1;
        }
    }
    printf("Невозможно найти студента\n");
    return 0;
}

int addStudentInStudentTable(StudentTable *table, Student student, bool checkExist) {
    if (checkExist && findStudentByID(table, student.bookId) != NULL)
        return 0;
    table->studentArray[table->studentSize++] = student;
    if (table->studentSize == table->bufferSize) {
        table->bufferSize *= 1.5;
        table->studentArray = realloc(table->studentArray, sizeof(Student) * (table->bufferSize));
    }
    if (checkExist)
        sortStudentTable(table); // Чот лень делать правильно.
    return 1;
}

void printStudent(Student *student) {
    printf("Зачетка #%d \nФИО: %s %s %s \n%s:%s \n", student->bookId, student->surname, student->name,
           student->patronymic,
           student->faculty, student->speciality);
}

void printAllStudent(StudentTable *table, bool sorted) {
    if (sorted) {
        if (table->studentSize != table->sortedSize)
            sortStudentTable(table);
        for (int i = 0; i < table->studentSize; i++)
            printStudent(table->sortedStudent[i]);
    } else
        for (int i = 0; i < table->studentSize; i++)
            printStudent(&table->studentArray[i]);

}

void saveStudentTable(StudentTable *table, const char *filename) {
    table->tableFile = fopen(filename, "w");

    if (table->tableFile == NULL) {
        printf("Ошибка при открытии файла");
        return;
    }
    printf("Сохранение БД в файл ... ");
    for (int i = 0; i < table->studentSize; i++) {
        fprintf(table->tableFile, "%d%c%s%c%s%c%s%c%s%c%s\n", table->studentArray[i].bookId,
                SEPARATOR_CHAR_STUDENT, table->studentArray[i].surname,
                SEPARATOR_CHAR_STUDENT, table->studentArray[i].name,
                SEPARATOR_CHAR_STUDENT, table->studentArray[i].patronymic,
                SEPARATOR_CHAR_STUDENT, table->studentArray[i].faculty,
                SEPARATOR_CHAR_STUDENT, table->studentArray[i].speciality);
    }
    printf("OK\n");
    fclose(table->tableFile);
    table->tableFile = NULL;
}

void freeStudentTable(StudentTable *table) {
    if (table->tableFile != NULL)
        fclose(table->tableFile);

    for (int i = 0; i < table->studentSize; i++) {
        free(table->studentArray[i].speciality);
        free(table->studentArray[i].surname);
        free(table->studentArray[i].name);
        free(table->studentArray[i].patronymic);
        free(table->studentArray[i].faculty);
    }
    free(table->studentArray);

    if (table->sortedStudent != NULL) {
        free(table->sortedStudent);
    }
}

void qsort_student(Student **array, int start, int end) {
    int i = start;
    int j = end;
    int middle = (*array[(start + end) / 2]).bookId;
    Student *tmp;

    do {
        while ((*array[i]).bookId > middle) i++;
        while ((*array[j]).bookId < middle) j--;

        if (i <= j) {
            if ((*array[i]).bookId < (*array[j]).bookId) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
        qsort_student(array, i, end);
    if (start < j)
        qsort_student(array, start, j);
}

int binarySearchStudent(Student **sortedArray, int bookId, size_t size) {
    int start = 0, end = 0, curPos = 1;

    // Бежим степенью двойки до ближайшего значения, больше искомого
    while (curPos < size && (*sortedArray[curPos]).bookId < bookId)
        curPos *= 2;;
    if (curPos > size)
        curPos = (int) size - 1;

    if (curPos == 1)
        start = 0;
    else
        start = curPos / 2;
    end = curPos;

    // Стандартный бинарный поиск
    do {
        curPos = (end - start) / 2;
        if (bookId > (*sortedArray[start + curPos]).bookId)
            start = start + curPos;
        else
            end = start + curPos;
    } while (end - start > 1);

    if (end >= size)
        return end - 1;
    else if (abs((int) ((*sortedArray[start]).bookId - bookId)) > abs((int) ((*sortedArray[end]).bookId - bookId)))
        return end;
    else return start;
}

Student *binarySearchTable(StudentTable *table, int bookId) {
    if (table->sortedStudent == NULL) {
        sortStudentTable(table);
    }

    int index = binarySearchStudent(table->sortedStudent, bookId, (size_t) table->studentSize);
    if (table->studentArray[index].bookId == bookId)
        return &table->studentArray[index];
    else return NULL;
}

void sortStudentTable(StudentTable *table) {
    if (table->studentSize == 0)
        return;
    if (table->sortedStudent == NULL) {
        table->sortedStudent = (Student **) calloc((size_t) table->studentSize, sizeof(Student *));
        table->sortedSize = table->studentSize;
        for (int i = 0; i < table->studentSize; i++)
            table->sortedStudent[i] = &table->studentArray[i];
    } else if (table->studentSize != table->sortedSize) {
        table->sortedStudent = realloc(table->sortedStudent, sizeof(Student *) * table->studentSize);
        table->sortedSize = table->studentSize;
        for (int i = 0; i < table->studentSize; i++)
            table->sortedStudent[i] = &table->studentArray[i];
    }
    qsort_student(table->sortedStudent, 0, table->studentSize - 1);
}

Student *findStudentByID(StudentTable *table, int id) {
    if (table->sortedStudent == NULL) {
        for (int i = 0; i < table->studentSize; i++)
            if (id == table->studentArray[i].bookId)
                return &table->studentArray[i];
    } else {
        return binarySearchTable(table, id);
    }
    return NULL;
}

void findAndPrintStudent(StudentTable *table, char *surname) {
    bool isFind = false;
    for (int i = 0; i < table->studentSize; i++) {
        if (strstr(table->studentArray[i].surname, surname) != NULL) {
            isFind = true;
            printStudent(&table->studentArray[i]);
        }
    }
    if (!isFind)
        printf("Таких книг не найдено!");
}
