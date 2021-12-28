// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
struct List
{
	int value;
	List *next;	
};

List *createList(int value)
{
	List *new = calloc(sizeof(List), 1);
	new->value = value;
	new->next = NULL;
	return new;
}

void printList(List *list)
{
	printf("%d ", list->value);
	if (list->next != NULL)
		printList(list->next);
}

int getListSize(List *list)
{
	List *next = list->next;
	int count = 1;
	while(next != NULL)
	{
		next = next->next;
		++count;
	}
	return count;
}

void insertElement(List **list, int value)
{
	List *new = createList(value);
	new->next = *list;
	*list = new;
}

int getElement(List *list)
{
	return list->value;
}

int deleteElement(List **list)
{
	int temp = getElement(*list);
	List *next = (*list)->next;
	free(*list);
	*list = next;
	return temp;
}

void destroyList(List **list)
{
	List *next;
	List *current = (*list);

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	(*list) = NULL;
}

int main()
{
	List *foo = createList(1);
	insertElement(&foo, 2);
	insertElement(&foo, 3);
	insertElement(&foo, 4);
	insertElement(&foo, 5);
	printList(foo);
	printf("SIZE: %d\n", getListSize(foo));
	printf("DESTROY: %d\n", deleteElement(&foo));
	printList(foo);
	destroyList(&foo);
	printf("\nPlz, segfaultu \n");
	printList(foo);

	return 0;
}