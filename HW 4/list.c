#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "myutilities.h"
#include "list.h"

// TODO: Read these values from file so that they could be updated more easily
//
// 1 EUR = 1.13469 USD Jan 21, 2022, 22:31 UTC
// 1 USD = 0.881337 EUR Jan 21, 2022, 22:34 UTC
// Source: https://www.xe.com/currencycharts/?from=USD&to=EUR
const float CUR_CONV_RATE[] = 
{
	1.13469, 
	0.881337,
};

const enum 
{ 
	EUR_TO_USD,
	USD_TO_EUR,
} CUR_CONV;

#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

#define COLL_0 10
#define COLL_1 15
#define COLL_END COLL_1 + 15
#define MAX_LINE_LEN 50

const char *CUR_LIST[] =
{
    "USD",
    "EUR",
};

List *List_create(void *value)
{
	List *new = calloc(sizeof(List), 1);
	if (!new)
		return NULL;

	new->value = value;
	new->next = NULL;
	return new;
}

size_t List_get_size(List *list)
{
	size_t count = 0;
	while (list != NULL)
	{
		list = list->next;
		++count;
	}
	return count;
}

// Iterates over all elements and passes them into a function `fun`, which can take any amount of additional arguments through a variable of `va_list` type (see docs for stdarg.h)
//  
void List_map(List *list, void (*fun)(void *, va_list), ...)
{
	va_list args;
	va_start(args, fun);

	while (list)
	{
		(*fun)(list->value, args);
		list = list->next;
	}

	va_end(args);
}

// Gets an elements from position at `poz` in list `list` 
List *List_get_element_at(List *list, size_t poz)
{
	while(list->next && poz--)
	{
		list = list->next;
	}

	if (0 == poz)
		return NULL;
	else
		return list;
}

// inserts a new element in a List at position `poz`
// Returns the pointer to the value inserted if insertion was successful, otherwise NULL 
List *List_insert_element_at(List **list, size_t poz, void *value)
{
	List *cur = *list;
	List *prev = *list;
	while (poz--)
	{
		if (cur == NULL)
			return NULL;

		prev = cur;
		cur = cur->next;
	}

	List *new = List_create(value);
	new->next = cur;
	prev->next = new;

	return new;
}

// Inserts an element at the top of a `List`
void List_insert_element(List **list, void *value)
{
	List *new = List_create(value);
	new->next = *list;
	*list = new;
}

// Frees all elements in a list
// `**list` is a pointer to a pointer to the start of the list
// a pointer pointing somethere else will only free elements from that point till end.
//
// `*free_el` is a pointer to a function which frees the contents of the elements held
// if your data type has, for example, strings allocated on the heap, then `free_el` must free those strings held inside your data type
void List_destroy(List **list, void (*free_el)(void *))
{
	List *next;
	List *current = (*list);

	while (current != NULL)
	{
		next = current->next;

		if (current->value != NULL)
		{
			(*free_el)(current->value);
			free(current->value);
		}

		free(current);

		current = next;
	}

	(*list) = NULL;
}

// Deletes the first element from a `List`
// `**list` is a pointer (to a pointer) to the first start of the List 
// `*free_el` - ditto
void List_delete_element(List **list, void (*free_el)(void *))
{
	List *next = (*list)->next;
	List *current = (*list);
	(*free_el)(current->value);
	free(current->value);
	free(current);
	*list = next;
}

// Deletes an element from a `List`
// Returns 0 if poz is too big
// Returns 1 if specified elements exist
// and can be deletes
// `*free_el` - ditto
short List_delete_element_at(List **list, size_t poz, void (*free_el)(void *))
{
	// size_t i = 0;
	// printf("NUM: %zu", i);
	List *cur = *list;
	List *prev = *list;
	while (poz--)
	{
		if (cur == NULL)
			return 0;

		prev = cur;
		cur = cur->next;
		// ++i;
	}

	List *next = NULL;
	if (cur->next != NULL)
		next = cur->next;
	
	(*free_el)(cur->value);
	free(cur->value);
	free(cur);
	puts(((TEvent *)prev->value)->description);
	prev->next = next;

	return 1;
}

// Frees all contents held inside TEvent
// Without freeing itself
// Intended to be used as a parameter to functions with free_el argument
void TEvent_free(void *event)
{
	TEvent *event_typed_ptr = (TEvent *)event;
	free(event_typed_ptr->description);
}

// Allocates enough memory for TEvent and its contents to be stored and returns a pointer to it
TEvent *TEvent_create(long long value, Currency cur, char *desc)
{
	TEvent *event = calloc(sizeof(TEvent), 1);

	if (!event)
		return NULL;

	event->value = value;
	event->currency = cur;

	// This line causes all unfreed memory
	event->description = strdup(desc);
	// event->description = desc;

	return event;
}

const char *TEvent_get_currency(TEvent *event)
{
	return CUR_LIST[event->currency];
}

char *TEvent_value_to_str(long long value)
{
	// Gets parts of whole and cent parts
	char *sign = (value > 0) ? " +" : (value > -1 * DECIMAL_CENT_POW) ? " -" : " ";

	long long whole = value / DECIMAL_CENT_POW;
	long long cent = value;
	cent = (cent >= 0) ? cent : -cent;
	cent %= DECIMAL_CENT_POW;
	cent = cent / pow_int32(10, DECIMAL_CENT_POZ - 2);

	// Constructs the string
	// TODO: Figure out why this isn't free()'d
	char *str = calloc(sizeof(char), MAX_LINE_LEN);
	str[0] = 0;
	char tmp[MAX_LINE_LEN] = {0};
	sprintf(str, "%s%lld", sign, whole);
	strcat(str, ".");
	sprintf(tmp, "%02lld", cent);
	strcat(str, tmp);

	return str;
}

// Functions to be used with List_Map LM for short
// 
// Changes the description of all TEvents
void TEvent_change_desc(TEvent *event, char *str)
{
	free(event->description);
	event->description = strdup(str);
}
void LM_TEvent_change_description(void *event, va_list args)
{
	va_list args_cpy;
	va_copy(args_cpy, args);
	char *str = va_arg(args_cpy, char *);

	TEvent_change_desc((TEvent *) event, str);
}

// Converts between supported (atm not many) currencies
long long TEvent_convert_cur(TEvent *event, Currency to)
{
	if (event->currency == to)
		return event->value;

	long double tmp = event->value;

	// Converts to USD
	// Then converts to `to`
	switch (event->currency)
	{
	case EUR:
		tmp = tmp * CUR_CONV_RATE[EUR_TO_USD];
		break;
	default:
		break;
	}

	event->currency = to;

	switch (to)
	{
	case EUR:
		tmp = tmp * CUR_CONV_RATE[USD_TO_EUR];
		break;
	default:
		break;
	}

	return tmp;
}
void LM_TEvent_convert_to_cur(void *event, va_list args)
{
	va_list args_cpy;
	va_copy(args_cpy, args);
	Currency to = va_arg(args_cpy, Currency);

	long long conv = TEvent_convert_cur((TEvent *)event, to);
	((TEvent *)event)->value = conv;
}

// Functions for outputing the List of TEvents
void TEvent_print(TEvent *event, FILE *out)
{
	// Constructs the string
	char str[MAX_LINE_LEN] = {0};
	char *tmp = TEvent_value_to_str(event->value);
	sprintf(
		str,
		"%-" STRINGIFY(COLL_0) "s| %-" STRINGIFY(COLL_1) "s|  %s",
		TEvent_get_currency(event),
		tmp, event->description);
	free(tmp);

	// Prints it
	fprintf(out, "%s\n", str);
}
void LM_TEvent_print(void *event, va_list args)
{
	va_list args_cpy;
	va_copy(args_cpy, args);
	FILE *out = va_arg(args_cpy, FILE *);

	TEvent_print((TEvent *) event, out);
}

void List_print_TEvent(FILE *out, List *events)
{
	List *start = events;

	if (NULL == events)
	{
		fprintf(stderr, "ERROR: Attempt to print an empty list!\n");
		return;
	}

	char str[MAX_LINE_LEN] = {0};
	sprintf(str,
			"%-" STRINGIFY(COLL_0) "s| %-" STRINGIFY(COLL_1) "s|  Description",
			"Currency", "Transfer");

	fprintf(out, "%s\n", str);
	char fill[MAX_LINE_LEN + 1] = {0};
	do_spacing_with(fill, '=', COLL_END);
	fprintf(out, "%s\n", fill);

	List_map(events, &LM_TEvent_print, out);

	do_spacing_with(fill, '=', COLL_END);
	fprintf(out, "%s\n", fill);

	long long sum = 0;
	while(events)
	{
		sum += ((TEvent *) events->value)->value;
		events = events->next;
	}

	char *tmp = TEvent_value_to_str(sum);
	fprintf(out, "Remaining: %s | No. of Items: %lu\n\n", tmp, List_get_size(start));
	free(tmp);
}
