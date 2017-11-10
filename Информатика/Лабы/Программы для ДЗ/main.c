#include <stdio.h>

int main(void) {
    int chislo;
    int lower, upper;
    lower = 0;
    upper = 100;
    chislo = lower;
    while (chislo <= upper){
        printf(chislo,"\n");
        chislo = chislo + 20;
    }

    return 0;
}