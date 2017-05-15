#include "stdio.h"

int main()
{
	int *pi;
	int i = 0;
	pi = &i;
	char *pc;
	char c = 'a';
	pc = &c;
	printf("%c - %u\t\t%d %u\n", *pc, pc, *pi, pi);
	printf("%u\t\t%u\n", &pc, &pi);
	while (1) {
		printf("%c - %d\n", *pc, *pc);
		pc++;
	}
	int a[10], *p;
	p = NULL;
	a[2] = *p; // Segmentation fault
	p = &a[0];
	for (int i = 0; i< 10; i++) {
		printf("%u - %u\n", p+i, &a[i]);
	}
	return 0;
}