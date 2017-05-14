#include "databases/books.h"
#include "databases/students.h"
#include "utils/menus.h"

int main() {
    printf("Привествую вас в NoSQL БД - DB4ever: 3000. \n");
    BookTable *bookTable = booksLoad(BOOKS_FILE);
    StudentTable *studentTable = studentsLoad(STUDENT_FILE);
    UserTable *userTable = loadUserTable(USER_FILE);
    int input = 0;
    User *user = auth(userTable);

    while ((input = openRootMenu(user)) != 0) {
        switch (input) {
            case 1: {
                while ((input = openBookMenu(user)) != 0)
                    bookTable = doItBook(input, bookTable);
                break;
            }
            case 2: {
                while ((input = openStudentMenu(user)) != 0)
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
    saveUserTable(userTable, USER_FILE);
    freeUserTable(userTable);
    return 0;
}


