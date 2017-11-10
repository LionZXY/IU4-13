#include <stdio.h>

int main() {
	int c, nl, prev;
	prev = '\n';
	nl = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			++nl;
		}
		prev = c;
	}
	if (prev != '\n') {
		++nl;
	}
	printf("%d\n", nl);
}