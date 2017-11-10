#ifndef VYZ_HASHMAP_H
#define VYZ_HASHMAP_H

#define firstBufferSize 16

typedef struct tHashMapElement {
    long hashStr; // Жертвуем ОЗУ в пользу производительности
    const char *str; // Для исключения коллизии
    int element;
} tHashMapElement;

typedef struct tHashMap {
    int size;
    int bufferSize;
    struct tHashMapElement **elementArray;
} tHashMap;


void initHashMap(tHashMap *hashMp);

tHashMapElement *get(const char *str, tHashMap *hsh);

void printElement(tHashMapElement *element);

void addElement(tHashMap *hash, tHashMapElement *element);

void printHash(tHashMap *hash);

unsigned long hash(const char *str);

tHashMapElement *add(tHashMap *hsh, const char *str, int value);

void removeHash(tHashMap *hashMap);

#endif