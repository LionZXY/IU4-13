#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @var number max is 7
 */
int getByte(long long var, int number) {
    return (int) ((var >> (number * 8)) & 255);
}

void radixSort(unsigned int *array, int n) {
    int *keyArray = (int *) malloc(256 * sizeof(int));
    unsigned int *tmpArray = (unsigned int *) malloc(n * sizeof(unsigned int));
    int tmp;
    int lastVar;
    for (int byteNumber = 0; byteNumber < 4; byteNumber++) {
        memset(keyArray, 0, 256 * sizeof(int));

        for (int i = 0; i < n; i++)
            keyArray[getByte(array[i], byteNumber)]++;

        lastVar = 0;
        for (int i = 0; i < 256; i++) {
            tmp = keyArray[i];
            keyArray[i] = lastVar;
            lastVar += tmp;
        }

        for (int i = 0; i < n; i++) {
            tmp = getByte(array[i], byteNumber);
            tmpArray[keyArray[tmp]] = array[i];
            keyArray[tmp]++;
        }

        memmove(array, tmpArray, n * sizeof(unsigned int));
    }
    free(tmpArray);
    free(keyArray);
}

int main() {
    int n = 0;
    scanf("%d", &n);

    unsigned int *array = (unsigned int *) malloc(sizeof(unsigned int) * n);
    for (int i = 0; i < n; i++)
       scanf("%u", &array[i]);

    radixSort(array, n);

    for (int i = 0; i < n; i++)
        printf("%u ",array[i]);

    free(array);
    return 0;
}