// Domantas Keturakis © 2021
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

short splitData(void *data, size_t size, size_t splitAt, void **dst0, void **dst1)
{
	if (data == NULL || *dst0 != NULL || *dst1 != NULL || size < splitAt)
		return -1;

	*dst0 = malloc(splitAt);
	*dst1 = malloc(size - splitAt);

	// void * cannot be dereferenced so they are converted into
	// pointers which point to each byte
	uint8_t *data_tmp = (uint8_t *) (data);
	uint8_t *dst0_tmp = (uint8_t *) (*dst0);
	uint8_t *dst1_tmp = (uint8_t *) (*dst1);

	for (size_t i = 0; i < splitAt; ++i)
		dst0_tmp[i] = data_tmp[i];

	for (size_t i = splitAt; i <= size; ++i)
		dst1_tmp[i - splitAt] = data_tmp[i];

	return 0;
}

int main()
{
	char *str = "Hello, World!";
	char *str0 = NULL;
	char *str1 = NULL;
	char *str_er = NULL;

	if (!splitData(str_er, 10000, 5 * sizeof(char), &str0, &str1))
		printf("STR: '%s'  STR0: '%5s'  STR1: '%s'\n", str_er, str0, str1);
	else
		printf("ERROR!\n");
	printf("\n");

	printf("STR: %s\n", str);
	if (!splitData(str, (strlen(str) + 1) * sizeof(char), 5 * sizeof(char), &str0, &str1))
		printf("STR: '%s'  STR0: '%5s'  STR1: '%s'\n", str, str0, str1);
	else
		printf("ERROR!\n");


	short nums[] = {0, 1, 2, 3, 4, 5, 6, 7};
	size_t numc = 7;
	short *nums0 = NULL;
	short *nums1 = NULL;
	if (!splitData(nums, numc * sizeof(short), 4 * sizeof(short), &nums0, &nums1))
	{
		for (size_t i = 0; i < 5; ++i)
		{
			printf("NUMS0: %d\n", nums0[i]);
			printf("NUMS1: %d\n", nums1[i]);
			printf("\n");
		}
	}
	else
		printf("ERROR!\n");

	if (!splitData(str, (strlen(str) + 1) * sizeof(char), 5 * sizeof(char), &str0, &str1))
		printf("STR: '%s'  STR0: '%5s'  STR1: '%s'\n", str, str0, str1);
	else
		printf("ERROR!\n");

	free(str0);
	free(str1);
	free(nums0);
	free(nums1);

	return 0;
}
