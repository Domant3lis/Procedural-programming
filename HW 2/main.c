// PS1 Domantas Keturakis © 2021
// domantas.keturakis@mif.stud.vu.lt
// The task is to calculate a polynomial's result with only one variable `x`,
// with `n + 1` terms from the biggest (power of `n`) to the smallest (power of `0`) exponent

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "ctype.h"
#include "float.h"

#define MAX_STR_LEN 50
#define PRINT_PRECISION 2
#define PRECISION_LOSS 0

// List of messages printed to the user
const char *MSG_GREETER =
	"This program calculates the answer of a given polynomial of n + 1 terms, "
	"where each terms' exponent is one less than before starting with n";
const char *MSG_ASK_NUM_OF_TERMS =
	"Please, enter the exponent of the first polynomial term: ";
const char *MSG_FAILED_ALLOCATION =
	"Failed to allocate enough memory for this polynomial, exiting program";
const char *MSG_IMPOSSIBLE_TERMS =
	"It's impossible to create a polynomial"
	" consisting of non-negative terms, exiting program";
const char *MSG_TERMS_OVERFLOW =
	"Not possible to count that many terms, exiting program";
const char *MSG_BAD_INPUT_TERMS =
	"Could not read the number of terms, exiting program";
const char *MSG_BAD_INPUT =
	"Could not read the coefficient";
const char *MSG_NOT_NATURAL_NUMBER =
	"The number of terms must be a natural number, exiting program";
const char *MSG_INFINITY_NUMBER =
	"The numbers are too large to calculate the result";
const char *MSG_NUMBER_TOO_LARGE =
	"Number is too large to store accurately";
const char *MSG_TOO_LARGE_NUM = "Number too large to compute";
const char *MSG_REENTER_TERM = "Please, reenter polynomial's coefficient: ";
const char *MSG_REENTER_X = "Please, enter the value of `x`: ";

int get_digits_lu(long unsigned num);
bool get_long_double(long double *input);

int main() {

	printf("%s\n", MSG_GREETER);

	unsigned long term_count;
	long double *input = NULL;
	long double in_x;
	long double result = 0;

	// gets data from the user
	{
		char str_input[MAX_STR_LEN];
		char c = 0;
		int sign_check = 0;
		int input_check = 0;

		// gets number of polynomial terms
		{
			printf("%s", MSG_ASK_NUM_OF_TERMS);

			scanf("%49[^\n]s", str_input);
			input_check = sscanf(str_input, "%lu%c", &term_count, &c);

			// accounts for malformated input
			if (2 == input_check)
			{
				if (isdigit(c))
					printf("%s\n", MSG_TOO_LARGE_NUM);
				else if(',' == c || '.' == c)
					printf("%s\n", MSG_NOT_NATURAL_NUMBER);
				else
					printf("%s\n", MSG_BAD_INPUT_TERMS);

				exit(1);
			}
			// accounts for malformated input
			else if (!(1 == input_check && 0 == c))
			{
				printf("%s\n", MSG_BAD_INPUT_TERMS);
				exit(1);
			}
			// accounts for negative or zero ammount of elements
			else if (sscanf(str_input, "%2d", &sign_check) == 1)
			{
				if (sign_check <= 0)
				{
					printf("%s\n", MSG_IMPOSSIBLE_TERMS);
					exit(1);
				}
			}
			// catches overflows
			if (strlen(str_input) != ((long unsigned) get_digits_lu(term_count)))
			{
				printf("%s\n", MSG_TERMS_OVERFLOW);
				exit(1);
			}

			input = calloc(term_count, sizeof(long double));

			if (NULL == input)
			{
				printf("%s\n", MSG_FAILED_ALLOCATION);
				exit(1);
			}
		}

		// Each term's exponent corresponds to an index of the input array
		// The value that is stored at that index is the coefficient of the same term
		// ax^y
		// input[i] -> a;  i  -> y
		// ...
		// input[2] -> a;  2 -> y
		// input[1] -> a;  1 -> y
		// input[0] -> a;  0 -> y

		int i = term_count;
		do
		{
			printf("Please, enter polynomial's, whose exponent is %i, coefficient: ", i);

			bool successful_read = get_long_double(&input[i]);
			if (!successful_read)
				++i;

			--i;
		}
		while (i >= 0);

		// gets `x` from user
		bool successful_read;
		printf("%s", MSG_REENTER_X);
		do
		{
			successful_read = get_long_double(&in_x);

			if (!successful_read)
				printf("%s", MSG_REENTER_X);

		}
		while(!successful_read);

	}

	// calculates the result of the polynomial
	for (int i = term_count; i >= 0; --i)
	{
		//               a * (x^y)
		result += input[i] * (long double) pow(in_x, i);
	}

	free(input);

	// checks for infinite numbers
	if (isinf(result))
	{
		printf("%s\n", MSG_INFINITY_NUMBER);
		exit(1);
	}

	// prints the result
	printf("%s%.*Lf\n", "The result is: ", PRINT_PRECISION, result);

	return 0;
}

// this function gets from the user a long double type variable
// returns true if successful and false if not
bool get_long_double(long double *input)
{
	bool successful_read = false;
	char str_input[MAX_STR_LEN];
	char c = 0;
	int input_check = 0;

	char format[MAX_STR_LEN] = "%";
	{
		char ld_max_digits[MAX_STR_LEN];
		sprintf(ld_max_digits, "%d", LDBL_DIG + PRECISION_LOSS);
		strcat(format, ld_max_digits);
		strcat(format, "Lf%c");
		// format = "%LDBL_DIGLf%c"
		// printf("FORMAT: '%s'\n", format);
	}

	// clear scanf buffer
	scanf("%*[^\n]s");
	scanf("\n");

	// scans input
	scanf("%49[^\n]s%*c", str_input);
	input_check = sscanf(str_input, format, input, &c);

	// checks for input correctness
	if(isdigit(c))
	{
		printf("%s\n", MSG_NUMBER_TOO_LARGE);
	}
	else if (1 != input_check)
	{
		printf("%s\n", MSG_BAD_INPUT);
	}
	else
		successful_read = true;

	return successful_read;
}

int get_digits_lu(long unsigned num)
{
	return (num == 0) ? 1 : log10(num) + 1;
}
