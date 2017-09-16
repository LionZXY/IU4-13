#include "set.h"
#include "stdio.h"
#include "hashset.h"

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

void printNode(HashNode *node, void *shared) {
    printf("%d ", node->key);
}

void combiningAndPrintSets(ArrayList *list, ArrayList *list2) {
    HashSet setOne;
    initHashSetFromArray(&setOne, list);
    for (int i = 0; i < list2->realSize; i++) {
        removeFromHashSet(&setOne, list2->array[i]); // Удаляем из первого листа все из второго
    }
    iterratorByHashSet(&setOne, NULL, &printNode);

    // Второй лист
    HashSet setTwo;
    initHashSetFromArray(&setTwo, list2);
    iterratorByHashSet(&setTwo, NULL, &printNode);

    printf("\n");

    freeHashSet(&setTwo);
    freeHashSet(&setOne);
}

void ifContainsPrint(HashNode *node, void *hashSet2) {
    HashSet *set = (HashSet *) hashSet2;
    if (containsInHashSet(set, node->key)) {
        printf("%d ", node->key);
    }
}

void peresAndPrintSets(ArrayList *list, ArrayList *list2) {
    HashSet setOne;
    HashSet setTwo;
    initHashSetFromArray(&setOne, list);
    initHashSetFromArray(&setTwo, list2);

    iterratorByHashSet(&setOne, &setTwo, &ifContainsPrint);

    freeHashSet(&setOne);
    freeHashSet(&setTwo);
}

void ifNotContainsPrint(HashNode *node, void *hashSet2) {
    HashSet *set = (HashSet *) hashSet2;
    if (!containsInHashSet(set, node->key)) {
        printf("%d ", node->key);
    }
}

void diffAndPrintSets(ArrayList *list, ArrayList *list2) {
    HashSet setOne;
    HashSet setTwo;
    initHashSetFromArray(&setOne, list);
    initHashSetFromArray(&setTwo, list2);

    iterratorByHashSet(&setOne, &setTwo, &ifNotContainsPrint);

    freeHashSet(&setOne);
    freeHashSet(&setTwo);
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
    free(setArrays.lists);
    setArrays.lists = NULL;
    setArrays.realSize = 0;
}

