// PS1 Domantas Keturakis ~ HW 3 © 2021
// The task is to find all palindromes in a given text give
// the results should be saved in a seperate file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 256
#define BUFFER_SIZE 1024

#define _STRINGIFY(s) #s
// Converts any #define'd constant to a string
#define STRINGIFY(s) _STRINGIFY(s)

const char *CMD_HELP = "-h";
const char *CMD_INPUT = "-i";
const char *CMD_OUTPUT = "-o";
const char *CMD_CASE_SENSITIVE = "-c";

const char *MSG_FAILED_ALLOCATION =
	"There is not enought memory to process this text";
const char *MSG_NO_INPUT_FILE = "Please, specify input file path: ";
const char *MSG_NO_ARGS = "To learn more about this program pass -h option";
const char *MSG_MISSING_ARG = "This option should be followed by an argument";
const char *MSG_FAILED_OPEN_IN = "Failed to open input file";
const char *MSG_FAILED_OPEN_OUT = "Failed to create output file";
const char *MSG_HELP = "This program finds all palindromes in a given text file seperated by a space.\n"
	"Use option -c if case sensitivity is important\n"
	"Use option -i ARG, to specify output file, where ARG is the path to the file\n"
	"Use option -o ARG, to specify input file, where ARG is the path to the file\n";

bool is_palindrome(char *str, bool is_case_sensitive);
bool has_option(int argc, char const *argv[], const char *opt, char *arg);
void write_results(FILE *in, FILE *out, bool is_case_sensitive);
void get_str_from_stdin(const char print_msg[], char *msg);

// Used only and included then testing is done
#ifdef TEST
	#include "./tests/tests.c"
#endif

int main(int argc, char const *argv[]) {

	// Only is called then TEST is defined
	// run `make test` to enable and run this
	#ifdef TEST
		test();
		#undef BUFFER_SIZE
		#define BUFFER_SIZE 1024*2
		test();
		#undef BUFFER_SIZE
		#define BUFFER_SIZE 9000
		test();
		#undef BUFFER_SIZE
		#define BUFFER_SIZE 1978
		test();
		#undef BUFFER_SIZE
		#define BUFFER_SIZE 1111
		test();
		printf("ALL TESTS PASSED SUCCEFULLY\n");
	#endif

	FILE *file_in = NULL;
	FILE *file_out = NULL;

	char str_in[CAPACITY] = "\1";
	char str_out[CAPACITY] = "\1";
	if (has_option(argc, argv, CMD_HELP, "\0"))
	{
		printf("%s\n", MSG_HELP);
		exit(0);
	}

	if(argc == 1)
	{
		printf("%s\n", MSG_NO_ARGS);
		exit(0);
	}

	bool is_in = has_option(argc, argv, CMD_INPUT, str_in);
	bool is_out = has_option(argc, argv, CMD_OUTPUT, str_out);
	bool is_case_sensitive = has_option(argc, argv, CMD_CASE_SENSITIVE, "\0");

	if(is_in)
	{
		file_in = fopen(str_in, "r");
	}

	// Part of UI, print a message only if
	// input file was specified in the command line
	// but failed to open
	if (is_in && (file_in == NULL))
		printf("%s\n", "Specified input file could not be read");

	// Repeatedly asks the user to specify a corrent input file
	// until a valid file path is given
	while(file_in == NULL)
	{

		get_str_from_stdin(MSG_NO_INPUT_FILE, str_in);
		file_in = fopen(str_in, "r");
		if (file_in == NULL)
			printf("%s\n", "Invalid file");
	}

	// Deals with output file stream
	if (is_out)
		file_out = fopen(str_out, "w");

	if (file_out == NULL)
		file_out = stdout;

	write_results(file_in, file_out, is_case_sensitive);


	fclose(file_in);
	fclose(file_out);

	return 0;
}

// Find a word (sequence of characters terminated by ' ' or '\n')
// at the end of a string `str` with size of `size`
// and saves the result into `last_str`
//
// IMPORTANT:
// `last_str` should have capacity equal to or greater than `size`
// BEFORE calling this function
//
// If a string ends with ' ' or '\n' it is considered that it ends with no
// word and wherefore returns an empty string
void find_word_from_end (char *str, size_t size, char *last_str)
{
	// creates and allocates memory for temporary variables
	size_t ix = size - 1;
	char ch = str[ix];

	// finds the start of last word
	while(!(ch == 0 || ch == '\n') && (ix > 0))
		ch = str[--ix];

	// saves the last word into `last_str`
	int jx = -1;
	for (size_t i = ++ix; i < size; ++i)
		last_str[++jx] = str[i];

	last_str[++jx] = 0;
}

// Checks if dynamic string allocation has failed
// and quits the program if it does
void str_alloc_check(char *str)
{
	if (str == NULL)
	{
		printf("%s\n", MSG_FAILED_ALLOCATION);
		exit(0);
	}
}

// This functions finds all palindromes from a given file stream (`in`)
// and writes the resuts into another (`out`)
// `is_case_sensitive` provides the option to
//
// IMPORTANT:
// This function does not open or close any file streams
// they should be opened and closed before and after the function is called
void write_results(FILE *in, FILE *out, bool is_case_sensitive)
{
	// Gets file size
	fseek(in, 0, SEEK_END);
	int file_size = ftell(in);
	fseek(in, 0, 0);

	// Allocates memory for a string buffer
	char *buffer = NULL;
	buffer = calloc(sizeof(char), BUFFER_SIZE);
	str_alloc_check(buffer);

	// Allocates memeory for a string
	char *last_word = NULL;
	last_word = calloc(sizeof(char), BUFFER_SIZE);
	str_alloc_check(last_word);
	strcpy(last_word, "");

	size_t size;

	do
	{
		size = fread(buffer, sizeof(char), BUFFER_SIZE, in);

		// counts all the words in the buffer
		// this is neccesary in order to later check if a word
		// is the last word and handle that appropriately
		// since they might be split accross buffers
		int word_count = 0;
		{
			char *buffer_cpy = NULL;
			buffer_cpy = calloc(sizeof(char), BUFFER_SIZE);
			str_alloc_check(buffer_cpy);
			strcpy(buffer_cpy, buffer);

			char *word = strtok(buffer_cpy, " \n");
			str_alloc_check(word);
			while(word != NULL)
			{
				++word_count;
				word = strtok(NULL, " \n");
			}
			free(buffer_cpy);
		}

		// Allocates memory for a temporary string
		char *result = NULL;
		result = calloc(sizeof(char), BUFFER_SIZE);
		str_alloc_check(result);

		// Tracks how many chars are left unread
		// and later compares to BUFFER_SIZE
		// this is done in order to see if a word
		// is last in the text so that it can be cheched as unsplit word
		// as compared to other words at the end of buffers which may be split
		file_size -= BUFFER_SIZE;
		bool last_buffer = true;
		if (file_size > 0)
			last_buffer = false;

		char *word = strtok(buffer, " \n");

		int ix = 0;
		while(word != NULL)
		{
			// if the last read buffer has a word at the end it means
			// that it may have been split between buffers and it is
			// neccesary to check if the the current buffer doesnt begin
			// with a word which has been split up between buffers
			bool check = is_palindrome(word, is_case_sensitive);
			check = check && (((ix + 1) != word_count) || last_buffer);

			if (strlen(last_word) && (0 == ix) && (word[0] != ' ' || word[0] != '\n'))
			{
				char *word_split = NULL;
				word_split = calloc(sizeof(char), BUFFER_SIZE);
				str_alloc_check(word_split);

				strcat(word_split, last_word);
				strcat(word_split, word);


				if (is_palindrome(word_split, is_case_sensitive))
				{
					strcat(result, word_split);
					strcat(result, "\n");
				}
				free(word_split);
			}
			else if (check)
			{
				strcat(result, word);
				strcat(result, "\n");
			}

			word = strtok(NULL, " \n");
			++ix;
		}

		last_word = calloc(sizeof(char), BUFFER_SIZE);
		find_word_from_end(buffer, size, last_word);
		fprintf(out, "%s", result);
		free(result);
	}
	while(size == BUFFER_SIZE);

	free(buffer);
	free(last_word);
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

// Gets a string from stdin
// and print an accompanying message stored in `print_msg`
// IMPORTANT: this function assumes a clean scanf buffer
void get_str_from_stdin(const char print_msg[], char *str)
{
	int has_input = 0;

	do
	{
		printf("%s", print_msg);
		has_input = scanf("%[^\n]s", str);
		scanf("%*c");
	}
	while(!has_input);
}

// This functions checks if an option was passed
// argc - argument count, argv all arguments passed to the program
// opt - command line option
// arg - stores the argument if arg[0] == 1 in arg
// 	and - checks if argumentless option was passed if arg[0] == 0
bool has_option(int argc, char const *argv[], const char *opt, char *arg)
{
	bool success = false;

	for (int i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i], opt))
		{

			if (arg[0] == 0)
			{
				success = true;
			}
			else
			{
				++i;

				if (i == argc && strlen(opt))
				{
					printf("%s\n", MSG_MISSING_ARG);
					exit(0);
				}
				else if ('-' == argv[i][0])
				{
					printf("%s\n", "Ambigious options passed");
					exit(0);
				}

				strcpy(arg, argv[i]);
				success = true;
			}

			break;
		}
	}

	return success;
}
