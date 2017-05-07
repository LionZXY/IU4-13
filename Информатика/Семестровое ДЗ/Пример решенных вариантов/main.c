
#include <stdlib.h>
#include <time.h>
#include "databases/books.h"
#include "reader.h"

int openMenu(long long *isbn);


BookTable *doIt(int input, long long isbn, BookTable *table);

int main() {
    printf("Привествую вас в NoSQL БД - DB4ever: 3000. \n");
    BookTable *bookTable = booksLoad(BOOKS_FILE);
    int input = 0;
    long long isbn = 0;

    while ((input = openMenu(&isbn)) != 0) {
        bookTable = doIt(input, isbn, bookTable);
    }

    saveBookTable(bookTable, BOOKS_FILE);
    freeBookTable(bookTable);
    return 0;
}

int openMenu(long long *isbn) {
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
    printf("0. Завершить работу программы\n");
    printf("Выберите пункт меню: ");
    scanf("%d", &input);
    switch (input) {
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
            printf("ISBN: ");
            scanf("%lli", isbn);
            break;
        default:
            *isbn = 0;
    }
    return input;
}

BookTable *doIt(int input, long long isbn, BookTable *table) {
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
            getchar(); // Костыль, отчищает консоль от \n из предыдущего ввода
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
            getchar();
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
    }
    return table;
}