#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "../reader.h"

const char *BOOKS_FILE = "books.csv";
const char SEPARATOR_CHAR = ';';

Book fromString(char *str) {
    Book book;
    int strIndex = 0;

    book.isbn = nextLong(str, &strIndex, SEPARATOR_CHAR);
    book.author = nextString(str, &strIndex, SEPARATOR_CHAR);
    book.bookName = nextString(str, &strIndex, SEPARATOR_CHAR);
    book.bookCount = nextInt(str, &strIndex, SEPARATOR_CHAR);
    book.bookAvailable = nextInt(str, &strIndex, SEPARATOR_CHAR);

    return book;
}

BookTable *booksLoad(const char *filename) {
    BookTable *table = NULL;
    table = (BookTable *) calloc(1, sizeof(BookTable));

    table->tableFile = fopen(filename, "r");
    if (table->tableFile == NULL) {
        printf("Ошибка при открытии файла\n");
        return NULL;
    }
    table->bookSize = 0;
    table->bufferSize = START_BUFFER;
    table->bookArray = (Book *) malloc(sizeof(Book) * (table->bufferSize));
    char buffer[256]; // Пусть максимальная длинна строки будет 256

    while (fgets(buffer, sizeof(buffer), table->tableFile)) {
        addBookInBookTable(table, fromString(buffer), false);
    }
    printf("Загрузка БД в память завершена! Всего элементов: %d. Сортировка ... ", table->bookSize);
    sortBookTable(table);
    printf("OK\n");
    fclose(table->tableFile);
    table->tableFile = NULL;
    return table;
}

int removeBook(BookTable *table, long long isbn) {
    for (int i = 0; i < table->bookSize; i++) {
        if (table->bookArray[i].isbn == isbn) {
            free(table->bookArray[i].bookName);
            free(table->bookArray[i].author);
            if (i != table->bookSize - 1)
                memmove(&table->bookArray[i], &table->bookArray[i + 1], sizeof(Book) * (table->bookSize - i));
            table->bookSize--;
            sortBookTable(table);
            return 1;
        }
    }
    printf("Невозможно найти книгу\n");
    return 0;
}

int addBookInBookTable(BookTable *table, Book book, bool checkExist) {
    if (checkExist && findBookByISBN(table, book.isbn) != NULL)
        return 0;
    table->bookArray[table->bookSize++] = book;
    if (table->bookSize == table->bufferSize) {
        table->bufferSize *= 1.5;
        table->bookArray = realloc(table->bookArray, sizeof(Book) * (table->bufferSize));
    }
    if (checkExist)
        sortBookTable(table); // Чот лень делать правильно.
    return 1;
}

void printBook(Book *book) {
    printf("Книга ISBN: %s | %lli \nАвтор: %s \nДоступно книг: %d/%d \n", book->bookName, book->isbn, book->author,
           book->bookAvailable, book->bookCount);
}

void printAllBook(BookTable *table, bool sorted) {
    if (sorted) {
        if (table->bookSize != table->sortedSize)
            sortBookTable(table);
        for (int i = 0; i < table->bookSize; i++)
            printBook(table->sortedBook[i]);
    } else
        for (int i = 0; i < table->bookSize; i++)
            printBook(&table->bookArray[i]);

}

void saveBookTable(BookTable *table, const char *filename) {
    table->tableFile = fopen(filename, "w");

    if (table->tableFile == NULL) {
        printf("Ошибка при открытии файла");
        return;
    }
    printf("Сохранение БД в файл ... ");
    for (int i = 0; i < table->bookSize; i++) {
        fprintf(table->tableFile, "%lli%c%s%c%s%c%d%c%d\n",
                table->bookArray[i].isbn, SEPARATOR_CHAR, table->bookArray[i].author, SEPARATOR_CHAR,
                table->bookArray[i].bookName, SEPARATOR_CHAR, table->bookArray[i].bookCount, SEPARATOR_CHAR,
                table->bookArray[i].bookAvailable);
    }
    printf("OK\n");
    fclose(table->tableFile);
    table->tableFile = NULL;
}

void freeBookTable(BookTable *table) {
    if (table->tableFile != NULL)
        fclose(table->tableFile);

    for (int i = 0; i < table->bookSize; i++) {
        free(table->bookArray[i].author);
        free(table->bookArray[i].bookName);
    }
    free(table->bookArray);

    if (table->sortedBook != NULL) {
        free(table->sortedBook);
    }
}

void qsort_book(Book **array, int start, int end) {
    int i = start;
    int j = end;
    long long middle = (*array[(start + end) / 2]).isbn;
    Book *tmp;

    do {
        while ((*array[i]).isbn > middle) i++;
        while ((*array[j]).isbn < middle) j--;

        if (i <= j) {
            if ((*array[i]).isbn < (*array[j]).isbn) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
        qsort_book(array, i, end);
    if (start < j)
        qsort_book(array, start, j);
}

int binarySearchBook(Book **sortedArray, long long isbn, size_t size) {
    int start = 0, end = 0, curPos = 1;

    // Бежим степенью двойки до ближайшего значения, больше искомого
    while (curPos < size && (*sortedArray[curPos]).isbn < isbn)
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
        if (isbn > (*sortedArray[start + curPos]).isbn)
            start = start + curPos;
        else
            end = start + curPos;
    } while (end - start > 1);

    if (end >= size)
        return end - 1;
    else if (abs((int) ((*sortedArray[start]).isbn - isbn)) > abs((int) ((*sortedArray[end]).isbn - isbn)))
        return end;
    else return start;
}

Book *binarySearch(BookTable *table, long long isbn) {
    if (table->sortedBook == NULL) {
        sortBookTable(table);
    }

    int index = binarySearchBook(table->sortedBook, isbn, (size_t) table->bookSize);
    if (table->bookArray[index].isbn == isbn)
        return &table->bookArray[index];
    else return NULL;
}

void sortBookTable(BookTable *table) {
    if (table->bookSize == 0)
        return;
    if (table->sortedBook == NULL) {
        table->sortedBook = (Book **) calloc((size_t) table->bookSize, sizeof(Book *));
        table->sortedSize = table->bookSize;
        for (int i = 0; i < table->bookSize; i++)
            table->sortedBook[i] = &table->bookArray[i];
    } else if (table->bookSize != table->sortedSize) {
        table->sortedBook = realloc(table->sortedBook, sizeof(Book *) * table->bookSize);
        table->sortedSize = table->bookSize;
        for (int i = 0; i < table->bookSize; i++)
            table->sortedBook[i] = &table->bookArray[i];
    }
    qsort_book(table->sortedBook, 0, table->bookSize - 1);
}

Book *findBookByISBN(BookTable *table, long long isbn) {
    if (table->sortedBook == NULL) {
        for (int i = 0; i < table->bookSize; i++)
            if (isbn == table->bookArray[i].isbn)
                return &table->bookArray[i];
    } else {
        return binarySearch(table, isbn);
    }
    return NULL;
}

void findAndPrintBook(BookTable *table, char *author) {
    bool isFind = false;
    for (int i = 0; i < table->bookSize; i++) {
        if (strstr(table->bookArray[i].author, author) != NULL) {
            isFind = true;
            printBook(&table->bookArray[i]);
        }
    }
    if (!isFind)
        printf("Таких книг не найдено!");
}