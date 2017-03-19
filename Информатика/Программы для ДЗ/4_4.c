#include <glob.h>
#include <stdlib.h>
#include "stdio.h"

int binarySearch(int n, size_t size, int *sortedArray);

int main() {
    int array[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int number = 0;
    while (number != -1) {
        scanf("%d", &number);

        int result = binarySearch(number, 8, array);

        if (array[result] == number)
            printf("OK!\n");
        else printf("NO!\n");
    }
    return 0;
}

int binarySearch(int n, size_t size, int *sortedArray) {
    int start = 0, end = 0, curPos = 1;

    // Бежим степенью двойки до ближайшего значения, больше искомого
    while (curPos < size && sortedArray[curPos] < n)
        curPos *= 2;;
    if (curPos > size)
        curPos = (int) size - 1;

    if (curPos == 1)
        start = 0;
    else start = curPos / 2;
    end = curPos;

    // Стандартный бинарный поиск
    do {
        curPos = (end - start) / 2;
        if (n > sortedArray[start + curPos])
            start = start + curPos;
        else end = start + curPos;
    } while (end - start > 1);

    if (end == size)
        return end - 1;
    else if (abs(sortedArray[start] - n) > abs(sortedArray[end] - n))
        return end;
    else return start;
}