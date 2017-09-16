#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashset.h"
#include "../io/reader.h"

const float MAX_CONTAINS = 0.75F;
const int START_BUFFER_SIZE = 8;

unsigned int hashInt(int num, int tableSize);

hashFunctionDef hashFunction = &hashInt;

void initHashSetFromArray(HashSet *hashSet, ArrayList *list) {
    hashSet->bufferSize = (int) (list->realSize / MAX_CONTAINS);
    hashSet->size = 0;
    hashSet->buffers = calloc((size_t) hashSet->bufferSize, sizeof(HashNode *));
    for (int i = 0; i < list->realSize; i++) {
        putInHashSet(hashSet, list->array[i]);
    }
}

void initHashSet(HashSet *hashSet) {
    hashSet->bufferSize = START_BUFFER_SIZE;
    hashSet->size = 0;
    hashSet->buffers = calloc((size_t) hashSet->bufferSize, sizeof(HashNode *));
}

HashNode *getHashNode(HashSet *hashSet, HASH_KEY key) {
    int hsh = hashFunction(key, hashSet->bufferSize);
    assert(hsh < hashSet->bufferSize);

    HashNode *hashNode = hashSet->buffers[hsh];
    while (hashNode != NULL) {
        if (hashNode->key == key)
            return hashNode;
        else hashNode = hashNode->next;
    }
    return hashNode;
}

bool containsInHashSet(HashSet *hashSet, HASH_KEY key) {
    HashNode *hashNode = getHashNode(hashSet, key);
    return hashNode != NULL;
}


void freeNode(HashNode *node, void *shared) {
}

bool removeFromHashSet(HashSet *hashSet, HASH_KEY key) {
    int hsh = hashFunction(key, hashSet->bufferSize);
    assert(hsh < hashSet->bufferSize);

    HashNode *hashNode = hashSet->buffers[hsh];
    if (hashNode == NULL)
        return false;
    if (hashNode->key == key) {
        freeNode(hashNode, NULL);
        hashSet->buffers[hsh] = NULL;
        hashSet->size--;
        return true;
    }
    HashNode *tmp;
    while (hashNode->next != NULL) {
        if (hashNode->key == key) {
            tmp = hashNode->next;
            hashNode->next = tmp->next;
            freeNode(tmp, NULL);
            hashSet->size--;
            return true;
        }
        hashNode = hashNode->next;
    }
    return false;
}

void rehash(HashSet *hashSet) {
    HashNode **oldMap = hashSet->buffers;
    int oldSize = hashSet->bufferSize;
    hashSet->size = 0;
    hashSet->bufferSize *= 1.5;
    hashSet->buffers = calloc((size_t) hashSet->bufferSize, sizeof(HashNode *));

    HashNode *tmp = NULL;
    HashNode *tmp2 = NULL;
    for (int i = 0; i < oldSize; i++) {
        if (oldMap[i] != NULL) {
            tmp = oldMap[i];
            while (tmp->next != NULL) {
                tmp2 = tmp->next;
                putInHashSet(hashSet, tmp->key);
                free(tmp);
                tmp = tmp2;
            }
            putInHashSet(hashSet, tmp->key);
            free(tmp);
        }
    }

    free(oldMap);
}

bool putInHashSet(HashSet *hashSet, HASH_KEY key) {
    int hsh = hashFunction(key, hashSet->bufferSize);

    assert(hsh < hashSet->bufferSize);

    HashNode *node = hashSet->buffers[hsh];
    if (node != NULL) {
        if (key == node->key)
            return false;
        while (node->next != NULL) {
            if (key == node->key)
                return false;
            node = node->next;
        }
        node->next = malloc(sizeof(HashNode));
        node = node->next;
    } else {
        node = malloc(sizeof(HashNode));
        hashSet->buffers[hsh] = node;
    }
    node->key = key;
    node->next = NULL;
    hashSet->size++;

    if (((float) hashSet->size / hashSet->bufferSize) >= MAX_CONTAINS)
        rehash(hashSet);
    return true;
}

void freeHashSet(HashSet *hashSet) {
    hashSet->bufferSize = 0;
    hashSet->size = 0;
    iterratorByHashSet(hashSet, NULL, &freeNode);
    hashSet->buffers = NULL;
}

void iterratorByHashSet(HashSet *hashSet, void *shared, void (*next)(HashNode *node, void *sharedVar)) {
    HashNode *tmp = NULL;
    HashNode *tmp2 = NULL;
    for (int i = 0; i < hashSet->bufferSize; i++) {
        if (hashSet->buffers[i] != NULL) {
            tmp = hashSet->buffers[i];
            while (tmp->next != NULL) {
                tmp2 = tmp->next;
                next(tmp, shared);
                tmp = tmp2;
            }
            next(tmp, shared);
        }
    }
}

const int a = 59;

// Хеш-функция строки.
unsigned int hashInt(int num, int tableSize) {
    return (unsigned int) ((num * a) % tableSize);
}