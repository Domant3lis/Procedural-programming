// PS1 ~ Domantas Keturakis © 2021 ~ Task 1
// This program finds the bounds (maximum and minimum possible values of (almost) each type)

#include "time.h"
#include "stdio.h"

#define TYPE _

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#define OVERFLOW \
	TYPE a[2];\
	a[0] = 1, a[1] = 0;\
	while(a[0] > a[1])\
	{\
		a[1] = a[0];\
		++a[0];\
	}\

#define PRINT(a, b) printf("Bounds of " STRINGIFY(TYPE) " are [%d; %d]\n", a, b);

int main() {

	{
		#define TYPE char
		OVERFLOW
		PRINT(a[0], a[1])
	}

	{
		#define TYPE unsigned char
		OVERFLOW
		PRINT(a[0], a[1])
	}

	{
		#define TYPE short int
		OVERFLOW
		PRINT(a[0], a[1])
	}

	{
		#define TYPE unsigned short int
		OVERFLOW
		PRINT(a[0], a[1])
	}

	// time_t start, end;
	// time(&start);
	{
		#define TYPE int
		OVERFLOW
		PRINT(a[0], a[1])
	}
	// time(&end);
	// double time_taken = (double) (end - start);
	// printf("TIME TAKEN: %lf", time_taken);

	{
		#define TYPE unsigned int
		OVERFLOW
		// printf("%ld \n", a[0]);
		printf("Bounds of " STRINGIFY(TYPE) " are [%lu; %lu]\n", a[0], a[1]);
	}

	// // long ints may take a while to compute
	// // probably 4294967297 times longer than int
	// // (assuming calculation times scale linearly)
	// //
	// // it took me 2 seconds to calculate int on my machine
	// //
	// // so assuming that it takes 2 seconds to calculate an int
	// // long int will probably take ~99420 days (aprox. 276 years)
	// {
	// 	#define TYPE long int
	// 	OVERFLOW
	// 	PRINT(a[0], a[1])
	// }
	//
	// {
	// 	#define TYPE unsigned long int
	// 	OVERFLOW
	// 	PRINT(a[0], a[1])
	// }

	{
		#define TYPE unsigned long int
		TYPE a = -1;
		printf("Bounds of " STRINGIFY(TYPE) " are [%lu; %lu]\n", 0, a);
	}

	return 0;
}
