//
// Created by lionzxy on 14.05.17.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"
#include "reader.h"

const float MAX_CONTAINS = 0.75F;
const int START_BUFFER_SIZE = 8;

unsigned int hash(const char *str, int tableSize);

void freeUser(User *user) {
    free(user->login);
    free(user->password);
}

void initHashMap(HashMap *hashMap) {
    hashMap->bufferSize = START_BUFFER_SIZE;
    hashMap->size = 0;
    hashMap->buffers = calloc((size_t) hashMap->bufferSize, sizeof(HashNode *));
}

HashNode *getHashNode(HashMap *hashMap, char *key) {
    int hsh = hash(key, hashMap->bufferSize);
    assert(hsh < hashMap->bufferSize);

    HashNode *hashNode = hashMap->buffers[hsh];
    while (hashNode != NULL) {
        if (!strcmp(hashNode->key, key))
            return hashNode;
        else hashNode = hashNode->next;
    }
    return hashNode;
}

User *getValue(HashMap *hashMap, char *key) {
    HashNode *hashNode = getHashNode(hashMap, key);
    return hashNode == NULL ? NULL : hashNode->user;
}


void freeNode(HashNode *node, void * shared) {
    free(node->key);
    freeUser(node->user);
}

bool removeFromHashMap(HashMap *hashMap, char *key) {
    int hsh = hash(key, hashMap->bufferSize);
    assert(hsh < hashMap->bufferSize);

    HashNode *hashNode = hashMap->buffers[hsh];
    if (hashNode == NULL)
        return false;
    if (!strcmp(hashNode->key, key)) {
        freeNode(hashNode, NULL);
        hashMap->buffers[hsh] = NULL;
        hashMap->size--;
        return true;
    }
    HashNode *tmp;
    while (hashNode->next != NULL) {
        if (!strcmp(hashNode->key, key)) {
            tmp = hashNode->next;
            hashNode->next = tmp->next;
            freeNode(tmp, NULL);
            hashMap->size--;
            return true;
        }
        hashNode = hashNode->next;
    }
    return false;
}

void rehash(HashMap *hashMap) {
    HashNode **oldMap = hashMap->buffers;
    int oldSize = hashMap->bufferSize;
    hashMap->size = 0;
    hashMap->bufferSize *= 1.5;
    hashMap->buffers = calloc((size_t) hashMap->bufferSize, sizeof(HashNode *));

    HashNode *tmp = NULL;
    HashNode *tmp2 = NULL;
    for (int i = 0; i < oldSize; i++) {
        if (oldMap[i] != NULL) {
            tmp = oldMap[i];
            while (tmp->next != NULL) {
                tmp2 = tmp->next;
                putInHashMap(hashMap, tmp->key, tmp->user);
                free(tmp->key);
                free(tmp);
                tmp = tmp2;
            }
            putInHashMap(hashMap, tmp->key, tmp->user);
            free(tmp->key);
            free(tmp);
        }
    }

    free(oldMap);
}

bool putInHashMap(HashMap *hashMap, char *key, User *user) {
    int hsh = hash(key, hashMap->bufferSize);

    assert(hsh < hashMap->bufferSize);

    HashNode *node = hashMap->buffers[hsh];
    if (node != NULL) {
        if (!strcmp(key, node->key))
            return false;
        while (node->next != NULL) {
            if (strcmp(key, node->key))
                return false;
            node = node->next;
        }
        node->next = malloc(sizeof(HashNode));
        node = node->next;
    } else {
        node = malloc(sizeof(HashNode));
        hashMap->buffers[hsh] = node;
    }

    node->user = user;
    node->key = copyString(key);
    node->next = NULL;
    hashMap->size++;

    if (((float) hashMap->size / hashMap->bufferSize) >= MAX_CONTAINS)
        rehash(hashMap);
    return true;
}

void freeHashMap(HashMap *hashMap) {
    hashMap->bufferSize = 0;
    hashMap->size = 0;
    iterratorByHashMap(hashMap, NULL, &freeNode);
    hashMap->buffers = NULL;
}

void iterratorByHashMap(HashMap *hashMap, void *shared, void (*next)(HashNode *node, void *sharedVar)) {
    HashNode *tmp = NULL;
    HashNode *tmp2 = NULL;
    for (int i = 0; i < hashMap->bufferSize; i++) {
        if (hashMap->buffers[i] != NULL) {
            tmp = hashMap->buffers[i];
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
unsigned int hash(const char *str, int tableSize) {
    unsigned int hash = 0;
    for (; *str != 0; ++str)
        hash = (hash * a + *str) % tableSize;
    return hash;
}