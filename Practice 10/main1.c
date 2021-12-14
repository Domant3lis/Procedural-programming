// Domantas Keturakis © 2021
// Task: reimplement strlen and then test it
#include "assert.h"
#include "string.h"
#include "test_strings.c"

unsigned long mystrlen(char *str);
int cmp (char *str);

int main() {

	// the tests
	// tests cmp()
	assert(
		(mystrlen("asd_\n !") == strlen("asd_\n !")) == cmp("asd_\n !")
	);
	// tests mystrlen()
	assert(cmp(""));
	assert(cmp("a"));
	assert(cmp("HELLO\n"));
	assert(mystrlen(NULL) == 0);
	assert(cmp("asd_\n "));
	assert(cmp(get_test_string(98765432)));
	// Uncomment if you like watching paint dry
	assert(cmp(get_test_string(-1)));

	char str[][101] = {
		{
			2, 14, 25, 27, 19, 31, 60, 46, 36,
			18, 20, 3, 27, 24, 28, 22, 58, 8, 24,
			6, 7, 94, 19, 63, 10, 29, 44, 8, 31,
			27, 14, 17, 14, 19, 127, 1, 26, 5,
			1, 4, 25, 12, 16, 16, 5, 7, 21, 35,
			25, 13, 29, 13, 9, 8, 23, 23, 17, 21,
			12, 25, 15, 5, 29, 12, 24, 19, 2, 16,
			20, 39, 6, 3, 81, 3, 4, 17, 89, 15,
			4, 20, 19, 2, 28, 12, 1, 36, 24, 10,
			7, 23, 18, 18, 1, 26, 16, 11, 8, 23,
			17, 1, 0,
		},
		{
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
			11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28,
			29, 39, 30, 31, 32, 33, 34, 35, 56, 0
		}
	};
	assert(cmp(str[0]));
	assert(cmp(str[1]));

	char del[] = {127, 127, 127, 0};
	assert(cmp(del));


	printf("%s\n", "All tests passed!");

	return 0;
}

// My reimplementation
// returns the lenght of a given string
unsigned long mystrlen(char *str){

	// checks if a given string is valid
	if (str == NULL)
		return 0;

	unsigned long i = 0;
	// increments the counter till it hits '\0' character
	while(str[i])
		++i;

	return i;
}

// checks if the reimplementation gives the same results
// as the actual implementaion
int cmp (char *str) { return (mystrlen(str) == strlen(str)); }
