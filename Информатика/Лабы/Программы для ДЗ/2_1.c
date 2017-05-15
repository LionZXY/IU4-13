#include <stdio.h>

int main() {
    char tmpChar = NULL;
    while (tmpChar != '\n') {
        tmpChar = getchar();
        if (tmpChar != ' ')
            putchar(tmpChar);
        else
            putchar('\n');
    }
}