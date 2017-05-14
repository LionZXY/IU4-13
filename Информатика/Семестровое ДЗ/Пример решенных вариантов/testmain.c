#include "utils/hashmap.h"
#include "stdio.h"

//
// Created by lionzxy on 14.05.17.
//
int main() {
    HashMap hashMap;
    initHashMap(&hashMap);
    User user;
    user.login = "LionZXY";
    user.password = "123";
    user.permissionBook = true;
    putInHashMap(&hashMap, user.login, &user);
    printf("%s", getValue(&hashMap, "LionZXY")->password);
    printf("%d", hashMap.size);
    freeHashMap(&hashMap);
    return 0;
};
