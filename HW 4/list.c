#pragma once
#include <stdlib.h>
#include <stdint.h>
#include "data.c"

typedef enum 
{
    TEvent_t = 0,
} MyType;

// void (*f)(void) = &fun;
void (*List_free_value)(void);

typedef struct List List;
struct List
{
    void *value;
    List *next;
};

List *List_create(void *value)
{
    // printf("CREATE: %%s | %lld | %s", 
    //     // CUR_LIST[((TEvent *) value)->currency], 
    //     ((TEvent *) value)->value,
    //     ((TEvent *) value)->description);

    List *new = calloc(sizeof(List), 1);
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

void List_delete_element(List **list, void (*destr_fun)(void **))
{
    List *next = (*list)->next;
    free((*list)->value);
    free(*list);
    *list = next;
}

// To rework ????
void List_destroy(List **list, void (*destr_fun)(void **))
{
    List *next;
    List *current = (*list);

    while (current != NULL)
    {
        next = current->next;
        List_delete_element(&current, destr_fun);
        current = next;
    }

    (*list) = NULL;
}

void *List_get_value(List *list)
    { return list->value; }

// TODO
// void List_insert_element_at(List **list, void *value)

void List_insert_element(List **list, void *value)
{
    List *new = List_create(value);
    new->next = *list;
    *list = new;
}
