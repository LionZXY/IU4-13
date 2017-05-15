#include <stdbool.h>
#include <glob.h>
#include "stdio.h"

void shellSorting(int arraySize, int *array) ;

int main(){
    int array[8] = {0,1,2,3,4,5,6,7};

    for(int i = 0; i< 8; i++)
        printf("%d ", array[i]);
    printf("\n");
    shellSorting(8,array);

    for(int i = 0; i< 8; i++)
        printf("%d ", array[i]);

    return 0;
}

void shellSorting(int arraySize, int *array) {
    int deltaArray[9] = {0, 1, 4, 10, 23, 57, 132, 301, 701};
    int deltaPos = 8;
    for (deltaPos = 8; deltaPos > 0 && deltaArray[deltaPos] > arraySize - 1; deltaPos--);

    int currentDelta = 0;
    for (currentDelta = deltaArray[deltaPos--]; currentDelta > 0; currentDelta = deltaArray[deltaPos--]) {
        bool isSorting = true;
        int tmp = 0;

        while (isSorting) {
            isSorting = false;
            for (int i = currentDelta; i < arraySize; i++)
                if (array[i] > array[i - currentDelta]) {
                    tmp = array[i - currentDelta];
                    array[i - currentDelta] = array[i];
                    array[i] = tmp;
                    isSorting = true;
                }
        }
    }
}
