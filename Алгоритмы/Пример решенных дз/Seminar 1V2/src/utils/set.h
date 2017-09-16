/**
 * @file set.h
 * @author LionZXY
 * @project Seminar
 * @date 08.09.17
 * @email nikita@kulikof.ru
 **/
#ifndef SEMINAR_SET_H
#define SEMINAR_SET_H

#include <lzma.h>
#include <stdlib.h>
#include "../io/reader.h"

struct SetArrays {
    int realSize;
    ArrayList *lists;
} typedef SetArrays;


/**
 * В контексте C довольно сложно ложится концепция ООП, поэтому не будет никакого контекста или синглтона
 **/
void addArray(ArrayList list);
void printArray(ArrayList *list);
void printAllArrays();
SetArrays* getSet();
void freeSets();

#endif //SEMINAR_SET_H
