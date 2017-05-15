#include <stdio.h>

int main() {
	long int nc;
	nc = 0;
	while (getchar() != EOF)
		++nc;
	printf("%ld\n", nc);
}