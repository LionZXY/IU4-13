//
// Created by lionzxy on 14.05.17.
//

#include <stdlib.h>
#include <stdio.h>
#include "users.h"
#include "../utils/reader.h"

const char *USER_FILE = "users.csv";
const char SEPARATOR_CHAR_USER = ';';

User *fromStr(char *str) {
    User *user = calloc(1, sizeof(User));
    int pos = 0;
    user->login = nextString(str, &pos, SEPARATOR_CHAR_USER);
    user->password = nextString(str, &pos, SEPARATOR_CHAR_USER);
    user->permissionBook = nextInt(str, &pos, SEPARATOR_CHAR_USER) == 1;
    user->permissionStudent = nextInt(str, &pos, SEPARATOR_CHAR_USER) == 1;
    return user;
}

UserTable *loadUserTable(const char *filename) {
    UserTable *userTable = calloc(1, sizeof(UserTable));
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return NULL;
    }
    userTable->hashMap = calloc(1, sizeof(HashMap));
    initHashMap(userTable->hashMap);
    char buffer[256]; // Пусть максимальная длинна строки будет 256
    User *tmp;
    while (fgets(buffer, sizeof(buffer), file)) {
        tmp = fromStr(buffer);
        putInHashMap(userTable->hashMap, tmp->login, tmp);
    }
    printf("Загрузка БД в память завершена! Всего элементов: %d.\n", userTable->hashMap->size);
    fclose(file);
    return userTable;
}

void saveToFile(HashNode *hashNode, void *file) {
    fprintf((FILE *) file, "%s%c%s%c%d%c%d", hashNode->user->login, SEPARATOR_CHAR_USER,
            hashNode->user->password, SEPARATOR_CHAR_USER,
            hashNode->user->permissionBook ? 1 : 0, SEPARATOR_CHAR_USER,
            hashNode->user->permissionStudent ? 1 : 0);
}

void saveUserTable(UserTable *table, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Ошибка при открытии файла");
        return;
    }
    printf("Сохранение БД в файл ... ");
    iterratorByHashMap(table->hashMap, file, &saveToFile);
    printf("OK\n");
    fclose(file);
}

User *findUser(UserTable *table, char *login) {
    return getValue(table->hashMap, login);
}

void freeUserTable(UserTable *userTable) {
    freeHashMap(userTable->hashMap);
    free(userTable);
}