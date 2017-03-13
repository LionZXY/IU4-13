#include <stdio.h>

int main() {
    char tmpChar = NULL;
    while (tmpChar != '*') {
        tmpChar = getchar();
        switch (tmpChar){
            case '\n':
                putchar('/');
                putchar('n');
                break;
            case '\t':
                putchar('/');
                putchar('t');
                break;
            default:
                putchar(tmpChar);
        }
    }
}
