#include <stdio.h>

int main() {
	char c;
	c = getchar();
	while (c != EOF) {
		putchar(c);
		c = getchar();
	}

	printf("%d\n", EOF);
}


int main() {
	int c;
	while ((c = getchar()) != EOF) {
		putchar(c);
	}
}