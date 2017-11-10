#ifndef IU4_DATABASE_USERS_H
#define IU4_DATABASE_USERS_H

#include <stdbool.h>
#include "../utils/hashmap.h"

extern const char *USER_FILE;
extern const char SEPARATOR_CHAR_USER;

struct UserTable {
    HashMap *hashMap;
} typedef UserTable;

User *findUser(UserTable *table, char *login);

UserTable *loadUserTable(const char *filename);

void saveUserTable(UserTable *table, const char *filename);

void freeUserTable(UserTable *userTable);

#endif //IU4_DATABASE_USERS_H
