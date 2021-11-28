// PS1 Domantas Keturakis ~ HW 3 © 2021
// The task is to find all palindromes in a given text give
// the results should be saved in a seperate file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define CAPACITY 256

#define _STRINGIFY(s) #s
// Converts any #define'd constant to a string
#define STRINGIFY(s) _STRINGIFY(s)

const char *CMD_OPT_HELP[] = {"-h", "--help"};
const int CMD_OPT_HELP_COUNT = 2;

const char *CMD_INPUT = "-i";
const char *CMD_OUTPUT = "-o";
const char *CMD_CASE_SENSITIVE = "-c";

const char *MSG_HELP = "This program finds all palindromes in a given text file seperated by a space.\n"
	"Use option -c if case sensitivity is important\n"
	"Use option -i ARG, to specify where input file is where ARG is the path to the file\n"
	"Use option -o ARG, to specify where output file is where ARG is the pahth to the file\n";
const char *MSG_NO_ARGS = "To learn more about this program type -h or --help option";
const char *MSG_WRONG_NO_OF_OPTS =
	"Where should be only two options each specifying a file";
const char *MSG_MISSING_ARG = "Each option should be followed by only one argument";
const char *MSG_FAILED_OPEN_IN = "Failed to open input file";
const char *MSG_FAILED_OPEN_OUT = "Failed to open or create output file";

bool user_confirmation(const char msg[]);
bool is_palindrome(char *str, bool is_case_sensitive);
void write_results(FILE *in, FILE *out, bool is_case_sensitive);

#ifdef TEST
	#include "./tests/tests.c"
#endif

int main(int argc, char const *argv[]) {

	#ifdef TEST
		test();
	#endif

	FILE *file_in, *file_out;
	bool is_case_sensitive = false;

	for (int i = 1; i < argc; ++i)
	{
		// prints a help message and quits
		// since if -h or --help is passed
		// the user probably doesn't know that they are doing
		// as so the program ends
		for (int j = 0; j < CMD_OPT_HELP_COUNT; ++j)
		{
			if (!strcmp(argv[i], CMD_OPT_HELP[j]))
			{
				printf("%s\n", MSG_HELP);
				exit(0);
			}
		}
	}

	// deals with command line options
	{
		if (1 == argc)
		{
			printf("%s\n", MSG_NO_ARGS);
			exit(0);
		}

		if(!(5 == argc || 6 == argc))
		{
			printf("%s\n", MSG_WRONG_NO_OF_OPTS);
			exit(0);
		}

		int count = 0;

		// goes through all options
		for (int i = 1; i < argc; ++i)
		{
			// handles input file
			if (!strcmp(argv[i], CMD_INPUT))
			{
				if ('-' == argv[i + 1][0])
				{
					char str[2*CAPACITY] = "Option -i has ";
					strncat(str, argv[i + 1], strlen(argv[i + 1]));
					strncat(str,
						" as an argument are you sure that this is correct [y/N]: ",
						100);
					if (!user_confirmation(str))
						exit(0);
				}

				++count;
				++i;

				file_in = fopen(argv[i], "r");

				continue;
			}

			// handles output file
			if (!strcmp(argv[i], CMD_OUTPUT))
			{
				if ('-' == argv[i + 1][0])
				{
					char str[2*CAPACITY] = "Option -i has ";
					strcat(str, argv[i + 1]);
					strcat(str,
						" as an argument are you sure that this is correct [y/N]: ");
					if (!user_confirmation(str))
						exit(0);
				}

				++count;
				++i;

				file_out = fopen(argv[i], "w");
				continue;
			}

			if (!strcmp(argv[i], CMD_CASE_SENSITIVE))
			{
				is_case_sensitive = true;
			}
		}

		// Checks if both options have been passed
		if (count != 2)
		{
			printf("%s\n", MSG_MISSING_ARG);
			exit(0);
		}
	}

	// check if all file streams have been succefully opened
	if (file_in == NULL)
	{
		printf("%s\n", MSG_FAILED_OPEN_IN);
		exit(1);
	}
	else if (file_out == NULL)
	{
		exit(1);
		printf("%s\n", MSG_FAILED_OPEN_OUT);
	}

	write_results(file_in, file_out, is_case_sensitive);

	fclose(file_in);
	fclose(file_out);

	return 0;
}

void write_results(FILE *in, FILE *out, bool is_case_sensitive)
{
	char ch = 0;

	while(ch != EOF)
	{
		char str[CAPACITY];
		fscanf(in, "%"STRINGIFY(CAPACITY)"s", str);

		if (is_palindrome(str, is_case_sensitive))
		{
			fprintf(out, "%s\n", str);
		}

		// This is done to reach the actual end
		// sometimes the last word may be read twice
		fseek(in, 1, SEEK_CUR);
		ch = getc(in);
		fseek(in, -1, SEEK_CUR);
	}
}

// Compares two chars
// As the names sugest these are case sensitive and insensitive versions
bool char_cmp_case(char a, char b) { return a == b; }
bool char_cmp_incase(char a, char b) { return toupper(a) == toupper(b); }

// This function checks if a given string is a palindrome
bool is_palindrome(char *str, bool is_case_sensitive)
{
	bool is_pal = true;
	// A pointer to a function is used to avoid
	// having an if statement inside the for loop
	// thus `is_case_sensitive` being evaluated each time and hurting performance
	bool (*cmp)(char, char) = &char_cmp_incase;
	if (is_case_sensitive)
		cmp = &char_cmp_case;

	long unsigned len = strlen(str);
	for (long unsigned i = 0; i < (len / 2); ++i)
	{
		if (!cmp(str[i], str[len - i - 1]))
		{
			is_pal = false;
			break;
		}
	}
	return is_pal;
}

// Gets user confirmation
// intended to be used then a user gives a potenttialy dangerous or unwanted command
// behaviour modeled, but not nessecceraly identically, after `dnf update` command
// this function assumes a clear scanf buffer
bool user_confirmation(const char msg[])
{
	do
	{
		char str[CAPACITY];
		printf("%s", msg);
		scanf("%"STRINGIFY(CAPACITY)"[^\n]s", str);

		if(strlen(str))
		{
			if ( (!strcasecmp(str, "y")) || (!strcasecmp(str, "yes")) )
				return true;
			else if ( (!strcasecmp(str, "n")) || (!strcasecmp(str, "no")) )
				return false;
		}
		else
			return false;

		scanf("%*c");
	}
	while(1);
}
