#include <stdbool.h>
#include <glob.h>
#include "stdio.h"
void bubbleSorting(size_t arraySize, int *array) ;

int main(){
    int array[8] = {0,1,2,3,4,5,6,7};

    for(int i = 0; i< 8; i++)
        printf("%d ", array[i]);
    printf("\n");
    bubbleSorting(8,array);

    for(int i = 0; i< 8; i++)
        printf("%d ", array[i]);

    return 0;
}

void bubbleSorting(size_t arraySize, int *array) {
    bool isSorting = true; // Метка о том, что в последнем прогоне было всплывание
    int tmp = 0;

    while (isSorting) {
        isSorting = false;
        for (int i = 1; i < arraySize; i++)
            if (array[i] > array[i - 1]) {
                tmp = array[i - 1];
                array[i - 1] = array[i];
                array[i] = tmp;
                isSorting = true;
            }
    }
}