#include <stdlib.h>
#include "stdio.h"
#include "io/menu.h"
#include "utils/set.h"

int main() {
    int select = 0;
    while ((select = menuMain()) != 0) {
        openSelectableMenu(select - 1);
    }
    printf("До новых встреч!)");
    freeSets();
    return EXIT_SUCCESS;
}