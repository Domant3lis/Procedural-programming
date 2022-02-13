#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "myutilities.h"

int main()
{
	void *tmp_void = NULL;
	TEvent *tmp = NULL;

	List *bar_list = List_create(NULL);
	List_destroy(&bar_list, &TEvent_free);
	List_print_TEvent(stdout, bar_list);

	// Initialization
	List *foo_list = List_create(TEvent_create(1 * DECIMAL_CENT_POW + 2432, USD, "Contractor"));

	// Insertion
	List_insert_element(&foo_list, TEvent_create(-420 * DECIMAL_CENT_POW - 6900, EUR, "HEATING0"));
	List_insert_element(&foo_list, TEvent_create(-420 * DECIMAL_CENT_POW - 6900, EUR, "HEATING1"));
	List_insert_element(&foo_list, TEvent_create(-420 * DECIMAL_CENT_POW - 6900, EUR, "HEATING2"));
	List_insert_element(&foo_list, TEvent_create(-420 * DECIMAL_CENT_POW - 6900, EUR, "HEATING3"));

	// Accesing values
	puts(((TEvent *) foo_list->next->next->value)->description);

	// Prints the whole list
	puts("1st print");
	List_print_TEvent(stdout, foo_list);

	// Deletes the first element
	List_delete_element(&foo_list, &TEvent_free);
	puts("\n2nd print");
	List_print_TEvent(stdout, foo_list);

	// Deletes any element we may want to
	List_delete_element_at(&foo_list, 1, &TEvent_free);
	puts("\n3rd print");
	List_print_TEvent(stdout, foo_list);

	// Insertion at selected places
	List *err = List_insert_element_at(&foo_list, 20, NULL);
	if (err != NULL)
		puts("Something has gone wrong");
	else
		puts("All ok!");

	// Selecting elements
	tmp_void = List_get_element_at(foo_list, 1)->value;
	if (tmp_void)
		TEvent_print( (TEvent *) tmp_void, stdout);

	tmp = (TEvent *)(List_get_element_at(foo_list, 3)->value);
	if(tmp)
		TEvent_print(tmp, stdout);

	puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");

	// Insertion at random points
	List_insert_element_at(&foo_list, 1, TEvent_create(369 * DECIMAL_CENT_POW, USD, "First"));
	puts("\n4th print");
	List_print_TEvent(stdout, foo_list);

	puts("\n4th print");
	List_print_TEvent(stdout, foo_list);

	List_map(foo_list, &LM_TEvent_change_description, "BarFoo");
	puts("\n5th print");
	List_print_TEvent(stdout, foo_list);

	List_map(foo_list, &LM_TEvent_convert_to_cur, EUR);
	puts("\n6th print");
	List_print_TEvent(stdout, foo_list);

	// printf("DESC: %s\n", ((TEvent *)(List_get_element_at(foo_list, 2)->value))->description );

	// // All allocated memory is freed
	List_destroy(&foo_list, &TEvent_free);

	return 0;
}
