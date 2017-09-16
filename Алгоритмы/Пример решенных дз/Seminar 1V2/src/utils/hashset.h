#ifndef SEMINAR_HASHSET_H
#define SEMINAR_HASHSET_H

// Пользовательские данные
#define HASH_KEY const char *
typedef unsigned int (*hashFunctionDef)(HASH_KEY key, int tableSize);
unsigned int hashStr(const char *str, int tableSize);
hashFunctionDef hashFunction = &hashStr;

#include <stdbool.h>

struct HashNode {
    HASH_KEY key;
    struct HashNode *next;
} typedef HashNode;

struct HashSet {
    int size;
    int bufferSize;

    HashNode **buffers;
} typedef HashSet;

bool putInHashSet(HashSet *hashSet, HASH_KEY key);

bool removeFromHashSet(HashSet *hashSet, HASH_KEY key);

bool containsInHashSet(HashSet *hashSet, HASH_KEY key);

void initHashSet(HashSet *hashSet);

void freeHashSet(HashSet *hashSet);

void iterratorByHashSet(HashSet *hashSet, void *shared, void (*next)(HashNode *node, void *sharedVar));


#endif //SEMINAR_HashSet_H
