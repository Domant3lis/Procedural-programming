#pragma once

#define DECIMAL_CENT_POZ 4
#define DECIMAL_CENT_POW pow_int32(10, DECIMAL_CENT_POZ)

typedef struct List List;
struct List
{
    void *value;
    List *next;
};

typedef enum
{
    USD,
    EUR,
} Currency; 

typedef struct
{
    char *description;

    // The worlds total networth is              418 342 000 000 000
    // Singed Long long max value is 9 223 372 036 854 775 807
    // Therefore, last 4 (decimal) digits will be dedicated to cents
    //
    // Positive value means income
    // Negative value means an expense
    long long value;
    Currency currency;
} TEvent; // Short for transaction event
List *List_insert_element_at(List **list, size_t poz, void *value);
List *List_create(void *value);
size_t List_get_size(List *list);
void List_delete_element(List **list, void (*free_el)(void *));
short List_delete_element_at(List **list, size_t poz, void (*free_el)(void *));
void List_destroy(List **list, void (*free_el)(void *));
void List_map(List *list, void (*fun)(void *, va_list), ...);
List *List_get_element_at(List *list, size_t poz);
void List_insert_element(List **list, void *value);
TEvent *TEvent_create(long long value, Currency cur, char *desc);
const char *TEvent_get_currency(TEvent *event);
char *TEvent_value_to_str(long long value);
void TEvent_free(void *event);
void TEvent_change_desc(TEvent *event, char *str);
void LM_TEvent_change_description(void *event, va_list args);
long long TEvent_convert_cur(TEvent *event, Currency to);
void LM_TEvent_convert_to_cur(void *event, va_list args);
void TEvent_print(TEvent *event, FILE *out);
void LM_TEvent_print(void *event, va_list args);
void List_print_TEvent(FILE *out, List *events);
