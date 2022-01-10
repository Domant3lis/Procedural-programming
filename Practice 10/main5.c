// PS1 ~ Domantas Keturakis © 2022
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void *mymemchr(const void *ptr, int c, size_t n)
{
	unsigned char *u_ptr = (unsigned char*) ptr;

	for (size_t iter = 0; iter < n; ++iter)
	{
		if (u_ptr[iter] == ((unsigned char) c))
			return u_ptr + iter;
	}

	return NULL;
}

short cmp(const void *ptr, int c, size_t n)
{
	return mymemchr(ptr, c, n) == memchr(ptr, c, n);
}

int main()
{
	char str0[20] = "Heello, Worldu!";
	char *str_cmp = mymemchr(str0, 'l', 20);
	assert(str_cmp == (str0 + 3));
	assert(!strcmp(str_cmp, "llo, Worldu!"));

	char str1[20] = {0, 0, 0, 'f', 'o', 'o', 'b', 'a', 'r'};
	str_cmp = mymemchr(str1, 'f', 20);
	assert((str1 + 3) == str_cmp);
	assert(!memcmp(str1 + 3, str_cmp, 17 * sizeof(char)));

	str_cmp = mymemchr(str0, 'z', 20);
	assert(str_cmp == NULL);

	str_cmp = mymemchr(str1, 'z', 20);
	assert(str_cmp == NULL);

	assert(cmp("Heello, Worldu!", 'l', 16));
	assert(cmp("Heello, Worldu!", 'l', 10));
	assert(cmp("Heello, Worldu!", 'l', 2));
	assert(cmp("Heello, Worldu!", 'l', 0));

	puts("All tests passed");

	return 0;
}
