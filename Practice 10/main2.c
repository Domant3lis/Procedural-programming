// PS1 ~ Domantas Keturakis © 2022
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <features.h>

// Compares two strings lexicographically
int mystrcmp(char *left, char *right){
	
	do
	{
		if (*left  != *right)
		{
			return *left - *right;
		}

		++left;
		++right;
	}
	while(*left || *right);
	
	return 0;
}

// checks if the mystrlen gives the same results
// as the GLIBC implementation i.e. lexicographical comparison
int cmp_lex(char *left, char *right)
{
	int cmp0 = mystrcmp(left, right);
	int cmp1 = strcmp(left, right);
	return (cmp1 == cmp0);
}

// checks if mystrlen() conforms to the standard
int cmp_std(char *left, char *right)
{
	// printf("STR_LEFT: '%s'", left);
	// printf("STR_RIGHT: '%s'", right);

	strcmp(left, right);
	int cmp1 = strcmp(left, right);
	int cmp0 = mystrcmp(left, right);

	// printf("LEFT: '%s'   RIGHT: '%s'\n", left, right);

	if (cmp1 > 0 && cmp0 > 0)
		return 1;
	else if (cmp1 < 0 && cmp0 < 0)
		return 1;
	else if (0 == cmp1 && 0 == cmp0)
		return 1;
	else
		return 0;
}

int main()
{
	char *str10 = "asd_\n !";
	char *str11 = "a";

	// checks if lexicographical comparison is correct
	// only if GLIBC is detected
	// since only GLIBC (as far as I know) implements lexicographical string comparison
	// since the standard only specifies to return values either
	// below 0, 0 or above 0
	#if defined(__GLIBC__) && __GLIBC__
		
		puts("GLIBC is used");

		// Tests cmp()
		assert((mystrcmp(str10, str11) == strcmp(str10, str11)) == cmp_lex(str10, str11));
		// this might not work:
		// assert((mystrcmp("asd_\n !", "a") == strcmp("asd_\n !", "a")) == cmp_lex("asd_\n !", "a"));
		// since some compilers (IIRC, clang and gcc)
		// optimize strlen and change its output
		// then constants are passed as arguments
		// 
		// -fno-builtin flag must be used to disable those optimizations
		// source: https://stackoverflow.com/questions/33091350/strcmp-return-different-values-for-same-string-comparisons

		assert(cmp_lex("abcd", "abcd"));
		assert(cmp_lex("aaa", "aaaa"));
		assert(cmp_lex("+____@!3`435678`12", "a"));
		assert(cmp_lex("\0", "a"));
		assert(cmp_lex("a", "\0"));

	#endif

	// Tests cmp()
	assert((mystrcmp(str10, str11) == strcmp(str10, str11)) == cmp_std(str10, str11));

	// Tests if function changes input
	char *str20 = "aaa";
	char *str20_dup = strdup(str20);
	mystrcmp(str20, "a");
	assert(!strcmp(str20, str20_dup));

	// Tests mystrcmp()
	assert(mystrcmp("abc", "abc") == 0);
	assert(cmp_std("abc", "abc"));
	assert(cmp_std("aa", "aaa"));
	assert(cmp_std("+____@!3`435678`12", "sssss"));
	assert(cmp_std("+____@!3`435678`12", "123\0"));
	assert(cmp_std("+____@!3`435678`12", "\0"));
	assert(cmp_std("\0", "+____ @!3`435678`12"));

	puts("All tests passed!");

	return 0;
}
