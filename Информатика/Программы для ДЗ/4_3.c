#include "stdio.h"

void qsort(int *array, int start, int end);

int main() {
    int array[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < 8; i++)
        printf("%d ", array[i]);
    printf("\n");
    qsort(array, 0, 7);

    for (int i = 0; i < 8; i++)
        printf("%d ", array[i]);

    return 0;
}

void qsort(int *array, int start, int end) {
    int i = start;
    int j = end;
    int middle = array[(start + end) / 2];
    int tmp;

    do {
        while (array[i] > middle) i++;
        while (array[j] < middle) j--;

        if (i <= j) {
            if (array[i] < array[j]) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
        qsort(array, i, end);
    if (start < j)
        qsort(array, start, j);
}