#include "databases/books.h"
#include "databases/students.h"
#include "utils/menus.h"

int main() {
    printf("Привествую вас в NoSQL БД - DB4ever: 3000. \n");
    BookTable *bookTable = booksLoad(BOOKS_FILE);
    StudentTable *studentTable = studentsLoad(STUDENT_FILE);
    int input = 0;

    while ((input = openRootMenu()) != 0) {
        switch (input) {
            case 1: {
                while ((input = openBookMenu()) != 0)
                    bookTable = doItBook(input, bookTable);
                break;
            }
            case 2: {
                while ((input = openStudentMenu()) != 0)
                    studentTable = doItStudent(input, studentTable);
                break;
            }
            default:
                printf("Такого пункта нет!");
        }
    }

    saveBookTable(bookTable, BOOKS_FILE);
    freeBookTable(bookTable);
    saveStudentTable(studentTable, STUDENT_FILE);
    freeStudentTable(studentTable);
    return 0;
}


