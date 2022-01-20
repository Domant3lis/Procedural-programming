// PS1 ~ Domanas Keturakis © 2022
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

char *mystrncpy(char *dest, char *src, size_t n)
{

	size_t i = 0;

	if (n)
		do
		{
			dest[i] = src[i];
			++i;
		}
		while (src[i] && i < n);

	for (; i < n; ++i)
		dest[i] = 0;
	
	return dest;
}

short cmp_by_char(char *left, char *right, size_t n)
{
	for (size_t i = 0; i < n; ++i)
		if (left[i] != right[i])
			return 0;

	return 1;
}

void print_by_char(char *str, size_t n)
{ 
	for (size_t i = 0; i < n; ++i)
		printf("%c %d \t", str[i], str[i]);
}

int main()
{

	// tests cmp_by_char()
	assert(cmp_by_char("asd", "asd", 3) == 1);
	assert(cmp_by_char("asdabd", "asd", 6) == 0);
	assert(cmp_by_char("asd", "asdasd", 6) == 0);

	// tests mystrcpy();
	char *str0 = "Heelo, WOSLD";
	char str1[20];
	char str2[20];
	mystrncpy(str1, str0, 20); 
	strncpy(str2, str0, 20); 
	assert(cmp_by_char(str2, str1, 20));

	char *str3 = calloc(20, sizeof(char));
	char *str4 = calloc(20, sizeof(char));
	str3 = mystrncpy(str3, str0, 20);
	str4 = strncpy(str4, str0, 20); 
	assert(cmp_by_char(str3, str4, 20));
	free(str3);
	free(str4);

	char *str5 = "Hello, \0 world!";
	char str6[20]; 
	char str7[20];
	strncpy(str6, str5, 20);
	mystrncpy(str7, str5, 20);
	assert(cmp_by_char(str7, str6, 20));

	char *str8 = "Hello, World!";
	char str9[20] = "lolno, you!";
	char str10[20] = "no-ol, you!";
	strncpy(str9, str8, 5);
	mystrncpy(str10, str8, 5);
	assert(cmp_by_char(str9, str10, 12));

	char str11[5];
	char str12[5];
	strncpy(str11, str8, 5);
	mystrncpy(str12, str8, 5);
	assert(cmp_by_char(str11, str12, 5));

	char str13[5] = {1, 2, 3, 4, 5};
	char str14[5];
	memcpy(str14, str13, sizeof(char) * 5);
	mystrncpy(str14, str13, 0);
	assert(cmp_by_char(str13, str14, 5));

	return 0;
}