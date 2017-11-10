#include <malloc.h>
#include <stdbool.h>


void removeSymbolsFromString(size_t s1Size, size_t s2Size, size_t outputSize, char *s1, char *s2, char *outputArray) ;

int main() {
    char *s1 = "Privet!";
    char *s2 = "asdfvg";
    size_t s1Size = 7;
    size_t s2Size = 5;

    char output[s1Size];
    size_t outputSize = 0;
    removeSymbolsFromString(s1Size, s2Size, outputSize, s1, s2, output);
    printf("%s", output);
}

void removeSymbolsFromString(size_t s1Size, size_t s2Size, size_t outputSize, char *s1, char *s2, char *outputArray) {
    outputSize = 0;
    bool contains = false;

    for (int i = 0; i < s1Size; i++) {
        for (int j = 0; j < s2Size && !contains; j++)
            if (s2[j] == s1[i])
                contains = true;
        if (!contains)
            outputArray[outputSize++] = s1[i];
        contains = false;
    }
    outputArray[outputSize] = '\0';
}
