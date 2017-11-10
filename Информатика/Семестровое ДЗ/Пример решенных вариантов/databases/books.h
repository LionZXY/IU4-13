#ifndef IU4_DATABASE_BOOKS_H
#define IU4_DATABASE_BOOKS_H

#include <stdio.h>
#include <stdbool.h>

extern const char *BOOKS_FILE;
extern const char SEPARATOR_CHAR;

typedef struct Book {
    long long isbn;
    char *author;
    char *bookName;
    int bookCount;
    int bookAvailable;
} Book;

typedef struct BookTable {
    FILE *tableFile;
    int bookSize;
    int bufferSize;
    Book *bookArray;

    int sortedSize;
    Book **sortedBook;
} BookTable;

BookTable *booksLoad(const char *filename);

void freeBookTable(BookTable *table);

void saveBookTable(BookTable *table, const char *filename);

int addBookInBookTable(BookTable *table, Book book, bool checkExist);

void sortBookTable(BookTable *table);

void printBook(Book *book);

Book *findBookByISBN(BookTable *table, long long isbn);

void printAllBook(BookTable *table, bool sorted);

int removeBook(BookTable *table, long long isbn);

void findAndPrintBook(BookTable *table, char *author);

#endif //IU4_DATABASE_BOOKS_H
