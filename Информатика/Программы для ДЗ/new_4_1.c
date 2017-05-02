#include <malloc.h>
#include <string.h>

int strend(char *string, char *templare);

int main() {
    char string[256] = {1};
    char *templare = "nik";
    while (string[0] != 0) {
        scanf("%s", string);
        if (strend(string, templare))
            printf("%s", string);
    }
    return 0;
}

int strend(char *string, char *templare) {
    size_t lenTemplare = strlen(templare);
    size_t lenString = strlen(string);

    if (lenString < lenTemplare)
        return 0;

    for (size_t i = lenString, j = lenTemplare; i > 0 & j > 0; i--, j--)
        if (string[i] != templare[j])
            return 0;

    return 1;
}