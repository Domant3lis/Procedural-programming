// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdint.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(){

	int a = 1;
	int b = 2;
	printf("A: %d, B: %d\n", a, b);
	swap(&a, &b);
	printf("A: %d, B: %d\n", a, b);

	return 0;
}
