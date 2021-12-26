// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// swaps values inside `a` and `b`
void swap(long *a, long *b)
{
	long temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	long a = -7;
	long b = 99999999;
	printf("A: %ld, B: %ld\n", a, b);
	swap(&a, &b);
	printf("A: %ld, B: %ld\n", a, b);

	long c = -1;
	long d = 11111111;
	printf("C: %ld, D: %ld\n", c, d);
	swap(&c, &d);
	printf("C: %ld, D: %ld\n", c, d);

	return 0;
}
