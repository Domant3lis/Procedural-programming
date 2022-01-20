#pragma once
#include <stdio.h>
#include <string.h>
#include "list.c"
#include "other.c"

#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

#define COLL_0 10
#define COLL_1 15
#define COLL_END COLL_1 + 15
#define MAX_LINE_LEN 50

const unsigned char DECIMAL_CENT_POZ = 4;
#define DECIMAL_CENT_POW pow_int32(10, DECIMAL_CENT_POZ)

const char *CUR_LIST[] =
{
	"Unknown",
	"USD",
	"EUR",
};

typedef enum
{
	USD = 1,
	EUR,
} Currency;

typedef struct
{
	char *description;

	// The worlds networth is              418 342 000 000 000
	// Singed Long long max value is 9 223 372 036 854 775 807
	// Therefore, last 4 (decimal) digits will be dedicated to 
	// cents
	// 
	// Positive value means income
	// Negative value means expenses
 	long long value;
	Currency currency;
} TEvent; // Short for transaction event

TEvent *TEvent_create(long long value, Currency cur, char *desc)
{
	TEvent *event = calloc(sizeof(TEvent), 1);

	if (!event)
		return NULL;

	event->value = value;
	event->currency = cur;
	event->description = strdup(desc);

	return event;
}

const char *TEvent_get_currency(TEvent *event)
{
	return CUR_LIST[event->currency];
}

char *TEvent_value_to_str(TEvent *event)
{
	// Gets parts of whole and cent parts
	long long whole = event->value / DECIMAL_CENT_POW;
	long long cent = event->value;
	cent = (cent >= 0) ? cent : -cent;
	cent %= DECIMAL_CENT_POW;
	cent = cent / pow_int32(10, DECIMAL_CENT_POZ - 2);

	// Constructs the string
	char *str = calloc(sizeof(char), MAX_LINE_LEN);
	str[0] = 0;
	char tmp[MAX_LINE_LEN] = { 0 };
	sprintf(str, "%+-lld", whole);
	strcat(str, ".");
	sprintf(tmp, "%02lld", cent);
	strcat(str, tmp);

	return str;
} 

void TEvent_print(FILE *out, TEvent *event)
{
	// Constructs the string
	char str[MAX_LINE_LEN] = { 0 };
	char *tmp = TEvent_value_to_str(event);
	sprintf(str,
		"%-" STRINGIFY(COLL_0) "s| %-" STRINGIFY(COLL_1) "s|  %s",
		TEvent_get_currency(event), tmp, event->description);

	// Prints it
	fprintf(out, "%s\n", str);
	free(tmp);
}

void List_insert_TEvent(List **list, TEvent event)
{
	// TEvent 
	// (TEvent *)&foo_0 = TEvent_create(-2 * DECIMAL_CENT_POW - 1000, EUR, "Water bill");
	// List_insert_element(&foo_list, &foo_0);
}
// void List_insert_TEvent_at

// ≡
void List_print_TEvent(FILE *out, List *events)
{
	List *or = events;
	char str[MAX_LINE_LEN] = { 0 };
	sprintf(str,
		"%-" STRINGIFY(COLL_0) "s| %-" STRINGIFY(COLL_1) "s|  Description",
		"Currency", "Transfer");

	fprintf(out, "%s\n", str);
	char fill[MAX_LINE_LEN + 1] = { 0 };
	do_spacing_with(fill, '=', COLL_END);
	fprintf(out, "%s\n", fill);

	while(events)
	{
		TEvent_print(out, events->value);
		events = events->next;
	}

	do_spacing_with(fill, '=', COLL_END);
	fprintf(out, "%s\n", fill);

	fprintf(out, "Remaining: %s | No. of Items: %lu\n\n", TEvent_value_to_str(or->value), List_get_size(events));
}

void TEvent_delete(TEvent **event)
{


	*event = NULL;
}