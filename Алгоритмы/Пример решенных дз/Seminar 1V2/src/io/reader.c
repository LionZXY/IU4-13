#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "reader.h"

/**
 * @file reader.c
 * @author LionZXY
 * @project Seminar
 * @date 08.09.17
 * @email nikita@kulikof.ru
 **/
// Private
const int BUFFER_SIZE = 16;


// Private
bool isValid(int symbol) {
    return symbol == '-'
           || (symbol >= '0' && symbol <= '9')
           || symbol == EOF;
}

// Private
int flushToNumber() {
    int tmpChar = 0;
    while (!isValid(tmpChar = getchar()) && tmpChar != '\n');
    return tmpChar;
}

int getInt(int *out) {
    int var = 0;
    bool nonNull = false;
    bool isNegative = false;
    int tmpChar = flushToNumber();

    if (tmpChar == '\n') {
        return EOF;
    }

    do {
        if (tmpChar != EOF) {
            if (tmpChar != '-') {
                var *= 10;
                var += tmpChar - '0';
                nonNull = true;
            } else {
                isNegative = true;
            }
        } else {
            return EOF;
        }
    } while (isValid(tmpChar = getchar()));

    if (isNegative) {
        *out = var * -1;
    } else {
        *out = var;
    }

    if (tmpChar == '\n') {
        if (nonNull) {
            return EOF;
        } else {
            return EXIT_FAILURE;
        }
    }

    if (nonNull == false) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

/**
 *
 * @param out Int array. Need free after using!
 * @param outSize Array size
 * @return
 */
int getIntArray(ArrayList *outList) {
    ArrayList list;
    list.bufferSize = BUFFER_SIZE;
    list.array = malloc(sizeof(int) * list.bufferSize);
    list.realSize = 0;

    int tmpVar;

    while (getInt(&tmpVar) == EXIT_SUCCESS) {
        list.array[list.realSize++] = tmpVar;
        if (list.realSize == list.bufferSize) {
            list.bufferSize = (int) (list.bufferSize * 1.5);
            list.array = realloc(list.array, (size_t) list.bufferSize);
        }
    }

    *outList = list;

    return EXIT_SUCCESS;
}

char *copyString(char *str) {
    char *toReturn = malloc(strlen(str) * sizeof(char) + 1);
    toReturn = strcpy(toReturn, str);
    return toReturn;
}
