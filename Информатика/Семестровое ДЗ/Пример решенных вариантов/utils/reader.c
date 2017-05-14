#include <stdlib.h>
#include <libio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "reader.h"

const int START_BUFFER = 16;

char *nextString(char *str, int *curIndex, const char separator) {
    int size = 0;
    int bufferSize = START_BUFFER;
    char *tmp = (char *) malloc(sizeof(char) * bufferSize);

    while (str[*curIndex] != separator && str[*curIndex] != '\0' && str[*curIndex] != EOF && str[*curIndex] != '\n') {
        tmp[size++] = str[*curIndex];
        if (size == bufferSize) {
            bufferSize *= 1.5;
            tmp = (char *) realloc(tmp, sizeof(char) * bufferSize);
        }
        (*curIndex)++;
    }
    (*curIndex)++;
    tmp[size] = '\0';
    return tmp;
}

long long nextLong(char *str, int *curIndex, const char separator) {
    long long var = 0;
    while (str[*curIndex] != separator && str[*curIndex] != '\0' && str[*curIndex] != EOF && str[*curIndex] != '\n') {
        var *= 10;
        var += str[*curIndex] - '0';
        (*curIndex)++;
    }
    (*curIndex)++;
    return var;
}

int nextInt(char *str, int *curIndex, const char separator) {
    int var = 0;
    while (str[*curIndex] != separator && str[*curIndex] != '\0' && str[*curIndex] != EOF && str[*curIndex] != '\n') {
        var *= 10;
        var += str[*curIndex] - '0';
        (*curIndex)++;
    }
    (*curIndex)++;
    return var;
}


char *getLine() {
    int size = 0;
    int bufferSize = START_BUFFER;
    char *tmp = (char *) malloc(sizeof(char) * bufferSize);
    int tmpChar = 0;
    while ((tmpChar = getchar()) != '\n') {
        if (tmpChar == EOF)
            continue;
        tmp[size++] = (char) tmpChar;
        if (size == bufferSize) {
            bufferSize *= 1.5;
            tmp = (char *) realloc(tmp, sizeof(char) * bufferSize);
        }
    }
    tmp[size] = '\0';
    return tmp;
}

char *nextWord() {
    int bufferSize = START_BUFFER;
    int count = 0;
    char *word = (char *) calloc((size_t) bufferSize, sizeof(char));
    int tmpChar = 0;
    while ((tmpChar = getchar()) != EOF && tmpChar != '\n') {
        if (tmpChar == ' ')
            continue;
        word[count++] = (char) tmpChar;
        if (count == bufferSize) {
            bufferSize *= 1.5;
            word = (char *) realloc(word, bufferSize * sizeof(char));
        }
    }
    word[count] = '\0';
    if (count == 0) {
        free(word);
        word = NULL;
    }
    return word;
}

int getUInt() {
    int var = 0;
    bool nonNull = false;
    int tmpChar;
    while ((tmpChar = getchar()) != '\n') {
        if (tmpChar == EOF)
            continue;
        var *= 10;
        var += tmpChar - '0';
        nonNull = true;
    }
    if (nonNull)
        return var;
    else return -1;
}

void clearinput() {
    while (getchar() != '\n'); // option TWO to clean stdin
}

void clearscr(void) {
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
//add some other OSes here if needed
#else
#error "OS not supported."
    //you can also throw an exception indicating the function can't be used
#endif
}

/**
 * Строка должна быть нультерменированная!
 * @param str
 * @return
 */
char *copyString(char *str) {
    char *toReturn = malloc(strlen(str) * sizeof(char) + 1);
    toReturn = strcpy(toReturn, str);
    return toReturn;
}