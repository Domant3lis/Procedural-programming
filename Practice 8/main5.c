// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_ERR "An has error occurred"

typedef struct 
{
	char ***matrix;
	size_t n;
	size_t m;
} StrMatrix;

// Prints all contents inside str_matrix 
void print_StrMatrix(FILE *out, StrMatrix *str_matrix)
{
	for (size_t i = 0; i < str_matrix->n; ++i)
	{
		for (size_t j = 0; j < str_matrix->m; ++j)
		fprintf(out, "\"%s\", ", str_matrix->matrix[i*str_matrix->m + j]);

		fprintf(out, "\n");
	}
}

// Creates a new string matrix and fils it with empty values e.g. NULL
short create_StrMatrix(StrMatrix *str_matrix, size_t n, size_t m)
{
	str_matrix->n = n;
	str_matrix->m = m;

	str_matrix->matrix = calloc(sizeof(char ***), n*m);
	
	if(!(str_matrix->matrix))
		return 0;

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			str_matrix->matrix[i*m + j] = NULL;

	return 1;
}

// Changes string inside `str_matrix` at line `i` and column `j` to `src`
short set_at_StrMatrix(StrMatrix *str_matrix, char *src, size_t i, size_t j)
{
	if (str_matrix->n <= i || (str_matrix->m <= j))
		return 0;

	str_matrix->matrix[str_matrix->m * i + j] = strdup(src);

	return 1;
}

// Returns a pointer to the string inside `str_matrix` at line `i` and column `j`
char *get_at_StrMatrix(StrMatrix *str_matrix, size_t i, size_t j)
{
	if (str_matrix->n <= i || (str_matrix->m <= j))
		return NULL;

	return str_matrix->matrix[str_matrix->m*i + j];
}

// Free()'s all strings inside this matrix
// and sets `m` and `n` to 0
void destroy_StrMatrix(StrMatrix *str_matrix)
{
	for (size_t i = 0; i < str_matrix->n; ++i)
		for (size_t j = 0; j < str_matrix->m; ++j)
		{
			free(str_matrix->matrix[i * str_matrix->m + j]);
		}

	str_matrix->n = 0;
	str_matrix->m = 0;
}

int main()
{
	StrMatrix foo;

	if(!create_StrMatrix(&foo, 5, 5))
	{
		printf("%s\n", MSG_ERR);
		exit(0);
	}

	StrMatrix bar;
	if (!create_StrMatrix(&bar, 1000000000000, 1000000000000))
		printf("%s\n", MSG_ERR);

	print_StrMatrix(stdout, &foo);

	set_at_StrMatrix(&foo, "Hello", 0, 0);
	set_at_StrMatrix(&foo, ",", 1, 1);
	set_at_StrMatrix(&foo, " ", 2, 2);
	set_at_StrMatrix(&foo, "World", 3, 3);
	set_at_StrMatrix(&foo, "!", 4, 4);
	if (!set_at_StrMatrix(&foo, "ERR", 10, 10))
		printf("%s\n", MSG_ERR);
	

	printf("\n");

	print_StrMatrix(stdout, &foo);

	printf("1:1  '%s'\n", get_at_StrMatrix(&foo, 1, 1));
	printf("2:2  '%s'\n", get_at_StrMatrix(&foo, 2, 2));
	printf("3:3  '%s'\n", get_at_StrMatrix(&foo, 3, 3));
	printf("4:4  '%s'\n", get_at_StrMatrix(&foo, 4, 4));
	printf("10:10  '%s'\n", get_at_StrMatrix(&foo, 10, 10));

	print_StrMatrix(stdout, &foo);

	destroy_StrMatrix(&foo);

	print_StrMatrix(stdout, &foo);

	return 0;
}