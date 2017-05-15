#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

void merge(int *arr, int firstStart, int firstEnd, int secondStart, int secondEnd) {
    int start = firstStart;
    int end = secondEnd;
    firstStart -= start;
    firstEnd -= start;
    secondStart -= start;
    secondEnd -= start;
    int size = secondEnd - firstStart + 1;

    int *buffer = malloc(size * sizeof(int));
    memcpy(buffer, arr + start, size * sizeof(int));

    for (int i = start; i <= end; i++) {
        if (secondEnd >= secondStart)
            if (firstEnd >= firstStart) {
                arr[i] = (buffer[firstStart] > buffer[secondStart] ? buffer[secondStart++] : buffer[firstStart++]);
            } else arr[i] = buffer[secondStart++];
        else arr[i] = buffer[firstStart++];
    }

    assert(secondStart > secondEnd);
    assert(firstStart > firstEnd);

    free(buffer);
}


void mergeSort(int *arr, int start, int end) {
    if (end - start < 2) {
        if (arr[start] > arr[end]) {
            int tmp = arr[start];
            arr[start] = arr[end];
            arr[end] = tmp;
        }
        return;
    }

    int size = end - start + 1;

    int firstStart = start;
    int firstEnd = start + size / 2;
    int secondStart = firstEnd + 1;
    int secondEnd = end;

    assert(firstEnd >= firstStart);
    assert(secondEnd >= secondStart);
    assert(size > 0);

    mergeSort(arr, firstStart, firstEnd);
    mergeSort(arr, secondStart, secondEnd);

    merge(arr, firstStart, firstEnd, secondStart, secondEnd);
}

int main() {
    int n = 0;
    scanf("%d", &n);

    int *array = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%u", &array[i]);

    mergeSort(array, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%u ", array[i]);

    free(array);
    return 0;
}