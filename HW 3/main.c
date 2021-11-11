// PS1 Domantas Keturakis ~ HW 3 © 2021
// The task is to find all palindromes in a given text give
// the results should be saved in a seperate file
// THIS PROGRAM IS WIP AND NOT FINISHED

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "ctype.h"

#define CAPACITY 256

const char *CMD_OPT_HELP[] = {"-h", "--help"};
const int CMD_OPT_HELP_COUNT = 2;

const char *CMD_INPUT = "-i";
const char *CMD_OUTPUT = "-o";

const char *MSG_HELP = "This program finds all words seperated by a space";
const char *MSG_NO_ARGS = "To learn more about this program type -h or --help option";
const char *MSG_MISSING_ARG = "One or both options are missing arguments";
const char *MSG_FAILED_OPEN_IN = "Failed to open input file";
const char *MSG_FAILED_OPEN_OUT = "Failed to open or create output file";

bool user_confirmation(const char msg[]);

int main(int argc, char const *argv[]) {

	/// TODO:
	// REFACTOR: seperate handling of cmd options into a function
	// fix user_confirmation

	printf("ARGC: %d\n", argc);
	FILE *in, *out;

	// deals with command line options
	// and opens neccessary file streams
	{
		// char

		if (1 == argc)
		{
			printf("%s\n", MSG_NO_ARGS);
			exit(0);
		}

		// goes through all options
		for (int i = 1; i < argc; ++i)
		{
			// prints a help message
			for (int j = 0; j < CMD_OPT_HELP_COUNT; ++j)
			{
				if (!strcmp(argv[i], CMD_OPT_HELP[j]))
				{
					printf("%s\n", MSG_HELP);
					exit(0);
				}
			}

			// handles input file
			if (!strcmp(argv[i], CMD_INPUT))
			{
				// printf("%s\n", "INPUT");

				//
				if (i == argc)
				{
					printf("%s\n", "Missing argument for input");
					exit(0);
				}

				++i;

				if ('-' == argv[i][0])
				{
					if (!user_confirmation("ARE YOU SURE [y/N]: "))
					{
						printf("%s\n", "NO");
						exit(0);
					}
					else
					{
						printf("%s\n", "OK");
					}
				}

				in = fopen(argv[i], "r");
				continue;
			}

			// handles output file
			if (!strcmp(argv[i], CMD_OUTPUT))
			{
				// printf("%s\n", "INPUT");

				//
				if (i == argc)
				{
					printf("%s\n", "Missing argument for input");
					exit(0);
				}

				++i;

				if ('-' == argv[i][0])
				{
					if (!user_confirmation("ARE YOU SURE [y/N]: "))
					{
						printf("%s\n", "NO");
						exit(0);
					}
					else
					{
						printf("%s\n", "OK");
					}
				}

				out = fopen(argv[i], "a");
				continue;
			}


		}
	}

	if (in == NULL)
	{
		printf("%s\n", MSG_FAILED_OPEN_IN);
		exit(1);
	}
	else if (out == NULL)
	{
		exit(1);
		printf("%s\n", MSG_FAILED_OPEN_OUT);
	}


	// fopen
		// error handling
	// FUNCTION"
		// for (START_OF_FILE..END_OF_FILE)
			// find text[word_start] and text[word_end]
				// word_start   word_end
				//      |         |
				// [' ' + 1;  ' ' - 1]
			// word = text[word_start..word_end]
			// bool check_word(text, word_start, word_end)
			// if (true)
				// fprintf(found_word)
			// if (text[i] == '\n')
				// fprintf("\n")

	// fclose
		// error handling
	fclose(in);
	fclose(out);

	return 0;
}

// Gets user confirmation
// intended to be used then a user gives a suspicious command
// behaviour modeled, but not nessecceraly identically, after `dnf update` command
// this function assumes a clear scanf buffer
bool user_confirmation(const char msg[])
{
	// TODO
	// scanf("%*[^\n]%*c");
	// scanf("\n");
	char c[1];

	do
	{
		printf("%s", msg);
		scanf("%1[^\n]s\n", c);

		if (toupper(*c) == 'Y')
			return true;
		else if (toupper(*c) == 'N')
			return false;

		scanf("\n");
	}
	while(1);
}
