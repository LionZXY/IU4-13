#include <stdlib.h>
#include <time.h>
#include "reader.h"
#include "../databases/books.h"
#include "../databases/students.h"

int openRootMenu() {
    clearscr();
    int input = 0;

    printf("===============================================\n");
    printf("Выберите пункт меню:\n");
    printf("1. Открыть меню книг\n");
    printf("2. Открыть меню студентов\n");
    printf("0. Завершить работу программы\n");
    printf("Выберите пункт меню: ");
    scanf("%d", &input);
    printf("===============================================\n");

    return input;
}

int openBookMenu() {
    clearscr();
    int input = 0;

    printf("===============================================\n");
    printf("Выберите пункт меню:\n");
    printf("1. Добавить новую книгу\n");
    printf("2. Удалить книгу по isbn\n");
    printf("3. Просмотр информации о книге\n");
    printf("4. Вывести информацию о всех книгах (Отсортированно)\n");
    printf("5. Редактировать книгу\n");
    printf("6. Изменить количество книг в библиотеке\n");
    printf("7. Выдать книгу студенту\n");
    printf("8. Принять книгу от студента\n");
    printf("9. Сделать бекап\n");
    printf("10. Востановить БД из бекапа\n");
    printf("11. Поиск по фамилии автора\n");
    printf("0. Вернуться в главное меню\n");
    printf("Выберите пункт меню: ");
    scanf("%d", &input);
    printf("===============================================\n");

    return input;
}

BookTable *doItBook(int input, BookTable *table) {
    long long isbn = 0;
    switch (input) {
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
            printf("ISBN: ");
            scanf("%lli", &isbn);
            break;
        default:
            isbn = 0;
    }

    Book *book = NULL;
    if (isbn != 0) {
        book = findBookByISBN(table, isbn);
        if (book == NULL) {
            printf("Книги с таким isbn не существует\n");
            return table;
        }
    }
    switch (input) {
        case 1: // Добавить книгу
        {
            Book newBook;
            printf("ISBN: ");
            scanf("%lli", &newBook.isbn);
            clearinput();// Костыль, отчищает консоль от \n из предыдущего ввода
            printf("Введите автора: ");
            newBook.author = getLine();
            printf("Введите название книги: ");
            newBook.bookName = getLine();
            printf("Введите сколько в библиотеке числиться книг: ");
            scanf("%d", &newBook.bookCount);
            printf("Введите сколько книг доступно: ");
            scanf("%d", &newBook.bookAvailable);
            if (addBookInBookTable(table, newBook, true))
                printf("Книга добавленна\n");
            else printf("Книга уже существует\n");
            break;
        }
        case 2: // Удалить книгу по isbn
        {
            if (removeBook(table, isbn))
                printf("Книга удалена успешно\n");
            else printf("Ошибка при удалении книги\n");
            break;
        }
        case 3: // Просмотр информации о книге
        {
            printBook(book);
            break;
        }
        case 4: // Вывести информацию о всех книгах (Отсортированно)
        {
            printAllBook(table, true);
            break;
        }
        case 5: // Редактировать книгу
        {
            char *tmpStr = NULL;
            printf("Для того, чтобы не редактировать значение, просто нажмите Enter\n");
            printf("ISBN редактировать нельзя\n");
            clearinput();
            printf("Введите нового автора (%s): ", book->author);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(book->author);
                    book->author = tmpStr;
                } else
                    free(tmpStr);
            }
            printf("Введите новое название книги (%s): ", book->bookName);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(book->bookName);
                    book->bookName = tmpStr;
                } else
                    free(tmpStr);
            }
            printf("Введите сколько книг числятся в библиотеке (%d): ", book->bookCount);
            int tmpVar = getUInt();
            if (tmpVar >= 0) {
                book->bookCount = tmpVar;
            }
            printf("Введите сколько книг доступно (%d): ", book->bookAvailable);
            tmpVar = getUInt();
            if (tmpVar >= 0) {
                book->bookAvailable = tmpVar;
            }
            printf("\nКнига успешно изменена!");
            break;
        }
        case 6: // Изменить количество книг в библиотеке
        {
            int old = book->bookCount;
            printf("Введите новое количество книг: ");
            scanf("%d", &book->bookCount);
            old = book->bookCount - old;
            book->bookAvailable += old;
            break;
        }
        case 7: // Выдать книгу студенту
        {
            if (book->bookAvailable == 0)
                printf("Свободных книг нет!");
            else
                book->bookAvailable--;
            break;
        }
        case 8: // Принять книгу у студента
        {
            book->bookAvailable++;
            break;
        }
        case 9: // Сделать бекап
        {
            char str[150];
            sprintf(str, "books_%li.csv", time(NULL));
            saveBookTable(table, str);
            printf("Бекап сохранен в файл: %s\n", str);
            break;
        }
        case 10: // Востановить из бекапа
        {
            char str[150];
            printf("Введите название файла: ");
            scanf("%s", str);
            BookTable *tmpTable = NULL;
            tmpTable = booksLoad(str);
            if (tmpTable != NULL) {
                freeBookTable(table);
                return tmpTable;
            } else {
                printf("Не удалось востановить файлы. Произошла какая-то ошибка");
            }
            break;
        }
        case 11: // Поиск по фамилии автора
        {
            char str[150];
            printf("Введите автора: ");
            scanf("%s", str);
            findAndPrintBook(table, str);
            break;
        }
        default:
            printf("Такого пункта нет");
    }
    printf("Нажмите [Enter] для продолжения.\n");
    clearinput();
    getchar();
    return table;
}

int openStudentMenu() {
    clearscr();
    int input = 0;

    printf("===============================================\n");
    printf("Выберите пункт меню:\n");
    printf("1. Добавить студента\n");
    printf("2. Удалить студента\n");
    printf("3. Редактировать студента\n");
    printf("4. Просмотр информации по студенту\n");
    printf("5. Сделать бекап\n");
    printf("6. Востановить БД из бекапа\n");
    printf("7. Поиск по фамилии студента\n");
    printf("0. Вернуться в главное меню\n");
    printf("Выберите пункт меню: ");
    scanf("%d", &input);
    printf("===============================================\n");

    return input;
}

StudentTable *doItStudent(int input, StudentTable *table) {
    int id = 0;
    switch (input) {
        case 2:
        case 3:
        case 4:
            printf("Номер зачетки: ");
            scanf("%d", &id);
            break;
        default:
            id = 0;
    }
    Student *student = NULL;
    if (id != 0) {
        student = findStudentByID(table, id);
        if (student == NULL) {
            printf("Книги с таким isbn не существует\n");
            return table;
        }
    }

    switch (input) {
        case 1: { // Добавить студента
            Student newStudent;
            printf("Номер зачетки: ");
            scanf("%d", &newStudent.bookId);
            clearinput();// Костыль, отчищает консоль от \n из предыдущего ввода
            printf("Введите фамилию: ");
            newStudent.surname = getLine();
            printf("Введите имя: ");
            newStudent.name = getLine();
            printf("Введите отчество: ");
            newStudent.patronymic = getLine();
            printf("Введите факультет: ");
            newStudent.faculty = getLine();
            printf("Введите специальность: ");
            newStudent.speciality = getLine();

            if (addStudentInStudentTable(table, newStudent, true))
                printf("Студент добавленн\n");
            else printf("Студент уже существует\n");
            break;
        }
        case 2: // Удалить студента по номеру зачетки
        {
            if (removeStudent(table, id))
                printf("Студент удален успешно\n");
            else printf("Ошибка при удалении студента\n");
            break;
        }
        case 3: // Редактировать студента
        {
            char *tmpStr = NULL;
            printf("Для того, чтобы не редактировать значение, просто нажмите Enter\n");
            printf("ID редактировать нельзя\n");
            clearinput();
            printf("Введите новую фамилию (%s): ", student->surname);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(student->surname);
                    student->surname = tmpStr;
                } else
                    free(tmpStr);
            }
            printf("Введите новое имя (%s): ", student->name);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(student->name);
                    student->name = tmpStr;
                } else
                    free(tmpStr);
            }
            printf("Введите новое отчество (%s): ", student->patronymic);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(student->patronymic);
                    student->patronymic = tmpStr;
                } else
                    free(tmpStr);
            }
            printf("Введите новый факультет (%s): ", student->faculty);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(student->faculty);
                    student->faculty = tmpStr;
                } else
                    free(tmpStr);
            }
            printf("Введите новую специальность (%s): ", student->speciality);
            tmpStr = getLine();
            if (tmpStr != NULL) {
                if (tmpStr[0] != '\0') {
                    free(student->speciality);
                    student->speciality = tmpStr;
                } else
                    free(tmpStr);
            }

            printf("\nДанные студента успешно изменены!");
            break;
        }
        case 4: // Просмотр информации о книге
        {
            printStudent(student);
            break;
        }
        case 5: // Сделать бекап
        {
            char str[150];
            sprintf(str, "student_%li.csv", time(NULL));
            saveStudentTable(table, str);
            printf("Бекап сохранен в файл: %s\n", str);
            break;
        }
        case 6: // Востановить из бекапа
        {
            char str[150];
            printf("Введите название файла: ");
            scanf("%s", str);
            StudentTable *tmpTable = NULL;
            tmpTable = studentsLoad(str);
            if (tmpTable != NULL) {
                freeStudentTable(table);
                return tmpTable;
            } else {
                printf("Не удалось востановить файлы. Произошла какая-то ошибка");
            }
            break;
        }
        case 7: // Поиск по фамилии
        {
            char str[150];
            printf("Введите фамилию: ");
            scanf("%s", str);
            findAndPrintStudent(table, str);
            break;
        }
        default:
            printf("Нет такого пункта меню");
    }
    printf("Нажмите [Enter] для продолжения.\n");
    clearinput();
    getchar();
    return table;
}