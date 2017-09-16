#include "set.h"
#include "stdio.h"

/**
 * @file set.c
 * @author LionZXY
 * @project Seminar
 * @date 08.09.17
 * @email nikita@kulikof.ru
 **/

static SetArrays setArrays = {0, NULL};

void addArray(ArrayList list) {
    int newSize = setArrays.realSize + 1;
    setArrays.lists = realloc(setArrays.lists, sizeof(ArrayList) * newSize);
    setArrays.lists[setArrays.realSize] = list;
    setArrays.realSize = newSize;
}

void printArray(ArrayList *list) {
    printf("%d элементов: ", list->realSize);
    for (int i = 0; i < list->realSize; i++) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

void printAllArrays() {
    printf("На данный момент хранится %d множеств(о)\n", setArrays.realSize);
    for (int i = 0; i < setArrays.realSize; i++) {
        printf("%d: ", i);
        for (int j = 0; j < setArrays.lists[i].realSize; j++) {
            printf("%d ", setArrays.lists[i].array[j]);
        }
        printf("\n");
    }
}

SetArrays *getSet() {
    return &setArrays;
}

void freeSets() {
    for (int i = 0; i < setArrays.realSize; i++) {
        free(&setArrays.lists[i]);
    }
    free(setArrays.lists);
    setArrays.lists = NULL;
    setArrays.realSize = 0;
}

