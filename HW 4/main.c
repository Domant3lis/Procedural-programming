#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.c"
#include "list.c"
// #include "ui.c"
// #include "tests.c"

int main()
{

	TEvent *foo_0 = TEvent_create(1 * DECIMAL_CENT_POW + 2432, USD, "Contractor");
	List *foo_list = List_create(foo_0);


	puts(((TEvent *) foo_list->value)->description);

	// List_print_TEvent(stdout, foo_list);

	// TODO:
	// foo_list = List_create(NULL);

	List_insert_element(&foo_list, TEvent_create(-420 * DECIMAL_CENT_POW - 6900, EUR, "HEATING"));

	List_print_TEvent(stdout, foo_list);

	List_destroy(&foo_list);
	
	puts("\n");

	return 0;
}
