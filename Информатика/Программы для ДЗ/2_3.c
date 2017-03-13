#include <stdio.h>

int main() {
    int counterForSpace = 0, counterForTabs = 0, counterForLine = 0;
    char tmpChar = NULL;
    while (tmpChar != '*') {
        tmpChar = getchar();
        switch (tmpChar) {
            case '\n':
                counterForLine++;
                break;
            case '\t':
                counterForTabs++;
                break;
            case ' ':
                counterForSpace++;
                break;
        }
    }
    printf("Количество пробелов: %d\n", counterForSpace);
    printf("Количество табов: %d\n", counterForTabs);
    printf("Количество линий: %d\n", counterForLine);
    printf("Количество 'особых' символов: %d\n", counterForLine + counterForSpace + counterForTabs);
}
