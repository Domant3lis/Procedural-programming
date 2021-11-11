// Domantas Keturakis © Workshop 7
// Limitations:
// * No functions
// * Input must be parsed using scanf paired with format specifiers

#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#define CAPACITY 1000

const char *greeter = "This program takes a number and figures out if it's a prime and if not the nearest number(s) who are\nPlease, enter seperate numbers by spaces or by the enter button. To exit enter 0\n";

int main()
{
	printf("%s", greeter);

	// stores a valid number
	int input;

	// stores whole input string
	char unparsed_line[CAPACITY] = {0};

	do
	{
		printf("Please, enter any amount of numbers: ");

		// scans user input
		scanf("%[^\n]s", unparsed_line);
		printf("\n");

		// checks if user has entered anything
		if (0 == strlen(unparsed_line))
		{
			scanf("%*c");
			input = 1;
			continue;
		}

		// parses all elements in `unparsed_line`
		do
		{
			bool correct_input = false;

			// stores only one element
			// and is a subset of whole input string `str_input`
			char str_input[CAPACITY] = {0};

			// used to check for input validity and comparison
			char str_check[CAPACITY] = {0};

			// scans an element
			sscanf(unparsed_line, "%s", str_input);

			// scans only select characters
			sscanf(str_input, "%[0-9-]s", str_check);

			// printf("DEBUG | STR_INPUT: %s\n", str_input);
			// printf("DEBUG | STR_CHECK: %s\n", str_check);

			// checks if input is correct
			{
				if (strlen(str_check) == strlen(str_input))
				{
					char c;

					sscanf(str_input, "%9d%c", &input, &c);
					// printf("DEBUG | INPUT: %d\n", input);
					// printf("DEBUG | CAHR: '%c'\n", c);

					// check if input fits into `int` type
					if ((c >= '0') && (c <= '9'))
					{
						printf("The number %s is too big to compute"
							"\n", str_input);

						c = 0;
					}
					// checks if input is positive
					else if (input < 0)
					{
						printf("The number %s does not meet the requirements. "
							"The number has to be positive\n", str_input);
					}
					else
					{
						// checks for `-` character in the middle of string
						// such as "123-123"
						sscanf(str_input, "%[0-9]s", str_check);
						unsigned long len_cmp = strlen(str_check);
						sscanf(str_input, "%[0-9-]s", str_check);

						if (len_cmp != strlen(str_check))
						{
							printf("Input \"%s\" is not a number\n", str_input);
						}
						// at this point the input is considered valid
						else
						{
							correct_input = true;
							// printf("NOT ERROR\n");
						}
					}
				}
				// handles other incorrect input
				else
				{

					sscanf(str_input, "%[0-9-.]s", str_check);

					// checks for floating point numbers
					if (strlen(str_check) == strlen(str_input))
					{
						double lf_input;
						sscanf(str_input, "%lf", &lf_input);

						// printf("UNNATURAL: %d %lf | %lf" "\n", input, (double) input, lf_input);

						if ( ((double) input ) != lf_input)
						{
							printf("The number %s does not meet the requirements."
								" It has be natural.\n", str_input);
						}
					}
					else
					{
						printf("Input \"%s\" is not a number\n", str_input);
					}

					// input is set to 1 in order not to end the input loop
					// since the loop condition is 0 != input
					// any other non-'0' value works also
					input = 1;
				}
			}

			// checks numbers for prime-ness
			if (correct_input)
			{
				// one is not considered to be a prime number
				bool is_prime = (2 > input) ? false : true;

				// checks if a number is prime
				for (int j = 2; j*j <= input; ++j)
				{
					if (input % j == 0)
					{
						is_prime = false;
						break;
					}
				}

				// prints prime number
				if (is_prime)
				{
					printf("%i is a prime number\n", input);
				}
				// finds and prints nearest primes
				else if (input != 0)
				{
					bool is_prime_a = false, is_prime_b = false;
					int offset = 0;

					// finds nearest prime numbers
					while ( (!is_prime_a) && (!is_prime_b))
					{
						++offset;

						is_prime_a = (input == 2 || input == 1) ? false : true;
						is_prime_b = true;

						// checks if a number before `offset` from the number `input` in a set of ℕ (natural numbers) is prime

						// printf("NUM_A: %d\n", input - offset);
						// printf("NUM_B: %d\n", input + offset);

						for (int j = 2; j*j <= input - offset; ++j)
						{
							if ((input - offset) % j == 0)
							{
								is_prime_a = false;
								break;
							}
						}

						// checks if a number after `offset` from the number `input` in a set of ℕ (natural numbers) is prime
						for (int j = 2; j*j <= input + offset; ++j)
						{
							if ((input + offset) % j == 0)
							{
								is_prime_b = false;
								break;
							}
						}

						// printf("DEBUG | NUM_A: %i\n", is_prime_a);
						// printf("NUM_B: %i\n", is_prime_b);
					}

					/// prints the answer
					// if there are primes at the same `offset` from the input
					if (is_prime_a && is_prime_b)
					{
						printf("Nearest prime numbers of %7i are %i and %i\n", input, input - offset, input + offset);
					}
					// there is only one nearest prime
					else if (is_prime_a)
					{
						printf("Nearest prime number  of %7i is  %i\n", input, input - offset);
					}
					// there is only one other nearest prime
					else if (is_prime_b)
					{
						printf("Nearest prime number  of %7i is  %i\n", input, input + offset);
					}
					// shouldn't ever appear, but is left here just in case
					else
						printf("AN UNHANDLED ERROR HAS OCCURED\n");

				}
			}

			printf("\n");

			/// removes parsed parts of input string from itself
			// printf("DEBUG | PRE_IF: '%s' - %lu\n", unparsed_line, strlen(unparsed_line));

			if(strlen(unparsed_line))
			{

				// printf("DEBUG | STR_INPUT: %s\n", str_input);

				int len = strlen(str_input);

				// leaves an empty string if there's only one element left
				if ( 0 == (strlen(unparsed_line) - strlen(str_input)))
				{
					unparsed_line[0] = '\0';
				}
				// removes the parsed part
				else
				{
					int j;
					for (j = 0; j < ((int) (strlen(unparsed_line) - strlen(str_input))); ++j)
					{
						// printf("DEBUG | PRE: '%c'\n", unparsed_line[j]);
						unparsed_line[j] = unparsed_line[len + j + 1];
						// printf("DEBUG | POST: '%c'\n", unparsed_line[j]);
					}
					unparsed_line[j + 1] = '\0';
				}

				// printf("DEBUG | %lu '%s'\n", strlen(unparsed_line), unparsed_line);
			}

			// printf("DEBUG | POST_IF: '%s' - %lu\n", unparsed_line, strlen(unparsed_line));
		}
		while (strlen(unparsed_line));

		// This ensures that scanf buffer is empty
		// therefore will not try to scan anything that supposedly is left
		// and instead will wait for additional user input
		scanf("%*c");
	}
	// while(1);
	while(0 != input);

   return 0;
}
