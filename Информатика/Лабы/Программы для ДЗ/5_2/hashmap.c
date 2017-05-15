#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "hashmap.h"

void initHashMap(tHashMap *hashMp) {
    hashMp->size = 0;
    hashMp->bufferSize = firstBufferSize;
    hashMp->elementArray = (tHashMapElement **) calloc(firstBufferSize, sizeof(tHashMapElement *));
}

int binarySearch(long hashStr, tHashMap *hsh) {
    int average_index = 0, // переменная для хранения индекса среднего элемента массива
            first_index = 0, // индекс первого элемента в массиве
            last_index = hsh->size - 1; // индекс последнего элемента в массиве
    if (last_index == -1) return 0;
    while (first_index < last_index) {
        average_index = first_index + (last_index - first_index) / 2; // меняем индекс среднего значения
        if (hashStr <= hsh->elementArray[average_index]->hashStr)
            last_index = average_index;
        else
            first_index = average_index + 1;
    }
    return last_index;
}

void addElement(tHashMap *hash, tHashMapElement *element) {
    if (hash->size == hash->bufferSize) {
        tHashMapElement **newArray = (tHashMapElement **) malloc(
                sizeof(tHashMapElement *) * (hash->bufferSize + firstBufferSize));
        for (int i = 0; i < hash->size; i++)
            newArray[i] = hash->elementArray[i];
        free(hash->elementArray);
        hash->elementArray = newArray;
        hash->bufferSize = hash->bufferSize + firstBufferSize;
    }
    if (hash->size == 0) {
        hash->size = 1;
        hash->elementArray[0] = element;
        return;
    }
    int k = binarySearch(element->hashStr, hash);
    if (hash->elementArray[k]->hashStr < element->hashStr)
        k++;
    for (int i = hash->size - 1; i >= k; i--)
        hash->elementArray[i + 1] = hash->elementArray[i];
    hash->size++;
    hash->elementArray[k] = element;
}

tHashMapElement *get(const char *str, tHashMap *hsh) {
    long hashStr = hash(str);
    int pos = binarySearch(hashStr, hsh);
    if (hsh->elementArray[pos] != NULL && hsh->elementArray[pos]->hashStr == hashStr)
        if (strcmp(hsh->elementArray[pos]->str, str) == 0)
            return hsh->elementArray[pos];
        else {
            int curPos = pos;
            while (hsh->elementArray[--curPos]->hashStr == hashStr)
                if (strcmp(hsh->elementArray[curPos]->str, str) == 0)
                    return hsh->elementArray[curPos];

            curPos = pos;
            while (hsh->elementArray[++curPos]->hashStr == hashStr)
                if (strcmp(hsh->elementArray[curPos]->str, str) == 0)
                    return hsh->elementArray[curPos];
        }
    return NULL;
}

tHashMapElement *add(tHashMap *hsh, const char *str, int value) {
    tHashMapElement *element = (tHashMapElement *) malloc(sizeof(tHashMapElement));
    char *copy = (char *) malloc(sizeof(char) * strlen(str));
    memcpy(copy, str, sizeof(char) * strlen(str));
    element->str = copy;
    element->hashStr = hash(str);
    element->element = value;
    addElement(hsh, element);
    return element;
}

void printElement(tHashMapElement *element) {
    printf("Хеш: %lu \nСтрока: \"%s\"\nЗначение: \"%d\"\n\n", element->hashStr, element->str,
           element->element);

}

void printHash(tHashMap *hash) {
    for (int i = 0; i < hash->size; i++) {
        printf("Элемент %d:\n", i);
        printElement(hash->elementArray[i]);
    }
}

void removeHash(tHashMap *hashMap) {
    for (int i = 0; i < hashMap->size; i++) {
        free((void *) hashMap->elementArray[i]->str);
        free(hashMap->elementArray[i]);
    }
    free(hashMap->elementArray);
}


/**
 * Алгоритм хеширования djb2 был взят отсюда: http://www.cse.yorku.ca/~oz/hash.html
 *
 * @param str
 * @return НЕ обладает 100% уникальностью
 */
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}