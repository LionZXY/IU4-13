//
// Created by lionzxy on 14.05.17.
//

#ifndef IU4_DATABASE_HASHMAP_H
#define IU4_DATABASE_HASHMAP_H

#include <stdbool.h>

struct User {
    char *login;
    char *password;
    bool permissionBook;
    bool permissionStudent;
} typedef User;


struct HashNode {
    char *key;
    User *user;
    struct HashNode *next;
} typedef HashNode;

struct HashMap {
    int size;
    int bufferSize;

    HashNode **buffers;
} typedef HashMap;

bool putInHashMap(HashMap *hashMap, char *key, User *value);

bool removeFromHashMap(HashMap *hashMap, char *key);

User *getValue(HashMap *hashMap, char *key);

void initHashMap(HashMap *hashMap);

void freeHashMap(HashMap *hashMap);

void iterratorByHashMap(HashMap *hashMap, void *shared, void (*next)(HashNode *node, void *sharedVar));

#endif //IU4_DATABASE_HASHMAP_H
