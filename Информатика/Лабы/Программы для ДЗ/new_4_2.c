#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int DEFAULT_BUFFER = 128;

// По идее, надо сделать Дек, но эт слишком сложно для дз по Информатике
int main() {
    int N = 0;
    scanf("%d", &N);

    int curPos = 0;
    char **strings = calloc((size_t) N, sizeof(char *));
    int tmpChar;

    int *size;
    int *bufferSize;
    char *workspace;
    while ((tmpChar = getchar()) != EOF) {
        if (strings[curPos] == NULL) {
            strings[curPos] = (char *) calloc(DEFAULT_BUFFER, sizeof(char));
            // Первые 8 байт в строке - служебные
            size = (void *) strings[curPos];
            bufferSize = (void *) size + sizeof(int);
            workspace = (void *) bufferSize + sizeof(int);
            *bufferSize = DEFAULT_BUFFER - sizeof(int) - sizeof(int);
        }

        if (tmpChar == '\n') {
            if (++curPos == N) {
                char *tmpString = strings[0];
                memmove(strings, strings + 1, sizeof(char *) * (N - 1));
                curPos = N - 1;
                strings[curPos] = tmpString;
                size = (void *) strings[curPos];
                bufferSize = (void *) size + sizeof(int);
                workspace = (void *) bufferSize + sizeof(int);

                *size = 0;
            }
        } else {
            workspace[(*size)++] = (char) tmpChar;
            if (*size == *bufferSize) {
                *bufferSize *= 1.5;
                strings[curPos] = (char *) realloc(strings[curPos],
                                                   sizeof(char) * (*bufferSize) + sizeof(int) + sizeof(int));
            }
        }
    }

    if (N == curPos)
        curPos = N - 1;
    for (int i = 0; i <= curPos; i++) {
        for (int j = 0; j <= *((int *) strings[i]); j++)
            putchar(strings[i][j + sizeof(int) * sizeof(int)]);
        putchar('\n');
    }
    return 0;
}