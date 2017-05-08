//
// Created by lionzxy on 08.05.17.
//

#ifndef IU4_DATABASE_MENUS_H
#define IU4_DATABASE_MENUS_H

#include "../databases/books.h"
#include "../databases/students.h"

int openRootMenu();
int openStudentMenu();
int openBookMenu();

BookTable *doItBook(int input, BookTable *table);
StudentTable *doItStudent(int input, StudentTable *table);

#endif //IU4_DATABASE_MENUS_H
