// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	double x, y;
} Point;

typedef struct List List;
struct List
{
	Point value;
	List *next;	
};

List *createList(double x, double y)
{
	List *new = calloc(sizeof(List), 1);
	new->value.x = x;
	new->value.y = y;
	new->next = NULL;
	return new;
}

void printList(List *list)
{
	printf("%lf %lf  ", list->value.x, list->value.y);
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

void insertElement(List **list, double x, double y)
{
	List *new = createList(x, y);
	new->next = *list;
	*list = new;
}

Point getElement(List *list) { return list->value; }

Point deleteElement(List **list)
{
	Point temp = getElement(*list);
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
	List *foo = createList(1, 1);
	insertElement(&foo, 2, 2);
	insertElement(&foo, 3, 3);
	insertElement(&foo, 4, 4);
	insertElement(&foo, 5, 5);
	printList(foo);
	printf("SIZE: %d\n", getListSize(foo));
	Point bar = deleteElement(&foo);
	printf("DESTROY: %lf %lf\n", bar.x, bar.y);
	printList(foo);
	destroyList(&foo);
	printf("\nPlz, segfaultu \n");
	printList(foo);

	return 0;
}