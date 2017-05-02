#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

char *nextWord(FILE *file);

int main(int argc, char *argv[]) {
    //if (argc < 2) {
    //    printf("Необходимо указать имя файла");
    //    return 0;
    //}
    FILE *file = fopen("File1.txt", "r");

    if (file == NULL) {
        printf("Невозможно открыть файл");
        return 0;
    }
    char *word = NULL;

    tHashMap hashMap;
    initHashMap(&hashMap);
    tHashMapElement *tmpElement;

    while ((word = nextWord(file)) != NULL) {
        tmpElement = get(word, &hashMap);
        if (tmpElement == NULL) {
            add(&hashMap, word, 1);
        } else {
            tmpElement->element++;
        }
        free(word);
    }

    printHash(&hashMap);
    removeHash(&hashMap);

    if (file != NULL)
        fclose(file);
    return 0;
}

const int BUFFER_SIZE = 128;

char *nextWord(FILE *file) {
    int bufferSize = BUFFER_SIZE;
    int count = 0;
    char *word = (char *) calloc((size_t) bufferSize, sizeof(char));
    int tmpChar = 0;
    while ((tmpChar = fgetc(file)) != EOF && tmpChar != ' ' && tmpChar != ',' && tmpChar != '\n') {
        word[count++] = (char) tmpChar;
        if (count == bufferSize) {
            bufferSize *= 1.5;
            word = (char *) realloc(word, bufferSize * sizeof(char));
        }
    }
    word[count] = 0;
    if (count == 0) {
        free(word);
        word = NULL;
    }
    return word;
}