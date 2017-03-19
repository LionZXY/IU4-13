#include <glob.h>
#include <math.h>
#include "stdio.h"

long long getLongFromHEX(size_t size, char *arr);

int main() {
    char *string = "B3A73CF8186";
    long long res = getLongFromHEX(11, string);

    printf("%lli", res);
    return 0;
}

int charToInt(char numeric) {
    if (numeric >= '0' && numeric <= '9')
        return numeric - '0';
    else if (numeric >= 'A' && numeric <= 'F')
        return numeric - 'A' + 10;
    else if (numeric >= 'a' && numeric <= 'f')
        return numeric - 'a' + 10;
    else return 0;
}

long long getLongFromHEX(size_t size, char *arr) {
    long long returnValue = 0;
    for (int i = (int) (size - 1), j = 0; i > -1; i--, j++) {
        returnValue += charToInt(arr[i]) *  pow(16.0, (double) j);
    }
    return returnValue;
}


