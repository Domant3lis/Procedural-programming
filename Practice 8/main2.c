// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// specific functions get specific names
char *getNameOfLargestFileSizeFromArrStr(int argc, char **argv);
long getFileSize(char *fileName);

int main()
{
	char *fake_argv[10] = {"main2.c", "main1.c", "Makefile"};
	int fake_argc = 3;
	assert(!strcmp(getNameOfLargestFileSizeFromArrStr(fake_argc, fake_argv), "main1.c"));

	return 0;
}

char *getNameOfLargestFileSizeFromArrStr(int argc, char **argv)
{
	long largestFile = getFileSize(*(argv));
	int largestFileIndex = 0;

	for (int i = 1; i < argc; ++i)
	{
		long cmp = getFileSize(*(argv + i));
		if (largestFile < cmp)
		{
			largestFile = cmp;
			largestFileIndex = i;
		}
	}

	return argv[largestFileIndex];
}

long getFileSize(char *fileName)
{
	FILE *file;
	file = fopen(fileName, "rb");

	if ((NULL == file) || ferror(file))
		return -1;

	fseek(file, SEEK_SET, SEEK_END);
	long len = ftell(file);

	fclose(file);

	return len;
}
