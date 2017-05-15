#include "stdio.h"
#include <glob.h>
#include <stdlib.h>

char * getFullString(size_t stringSize, size_t string2Size, char *string1, char *string2) ;

int main() {
    char *string1 = "a-zA-Z0-9";
    char *string2 = NULL;

    size_t stringSize = 9;
    size_t string2Size = 0;
    string2 = getFullString(stringSize, string2Size, string1, string2);

    printf("%s", string2);
    return 0;
}

int calculateNewSize(size_t stringSize, char *string) {
    int newSize = 0;
    for (int i = 0; i < stringSize; i++) {
        newSize++;
        if (string[i] == '-')
            newSize += string[i + 1] - string[i - 1] - 2;
    }
    return newSize + 1;
}

char* getFullString(size_t stringSize, size_t string2Size, char *string1, char *string2) {
    string2Size = (size_t) calculateNewSize(stringSize, string1);
    string2 = malloc(sizeof(char) * string2Size);
    int curPos = 0;

    for (int i = 0; i < stringSize; i++) {
        if (string1[i] != '-')
            string2[curPos++] = string1[i];
        else
            for (char ch = (char) (string1[i - 1] + 1); ch < string1[i + 1]; ch++)
                string2[curPos++] = ch;
    }
    string2[curPos] = '\0';
    return string2;
}

