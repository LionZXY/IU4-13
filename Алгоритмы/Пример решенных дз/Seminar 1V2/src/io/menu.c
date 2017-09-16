#include <stdlib.h>
#include <stdbool.h>
#include "stdio.h"
#include "reader.h"
#include "../utils/set.h"
#include "../utils/convert.h"

/**
 * @file menu.c
 * @author LionZXY
 * @project Seminar
 * @date 11.09.17
 * @email nikita@kulikof.ru
 **/

/**
 * Шаблон функции для открытии меню
 *
 * Без ООП тут тяжко, поэтому тут вывод и выполнение будет в одном слое
 * @return Код выполнения. EXIT_SUCCESS - все нормально. Все остальное - ошибка.
 */
typedef int (*menuFunction)();

int menuSetInsert();

int menuSetPrint();

int menuNumberInterpretation();

int menuSetSelect();

menuFunction menus[] = {
        &menuSetInsert,
        &menuSetPrint,
        &menuNumberInterpretation,
        &menuSetSelect
};

int menuMain() {
    printf("Привет! Выбери пункт меню:\n");
    printf("1. Ввести новый сет\n");
    printf("2. Вывести все сеты\n");
    printf("3. Перевести из десятичной системы в двоичную\n");
    printf("4. Вывести элементы 2-x множеств\n");
    printf("0. Выйти\n");

    int result = 0;
    if (getInt(&result) == EXIT_FAILURE) {
        printf("Не валидный ввод!\n");
        return menuMain();
    }
    if (!(result >= 0 && result <= 4)) {
        printf("Такого пункта меню нет!\n");
        return menuMain();
    }

    system("clear");

    return result;
}


int menuSetInsert() {
    printf("Введите последовательность:\n");
    ArrayList arrayList; // Тут указатель не освобождаем так как потом структура будет использоваться в другом месте. Там и освободим
    if (getIntArray(&arrayList) == EXIT_SUCCESS) {
        addArray(arrayList);
        printArray(&arrayList);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

int menuSetPrint() {
    printAllArrays();
    return EXIT_SUCCESS;
}

int menuNumberInterpretation() {
    printf("Введите число:\n");
    int number = 0;
    if (getInt(&number) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    bool *output = NULL;
    int numberSize = 0;
    if (toBinary(number, &output, &numberSize) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int i = numberSize - 1;
    while (output[i] == 0 && i != 0) i--;

    for (; i >= 0; i--) {
        printf("%d", output[i] ? 1 : 0);
    }
    printf("\n");

    if (output != NULL) {
        free(output);
    }
    return EXIT_SUCCESS;
}

// Private
int getIndexArray(int *out) {
    int index = 0;
    if (getInt(&index) != EXIT_FAILURE) {
        if (index >= 0 && index < getSet()->realSize) {
            *out = index;
            return EXIT_SUCCESS;
        } else if (index == -1) {
            return EXIT_FAILURE;
        } else {
            printf("Такого элемента нет (Границы %d-%d). Чтобы прекратить ввод, введите -1\n", 0, getSet()->realSize);
            return getIndexArray(out);
        }
    } else {
        printf("Чтобы прекратить ввод, введите -1\n");
        return getIndexArray(out);
    }
    *out = index;
    return EXIT_SUCCESS;
}

int menuSetSelect() {
    printf("Выберите два множества:\n");
    printAllArrays();
    printf("Индекс первого множества:\n");
    int first = 0;
    if (getIndexArray(&first) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    printf("Индекс второго множества\n");
    int second = 0;
    if (getIndexArray(&second) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    printf("Чего с ними сделать?\n");
    printf("1. Просто вывести\n");
    printf("2. Сложить множества\n");
    printf("3. Пересечения множеств\n");
    printf("4. Вычитать множества\n");
    printf("5. Я хлебушек\n");
    printf("0. Выход\n");
    int select = 0;
    if (getInt(&select) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    switch (select) {
        case 1: {
            printf("Эт мы могем, эт мы с радостью:\n");
            printArray(&getSet()->lists[first]);
            printArray(&getSet()->lists[second]);
            break;
        }
        case 2: {
            combiningAndPrintSets(&getSet()->lists[first], &getSet()->lists[second]);
            break;
        }
        case 3: {
            peresAndPrintSets(&getSet()->lists[first], &getSet()->lists[second]);
            break;
        }
        case 4: {
            diffAndPrintSets(&getSet()->lists[first], &getSet()->lists[second]);
            break;
        }
        case 5: {
            printf("Ты хлебушек\n");
            break;
        }
        case 0: {
            return EXIT_SUCCESS;
        }
        default: {
            printf("Такого пункта нет\n");
            break;
        }
    }
    return EXIT_SUCCESS;
}


int openSelectableMenu(int item) {
    if (item >= 0 && item < sizeof(menus) / sizeof(menuFunction)) {
        return menus[item]();
    } else {
        return EXIT_FAILURE;
    }
}