#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    const int bufferSize = 256;
    if (argc < 4) {
        printf("Необходимо указать название трех файлов");
        return 0;
    }
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    FILE *file3 = fopen(argv[3], "w");
    char buffer[bufferSize];
    if (file1 == NULL || file2 == NULL || file3 == NULL)
        printf("Проблема при открытии одного из файлов");
    else {
        bool isAdded = true;
        while (isAdded) {
            isAdded = false;

            if (fgets(buffer, bufferSize, file1) != NULL) {
                fputs(buffer, file3);
                isAdded = true;
            }

            if (fgets(buffer, bufferSize, file2) != NULL) {
                fputs(buffer, file3);
                isAdded = true;
            }

        }
    }

    if (file1 != NULL)
        fclose(file1);
    if (file2 != NULL)
        fclose(file2);
    if (file3 != NULL)
        fclose(file3);

    return 0;
}