//
// Created by lionzxy on 06.05.17.
//
#include <stdlib.h>
#include "students.h"
#include "../reader.h"

const char *STUDENT_FILE = "students.csv";
const char SEPARATOR_CHAR_STUDENT = ';';

StudentTable *booksLoad(const char *filename) {
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
        addBook(table, fromString(buffer));
    }
    printf("Загрузка БД в память завершена! Всего элементов: %d. Сортировка ... ", table->bookSize);
    sortBookTable(table);
    printf("OK\n");
    fclose(table->tableFile);
    table->tableFile = NULL;
    return table;
}
