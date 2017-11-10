// printf("(%d,%d)\n", r1.pt1.x, r1.pt1.y);

// (3, 4)

// printf("(%d,%d) - (%d,%d)\n", r1.pt1.x, r1.pt1.y, r1.pt2.x, r1.pt2.y);

// (3, 4) - (7, 9)

struct key {
    char *word;
    int count; 
};

struct key k1 = {"auto", 0};

// struct key keytab[NKEYS] = {
//   "auto", 0,
//   "break", 0, 
//   "case", 0
// };

struct key keytab[] = {
  {"auto", 0},
  {"break", 0}, 
  {"case", 0}
};

#include "stdio.h"

int main(int argc, char const *argv[])
{
	printf(
		"%lu - %lu\n",
		sizeof keytab / sizeof(struct key),
		sizeof keytab / sizeof keytab[0]
	);

	printf("%lu\n", sizeof(struct key));

	printf("%lu - %lu - %lu\n", &keytab[0], &keytab[1], &keytab[2]);

	printf(
		"%lu\n", 
		// (&keytab[0] + &keytab[2]) / 2,
		&keytab[0] + (&keytab[2] - &keytab[0]) / 2
	);

	return 0;
}