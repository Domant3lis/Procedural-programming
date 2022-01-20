// PS1 ~ Domantas Keturakis © 2022
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

char *mystrstr(char *haystack, const char *needle)
{
	bool is_strstr = true;

	while(*haystack && is_strstr)
	{
		size_t iter = 0;
		while(needle[iter])
		{
			if (needle[iter] != haystack[iter])
			{
				++haystack;
				is_strstr = false;
				break;
			}
			else
				++iter;
		}

		if (true == is_strstr)
			return haystack;
		else
			is_strstr = true;

	}

	return NULL;
}

short cmp(char *haystack, char *needle)
{
	return strstr(haystack, needle) == mystrstr(haystack, needle);
}

int main()
{
	assert(!strcmp("foobar", mystrstr("foobar", "f")));
	assert(!strcmp("foobar", mystrstr("foobar", "foo")));
	assert(!strcmp("bar", mystrstr("foobar", "bar")));
	assert(mystrstr("mmhello", "helo") == NULL);
	assert(mystrstr("mmhelo", "hello") == NULL);

	assert(cmp("foobar", "f"));
	assert(cmp("foobar", "foo"));
	assert(cmp("foobar", "bar"));
	assert(cmp("mmhello", "bar"));
	assert(cmp("mmhelo", "hello"));

	return 0;
}