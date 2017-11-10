#include "stdio.h"

int main(int argc, char const *argv[])
{
	char c;
	FILE *f1, *f2;
	f1 = fopen("f1.c", "r");
	f2 = fopen("f2.c", "w");
	while ((c = getc(f1)) != EOF) {
		putchar(c);
		putc(c, f2);
	}
	fclose(f1); // comment
	fclose(f2);
	return 0;
}
