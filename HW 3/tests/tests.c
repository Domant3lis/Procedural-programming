#include <assert.h>

// These are unneccesary but otherwise the linter may give annoying errors
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TEST_CAPACITY 10000

void write_results(FILE *in, FILE *out, bool is_case_sensitive);
void get_str_from_file(FILE *fp, char *str);

void test() {
	FILE *input, *temp;

	temp = fopen("./temp", "w");
	input = fopen("./tests/test0.txt", "r");
	char str[1000] = "";

	char cmp[1000] = "tenet\ntapat\nsimis\ntattarrattat\n";
	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test0.txt", "r");
	strcpy(cmp, "tenet\ntapat\nsimis\ntattarrattat\n");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test1.txt", "r");
	strcpy(cmp, "tenEt\ntapat\nsiMIs\ntattarrattat\n");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test1.txt", "r");
	strcpy(cmp, "tapat\ntattarrattat\n");

	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test2.txt", "r");
	strcpy(cmp,"Lorol\niiSii\niisIi\n,\nautemETUA\nnon\nnon\nmODodom\nesse\nnon\nnihin\n");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test2.txt", "r");
	strcpy(cmp,"iiSii\n,\nnon\nnon\nesse\nnon\nnihin\n");

	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test3.txt", "r");
	strcpy(cmp,"12345678987654321\n,./;''\\[]`==`][\\'';/.,\n"
		",sd./;''\\[]`==`][\\'';/.ds,\n"
		"123,321\n");

	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test3.txt", "r");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test4.txt", "r");
	strcpy(cmp,"did\ndid\ndid\ndid\ndid\nseeS\n");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test4.txt", "r");
	strcpy(cmp,"did\ndid\ndid\ndid\ndid\n");

	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );



	temp = fopen("./temp", "w");
	input = fopen("./tests/test5.txt", "r");
	strcpy(cmp,"did\n");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test5.txt", "r");
	strcpy(cmp,"did\n");

	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test6.txt", "r");
	strcpy(cmp,"uWwu\nUwU\n");

	write_results(input, temp, false);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	temp = fopen("./temp", "w");
	input = fopen("./tests/test6.txt", "r");
	strcpy(cmp,"UwU\n");

	write_results(input, temp, true);
	freopen("./temp", "r", temp);
	get_str_from_file(temp, str);
	assert(!strcmp(cmp, str) );


	fclose(input);
	fclose(temp);
	exit(0);
}

void get_str_from_file(FILE *fp, char *str)
{
	str[0] = 0;
	char ch = 0;
	while(ch != EOF)
	{
		char get[1000];
		fscanf(fp, "%s", get);
		strcat(str, get);
		strcat(str, "\n");

		// This is done to reach the actual end
		// sometimes the last word may be read twice
		fseek(fp, 1, SEEK_CUR);
		ch = getc(fp);
		fseek(fp, -1, SEEK_CUR);
	}
}
