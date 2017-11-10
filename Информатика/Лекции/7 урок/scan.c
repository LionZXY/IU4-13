#include "stdio.h"

int main(int argc, char const *argv[])
{
	int i;
	// scanf("%d", &i);
	// printf("%d\n", i);
	int y, m, d;
	int scan_res;

	if ((scan_res = fscanf(stdin, "%d-%d-%d", &y, &m, &d)) == 3 && scan_res != EOF) {
		fprintf(stdout, "%d/%d/%d\n", y, d, m);
	} else {
		fprintf(stdout, "Incorrect format!\n");
	}
	return 0;
}