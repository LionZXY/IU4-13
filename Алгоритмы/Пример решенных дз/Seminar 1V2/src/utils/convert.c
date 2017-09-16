#include <stdbool.h>
#include <stdlib.h>
#include "convert.h"

/**
 * @file convert.c
 * @author LionZXY
 * @project Seminar
 * @date 16.09.17
 * @email nikita@kulikof.ru
 **/

/**
 * После вызова этого метода надо вызвать free(array) чтобы освободить массив, который находиться в Heap
 *
 * @param number
 * @return
 */
bool readBit(int number, int num);

void writeToBit(int *number, bool bit, int num);

int toBinary(int number, bool **bits, int *bitSize) {
    int bitSz = sizeof(int) * 8;
    bool *binary = malloc(sizeof(bool) * bitSz);
    for (int i = 0; i < bitSz; i++) {
        binary[i] = readBit(number, i);
    }
    *bits = binary;
    *bitSize = bitSz;
    return EXIT_SUCCESS;
}

int fromBinaryToDecimal(bool *array, int lenght) {
    int number = 0;
    for (int i = 0; i < lenght; i++) {
        writeToBit(&number, array[i], i);
    }
    return number;
}

void writeToBit(int *number, bool bit, int num) {
    bool tmpval = 1;
    int tmp = *number;
    tmpval = (tmpval << num);//устанавливаем нужный бит в единицу
    tmp = (tmp & (~tmpval));//сбрасываем в 0 нужный бит

    if (bit) { // если бит требуется установить в 1
        tmp = (tmp | (tmpval));//то устанавливаем нужный бит в 1
    }
    *number = tmp;
}

bool readBit(int number, int num) {
    return ((number >> num) & 1) > 0;
}
