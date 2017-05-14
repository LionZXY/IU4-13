//
// Created by lionzxy on 08.05.17.
//

#ifndef IU4_DATABASE_MENUS_H
#define IU4_DATABASE_MENUS_H

#include "../databases/books.h"
#include "../databases/students.h"
#include "hashmap.h"
#include "../databases/users.h"

int openRootMenu(User * user);

int openStudentMenu(User * user);

int openBookMenu(User * user);

BookTable *doItBook(int input, BookTable *table);

StudentTable *doItStudent(int input, StudentTable *table);

User *auth(UserTable *userTable);

#endif //IU4_DATABASE_MENUS_H
